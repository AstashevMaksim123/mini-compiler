#include "sema.hpp"

#include <sstream>
#include <unordered_set>

namespace mini {

SemanticAnalyzer::SemanticAnalyzer(ParserContext& context) : context_(context) {}

bool SemanticAnalyzer::analyze(Program& program) {
    functions_.clear();
    for (const auto& function : program.functions) {
        if (functions_.count(function->name) != 0U) {
            report(function->range, "function '" + function->name + "' is already declared");
            continue;
        }
        FunctionInfo info;
        info.returnType = function->returnType;
        for (const auto& param : function->params) {
            info.paramTypes.push_back(param->type);
        }
        functions_.emplace(function->name, std::move(info));
    }

    if (functions_.count("compiled_fn") == 0U) {
        report(program.range, "program must define function 'compiled_fn'");
    } else {
        FunctionInfo& info = functions_.at("compiled_fn");
        if (info.returnType != TypeKind::Int || info.paramTypes.size() != 1U || info.paramTypes[0] != TypeKind::Int) {
            report(program.range, "function 'compiled_fn' must have signature fn compiled_fn(arg: int) -> int");
        }
    }

    for (const auto& function : program.functions) {
        analyzeFunction(*function);
    }
    return !context_.hasErrors();
}

void SemanticAnalyzer::pushScope() {
    scopes_.emplace_back();
}

void SemanticAnalyzer::popScope() {
    scopes_.pop_back();
}

bool SemanticAnalyzer::declareVariable(const std::string& name, VariableInfo info, const SourceRange& range) {
    auto& scope = scopes_.back();
    if (scope.count(name) != 0U) {
        report(range, "variable '" + name + "' is already declared in this scope");
        return false;
    }
    scope.emplace(name, info);
    return true;
}

SemanticAnalyzer::VariableInfo* SemanticAnalyzer::lookupVariable(const std::string& name) {
    for (auto it = scopes_.rbegin(); it != scopes_.rend(); ++it) {
        auto found = it->find(name);
        if (found != it->end()) {
            return &found->second;
        }
    }
    return nullptr;
}

SemanticAnalyzer::FunctionInfo* SemanticAnalyzer::lookupFunction(const std::string& name) {
    auto it = functions_.find(name);
    return it == functions_.end() ? nullptr : &it->second;
}

void SemanticAnalyzer::analyzeFunction(FunctionDecl& function) {
    scopes_.clear();
    pushScope();
    currentReturnType_ = function.returnType;

    for (const auto& param : function.params) {
        declareVariable(param->name, VariableInfo{param->type, false}, param->range);
    }

    analyzeBlock(*function.body);
    if (!blockAlwaysReturns(*function.body)) {
        report(function.range, "function '" + function.name + "' does not return a value on all paths");
    }
    popScope();
}

void SemanticAnalyzer::analyzeBlock(BlockStmt& block) {
    pushScope();
    for (const auto& stmt : block.statements) {
        analyzeStmt(*stmt);
    }
    popScope();
}

void SemanticAnalyzer::analyzeStmt(Stmt& stmt) {
    if (auto* block = dynamic_cast<BlockStmt*>(&stmt)) {
        analyzeBlock(*block);
        return;
    }
    if (auto* decl = dynamic_cast<VarDeclStmt*>(&stmt)) {
        TypeKind initType = analyzeExpr(*decl->initializer);
        if (initType != decl->type && initType != TypeKind::Invalid) {
            report(decl->range, "cannot initialize variable '" + decl->name + "' of type " + toString(decl->type) +
                                    " with expression of type " + toString(initType));
        }
        declareVariable(decl->name, VariableInfo{decl->type, decl->isMutable}, decl->range);
        return;
    }
    if (auto* assign = dynamic_cast<AssignStmt*>(&stmt)) {
        VariableInfo* variable = lookupVariable(assign->name);
        if (variable == nullptr) {
            report(assign->range, "variable '" + assign->name + "' is not declared");
            analyzeExpr(*assign->value);
            return;
        }
        if (!variable->isMutable) {
            report(assign->range, "variable '" + assign->name + "' is not mutable");
        }
        TypeKind valueType = analyzeExpr(*assign->value);
        if (valueType != variable->type && valueType != TypeKind::Invalid) {
            report(assign->range, "cannot assign expression of type " + toString(valueType) + " to variable '" +
                                      assign->name + "' of type " + toString(variable->type));
        }
        return;
    }
    if (auto* exprStmt = dynamic_cast<ExprStmt*>(&stmt)) {
        analyzeExpr(*exprStmt->expr);
        return;
    }
    if (auto* ifStmt = dynamic_cast<IfStmt*>(&stmt)) {
        TypeKind conditionType = analyzeExpr(*ifStmt->condition);
        if (conditionType != TypeKind::Bool && conditionType != TypeKind::Invalid) {
            report(ifStmt->condition->range, "if condition must have type bool");
        }
        analyzeBlock(*ifStmt->thenBlock);
        if (ifStmt->elseBlock) {
            analyzeBlock(*ifStmt->elseBlock);
        }
        return;
    }
    if (auto* forStmt = dynamic_cast<ForStmt*>(&stmt)) {
        pushScope();
        ++loopDepth_;
        analyzeStmt(*forStmt->init);
        TypeKind conditionType = analyzeExpr(*forStmt->condition);
        if (conditionType != TypeKind::Bool && conditionType != TypeKind::Invalid) {
            report(forStmt->condition->range, "for condition must have type bool");
        }
        analyzeBlock(*forStmt->body);
        analyzeStmt(*forStmt->step);
        --loopDepth_;
        popScope();
        return;
    }
    if (auto* switchStmt = dynamic_cast<SwitchStmt*>(&stmt)) {
        TypeKind switchType = analyzeExpr(*switchStmt->value);
        if (switchType != TypeKind::Int && switchType != TypeKind::Invalid) {
            report(switchStmt->value->range, "switch expression must have type int");
        }
        ++switchDepth_;
        std::unordered_set<std::int64_t> usedCases;
        bool seenDefault = false;
        for (const auto& clause : switchStmt->clauses) {
            if (clause->isDefault) {
                if (seenDefault) {
                    report(clause->range, "switch cannot contain more than one default clause");
                }
                seenDefault = true;
            } else if (!usedCases.insert(clause->value).second) {
                report(clause->range, "duplicate case value " + std::to_string(clause->value));
            }
            analyzeBlock(*clause->body);
        }
        --switchDepth_;
        return;
    }
    if (auto* returnStmt = dynamic_cast<ReturnStmt*>(&stmt)) {
        TypeKind valueType = analyzeExpr(*returnStmt->value);
        if (valueType != currentReturnType_ && valueType != TypeKind::Invalid) {
            report(returnStmt->range, "return type mismatch: expected " + toString(currentReturnType_) + ", got " +
                                          toString(valueType));
        }
        return;
    }
    if (dynamic_cast<BreakStmt*>(&stmt) != nullptr) {
        if (loopDepth_ == 0 && switchDepth_ == 0) {
            report(stmt.range, "break is not allowed outside loop or switch");
        }
        return;
    }
    if (dynamic_cast<ContinueStmt*>(&stmt) != nullptr) {
        if (loopDepth_ == 0) {
            report(stmt.range, "continue is not allowed outside loop");
        }
        return;
    }
}

TypeKind SemanticAnalyzer::analyzeExpr(Expr& expr) {
    if (auto* literal = dynamic_cast<IntLiteralExpr*>(&expr)) {
        (void)literal;
        expr.inferredType = TypeKind::Int;
        return expr.inferredType;
    }
    if (auto* literal = dynamic_cast<BoolLiteralExpr*>(&expr)) {
        (void)literal;
        expr.inferredType = TypeKind::Bool;
        return expr.inferredType;
    }
    if (auto* var = dynamic_cast<VarExpr*>(&expr)) {
        VariableInfo* info = lookupVariable(var->name);
        if (info == nullptr) {
            report(var->range, "variable '" + var->name + "' is not declared");
            expr.inferredType = TypeKind::Invalid;
            return expr.inferredType;
        }
        expr.inferredType = info->type;
        return expr.inferredType;
    }
    if (auto* unary = dynamic_cast<UnaryExpr*>(&expr)) {
        TypeKind operandType = analyzeExpr(*unary->operand);
        if (unary->op == "-") {
            if (operandType != TypeKind::Int && operandType != TypeKind::Invalid) {
                report(unary->range, "unary '-' expects operand of type int");
            }
            expr.inferredType = TypeKind::Int;
            return expr.inferredType;
        }
        if (unary->op == "!") {
            if (operandType != TypeKind::Bool && operandType != TypeKind::Invalid) {
                report(unary->range, "unary '!' expects operand of type bool");
            }
            expr.inferredType = TypeKind::Bool;
            return expr.inferredType;
        }
    }
    if (auto* binary = dynamic_cast<BinaryExpr*>(&expr)) {
        TypeKind lhsType = analyzeExpr(*binary->lhs);
        TypeKind rhsType = analyzeExpr(*binary->rhs);
        const std::string& op = binary->op;
        if (op == "+" || op == "-" || op == "*" || op == "/" || op == "%") {
            if (lhsType != TypeKind::Int || rhsType != TypeKind::Int) {
                if (lhsType != TypeKind::Invalid && rhsType != TypeKind::Invalid) {
                    report(binary->range, "arithmetic operator '" + op + "' expects int operands");
                }
            }
            expr.inferredType = TypeKind::Int;
            return expr.inferredType;
        }
        if (op == "<" || op == "<=" || op == ">" || op == ">=") {
            if (lhsType != TypeKind::Int || rhsType != TypeKind::Int) {
                if (lhsType != TypeKind::Invalid && rhsType != TypeKind::Invalid) {
                    report(binary->range, "comparison operator '" + op + "' expects int operands");
                }
            }
            expr.inferredType = TypeKind::Bool;
            return expr.inferredType;
        }
        if (op == "==" || op == "!=") {
            if (lhsType != rhsType && lhsType != TypeKind::Invalid && rhsType != TypeKind::Invalid) {
                report(binary->range, "equality operator '" + op + "' expects operands of the same type");
            }
            expr.inferredType = TypeKind::Bool;
            return expr.inferredType;
        }
        if (op == "&&" || op == "||") {
            if (lhsType != TypeKind::Bool || rhsType != TypeKind::Bool) {
                if (lhsType != TypeKind::Invalid && rhsType != TypeKind::Invalid) {
                    report(binary->range, "logical operator '" + op + "' expects bool operands");
                }
            }
            expr.inferredType = TypeKind::Bool;
            return expr.inferredType;
        }
    }
    if (auto* call = dynamic_cast<CallExpr*>(&expr)) {
        FunctionInfo* function = lookupFunction(call->callee);
        if (function == nullptr) {
            report(call->range, "function '" + call->callee + "' is not declared");
            expr.inferredType = TypeKind::Invalid;
            return expr.inferredType;
        }
        if (function->paramTypes.size() != call->args.size()) {
            report(call->range, "function '" + call->callee + "' expects " +
                                    std::to_string(function->paramTypes.size()) + " arguments, got " +
                                    std::to_string(call->args.size()));
        }
        for (std::size_t i = 0; i < call->args.size(); ++i) {
            TypeKind argType = analyzeExpr(*call->args[i]);
            if (i < function->paramTypes.size() && argType != function->paramTypes[i] && argType != TypeKind::Invalid) {
                report(call->args[i]->range,
                       "argument " + std::to_string(i + 1) + " of function '" + call->callee + "' must have type " +
                           toString(function->paramTypes[i]));
            }
        }
        expr.inferredType = function->returnType;
        return expr.inferredType;
    }

    expr.inferredType = TypeKind::Invalid;
    return expr.inferredType;
}

bool SemanticAnalyzer::stmtAlwaysReturns(const Stmt& stmt) const {
    if (dynamic_cast<const ReturnStmt*>(&stmt) != nullptr) {
        return true;
    }
    if (auto* block = dynamic_cast<const BlockStmt*>(&stmt)) {
        return blockAlwaysReturns(*block);
    }
    if (auto* ifStmt = dynamic_cast<const IfStmt*>(&stmt)) {
        return ifStmt->elseBlock != nullptr && blockAlwaysReturns(*ifStmt->thenBlock) && blockAlwaysReturns(*ifStmt->elseBlock);
    }
    if (auto* switchStmt = dynamic_cast<const SwitchStmt*>(&stmt)) {
        bool hasDefault = false;
        for (const auto& clause : switchStmt->clauses) {
            hasDefault = hasDefault || clause->isDefault;
            if (!blockAlwaysReturns(*clause->body)) {
                return false;
            }
        }
        return hasDefault && !switchStmt->clauses.empty();
    }
    return false;
}

bool SemanticAnalyzer::blockAlwaysReturns(const BlockStmt& block) const {
    for (const auto& stmt : block.statements) {
        if (stmtAlwaysReturns(*stmt)) {
            return true;
        }
    }
    return false;
}

void SemanticAnalyzer::report(const SourceRange& range, const std::string& message) {
    context_.report(range, message);
}

ParserContext::ParserContext(std::string fileName) : fileName(std::move(fileName)) {}

void ParserContext::report(const SourceRange& range, std::string message) {
    diagnostics.push_back(Diagnostic{range, std::move(message)});
}

bool ParserContext::hasErrors() const {
    return !diagnostics.empty();
}

std::string ParserContext::formatDiagnostics() const {
    std::ostringstream output;
    for (const auto& diagnostic : diagnostics) {
        output << "line " << diagnostic.range.begin.line << ":" << diagnostic.range.begin.column << ": "
               << diagnostic.message << '\n';
    }
    return output.str();
}

}  // namespace mini
