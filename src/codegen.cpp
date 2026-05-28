#include "codegen.hpp"ж

#include <llvm/IR/Constants.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Verifier.h>

namespace mini {

CodeGenerator::CodeGenerator(std::string moduleName, std::string targetTriple)
    : module_(std::make_unique<llvm::Module>(std::move(moduleName), context_)),
      builder_(context_),
      targetTriple_(std::move(targetTriple)) {
    module_->setTargetTriple(targetTriple_);
}

bool CodeGenerator::generate(const Program& program, std::string& errorMessage) {
    errorMessage_.clear();
    functionTable_.clear();
    astFunctions_.clear();

    if (!declareFunctions(program)) {
        errorMessage = errorMessage_;
        return false;
    }

    for (const auto& function : program.functions) {
        if (!emitFunction(*function)) {
            errorMessage = errorMessage_;
            return false;
        }
    }

    if (llvm::verifyModule(*module_, &llvm::errs())) {
        errorMessage = "LLVM module verification failed";
        return false;
    }

    errorMessage.clear();
    return true;
}

llvm::Module& CodeGenerator::module() {
    return *module_;
}

const std::string& CodeGenerator::targetTriple() const {
    return targetTriple_;
}

void CodeGenerator::pushScope() {
    scopes_.emplace_back();
}

void CodeGenerator::popScope() {
    scopes_.pop_back();
}

void CodeGenerator::bindVariable(const std::string& name, VariableInfo info) {
    scopes_.back()[name] = info;
}

CodeGenerator::VariableInfo* CodeGenerator::lookupVariable(const std::string& name) {
    for (auto it = scopes_.rbegin(); it != scopes_.rend(); ++it) {
        auto found = it->find(name);
        if (found != it->end()) {
            return &found->second;
        }
    }
    return nullptr;
}

llvm::Type* CodeGenerator::llvmType(TypeKind type) {
    switch (type) {
        case TypeKind::Int:
            return llvm::Type::getInt64Ty(context_);
        case TypeKind::Bool:
            return llvm::Type::getInt1Ty(context_);
        case TypeKind::Invalid:
            return nullptr;
    }
    return nullptr;
}

llvm::AllocaInst* CodeGenerator::createEntryBlockAlloca(llvm::Function* function,
                                                        const std::string& name,
                                                        llvm::Type* type) {
    llvm::IRBuilder<> tmp(&function->getEntryBlock(), function->getEntryBlock().begin());
    return tmp.CreateAlloca(type, nullptr, name);
}

bool CodeGenerator::declareFunctions(const Program& program) {
    for (const auto& function : program.functions) {
        std::vector<llvm::Type*> paramTypes;
        for (const auto& param : function->params) {
            paramTypes.push_back(llvmType(param->type));
        }
        auto* type = llvm::FunctionType::get(llvmType(function->returnType), paramTypes, false);
        auto linkage = function->name == "compiled_fn" ? llvm::Function::ExternalLinkage : llvm::Function::InternalLinkage;
        llvm::Function* llvmFunction =
            llvm::Function::Create(type, linkage, function->name, module_.get());
        functionTable_[function->name] = llvmFunction;
        astFunctions_[function->name] = function.get();
    }
    return true;
}

bool CodeGenerator::emitFunction(const FunctionDecl& function) {
    llvm::Function* llvmFunction = functionTable_.at(function.name);
    llvmFunction->arg_begin();

    llvm::BasicBlock* entry = llvm::BasicBlock::Create(context_, "entry", llvmFunction);
    builder_.SetInsertPoint(entry);
    scopes_.clear();
    pushScope();
    breakTargets_.clear();
    continueTargets_.clear();

    std::size_t index = 0;
    for (auto& arg : llvmFunction->args()) {
        const auto& param = function.params[index];
        arg.setName(param->name);
        llvm::AllocaInst* alloca = createEntryBlockAlloca(llvmFunction, param->name, llvmType(param->type));
        builder_.CreateStore(&arg, alloca);
        bindVariable(param->name, VariableInfo{alloca, param->type});
        ++index;
    }

    if (!emitBlock(*function.body)) {
        return false;
    }

    if (builder_.GetInsertBlock() != nullptr && builder_.GetInsertBlock()->getTerminator() == nullptr) {
        builder_.CreateUnreachable();
    }

    if (llvm::verifyFunction(*llvmFunction, &llvm::errs())) {
        setError("LLVM function verification failed for '" + function.name + "'");
        return false;
    }
    return true;
}

bool CodeGenerator::emitBlock(const BlockStmt& block) {
    pushScope();
    for (const auto& stmt : block.statements) {
        if (builder_.GetInsertBlock() == nullptr || builder_.GetInsertBlock()->getTerminator() != nullptr) {
            break;
        }
        if (!emitStmt(*stmt)) {
            return false;
        }
    }
    popScope();
    return true;
}

bool CodeGenerator::emitStmt(const Stmt& stmt) {
    if (auto* block = dynamic_cast<const BlockStmt*>(&stmt)) {
        return emitBlock(*block);
    }
    if (auto* decl = dynamic_cast<const VarDeclStmt*>(&stmt)) {
        llvm::Function* function = builder_.GetInsertBlock()->getParent();
        llvm::Type* type = llvmType(decl->type);
        llvm::AllocaInst* alloca = createEntryBlockAlloca(function, decl->name, type);
        llvm::Value* initialValue = emitExpr(*decl->initializer);
        if (initialValue == nullptr) {
            return false;
        }
        builder_.CreateStore(initialValue, alloca);
        bindVariable(decl->name, VariableInfo{alloca, decl->type});
        return true;
    }
    if (auto* assign = dynamic_cast<const AssignStmt*>(&stmt)) {
        VariableInfo* variable = lookupVariable(assign->name);
        if (variable == nullptr) {
            setError("internal error: unknown variable '" + assign->name + "' during code generation");
            return false;
        }
        llvm::Value* value = emitExpr(*assign->value);
        if (value == nullptr) {
            return false;
        }
        builder_.CreateStore(value, variable->alloca);
        return true;
    }
    if (auto* exprStmt = dynamic_cast<const ExprStmt*>(&stmt)) {
        return emitExpr(*exprStmt->expr) != nullptr;
    }
    if (auto* ifStmt = dynamic_cast<const IfStmt*>(&stmt)) {
        llvm::Value* condition = emitCondition(*ifStmt->condition);
        if (condition == nullptr) {
            return false;
        }
        llvm::Function* function = builder_.GetInsertBlock()->getParent();
        llvm::BasicBlock* thenBlock = llvm::BasicBlock::Create(context_, "if.then", function);
        llvm::BasicBlock* elseBlock = ifStmt->elseBlock ? llvm::BasicBlock::Create(context_, "if.else", function) : nullptr;
        llvm::BasicBlock* endBlock = llvm::BasicBlock::Create(context_, "if.end", function);
        builder_.CreateCondBr(condition, thenBlock, elseBlock != nullptr ? elseBlock : endBlock);

        builder_.SetInsertPoint(thenBlock);
        if (!emitBlock(*ifStmt->thenBlock)) {
            return false;
        }
        if (builder_.GetInsertBlock()->getTerminator() == nullptr) {
            builder_.CreateBr(endBlock);
        }

        if (elseBlock != nullptr) {
            builder_.SetInsertPoint(elseBlock);
            if (!emitBlock(*ifStmt->elseBlock)) {
                return false;
            }
            if (builder_.GetInsertBlock()->getTerminator() == nullptr) {
                builder_.CreateBr(endBlock);
            }
        }

        builder_.SetInsertPoint(endBlock);
        return true;
    }
    if (auto* forStmt = dynamic_cast<const ForStmt*>(&stmt)) {
        pushScope();
        if (!emitStmt(*forStmt->init)) {
            return false;
        }

        llvm::Function* function = builder_.GetInsertBlock()->getParent();
        llvm::BasicBlock* condBlock = llvm::BasicBlock::Create(context_, "for.cond", function);
        llvm::BasicBlock* bodyBlock = llvm::BasicBlock::Create(context_, "for.body", function);
        llvm::BasicBlock* stepBlock = llvm::BasicBlock::Create(context_, "for.step", function);
        llvm::BasicBlock* endBlock = llvm::BasicBlock::Create(context_, "for.end", function);

        builder_.CreateBr(condBlock);
        builder_.SetInsertPoint(condBlock);
        llvm::Value* condition = emitCondition(*forStmt->condition);
        if (condition == nullptr) {
            return false;
        }
        builder_.CreateCondBr(condition, bodyBlock, endBlock);

        breakTargets_.push_back(endBlock);
        continueTargets_.push_back(stepBlock);

        builder_.SetInsertPoint(bodyBlock);
        if (!emitBlock(*forStmt->body)) {
            return false;
        }
        if (builder_.GetInsertBlock()->getTerminator() == nullptr) {
            builder_.CreateBr(stepBlock);
        }

        builder_.SetInsertPoint(stepBlock);
        if (!emitStmt(*forStmt->step)) {
            return false;
        }
        if (builder_.GetInsertBlock()->getTerminator() == nullptr) {
            builder_.CreateBr(condBlock);
        }

        breakTargets_.pop_back();
        continueTargets_.pop_back();
        builder_.SetInsertPoint(endBlock);
        popScope();
        return true;
    }
    if (auto* switchStmt = dynamic_cast<const SwitchStmt*>(&stmt)) {
        llvm::Value* value = emitExpr(*switchStmt->value);
        if (value == nullptr) {
            return false;
        }

        llvm::Function* function = builder_.GetInsertBlock()->getParent();
        llvm::BasicBlock* endBlock = llvm::BasicBlock::Create(context_, "switch.end", function);
        llvm::BasicBlock* defaultBlock = endBlock;
        const CaseClause* defaultClause = nullptr;

        for (const auto& clause : switchStmt->clauses) {
            if (clause->isDefault) {
                defaultBlock = llvm::BasicBlock::Create(context_, "switch.default", function);
                defaultClause = clause.get();
                break;
            }
        }

        auto* switchInst = builder_.CreateSwitch(value, defaultBlock, static_cast<unsigned>(switchStmt->clauses.size()));
        breakTargets_.push_back(endBlock);

        for (const auto& clause : switchStmt->clauses) {
            if (clause->isDefault) {
                continue;
            }
            llvm::BasicBlock* caseBlock = llvm::BasicBlock::Create(context_, "switch.case", function);
            switchInst->addCase(llvm::ConstantInt::getSigned(llvm::Type::getInt64Ty(context_), clause->value), caseBlock);
            builder_.SetInsertPoint(caseBlock);
            if (!emitBlock(*clause->body)) {
                return false;
            }
            if (builder_.GetInsertBlock()->getTerminator() == nullptr) {
                builder_.CreateBr(endBlock);
            }
        }

        if (defaultClause != nullptr) {
            builder_.SetInsertPoint(defaultBlock);
            if (!emitBlock(*defaultClause->body)) {
                return false;
            }
            if (builder_.GetInsertBlock()->getTerminator() == nullptr) {
                builder_.CreateBr(endBlock);
            }
        }

        breakTargets_.pop_back();
        builder_.SetInsertPoint(endBlock);
        return true;
    }
    if (auto* returnStmt = dynamic_cast<const ReturnStmt*>(&stmt)) {
        llvm::Value* value = emitExpr(*returnStmt->value);
        if (value == nullptr) {
            return false;
        }
        builder_.CreateRet(value);
        return true;
    }
    if (dynamic_cast<const BreakStmt*>(&stmt) != nullptr) {
        if (breakTargets_.empty()) {
            setError("internal error: break target stack is empty");
            return false;
        }
        builder_.CreateBr(breakTargets_.back());
        return true;
    }
    if (dynamic_cast<const ContinueStmt*>(&stmt) != nullptr) {
        if (continueTargets_.empty()) {
            setError("internal error: continue target stack is empty");
            return false;
        }
        builder_.CreateBr(continueTargets_.back());
        return true;
    }

    setError("internal error: unsupported statement during code generation");
    return false;
}

llvm::Value* CodeGenerator::emitExpr(const Expr& expr) {
    if (auto* literal = dynamic_cast<const IntLiteralExpr*>(&expr)) {
        return llvm::ConstantInt::getSigned(llvm::Type::getInt64Ty(context_), literal->value);
    }
    if (auto* literal = dynamic_cast<const BoolLiteralExpr*>(&expr)) {
        return llvm::ConstantInt::get(llvm::Type::getInt1Ty(context_), literal->value ? 1 : 0);
    }
    if (auto* var = dynamic_cast<const VarExpr*>(&expr)) {
        VariableInfo* variable = lookupVariable(var->name);
        if (variable == nullptr) {
            setError("internal error: unknown variable '" + var->name + "'");
            return nullptr;
        }
        return builder_.CreateLoad(llvmType(variable->type), variable->alloca, var->name + ".value");
    }
    if (auto* unary = dynamic_cast<const UnaryExpr*>(&expr)) {
        llvm::Value* operand = emitExpr(*unary->operand);
        if (operand == nullptr) {
            return nullptr;
        }
        if (unary->op == "-") {
            return builder_.CreateNeg(operand, "negtmp");
        }
        if (unary->op == "!") {
            return builder_.CreateNot(operand, "nottmp");
        }
    }
    if (auto* binary = dynamic_cast<const BinaryExpr*>(&expr)) {
        llvm::Value* lhs = emitExpr(*binary->lhs);
        llvm::Value* rhs = emitExpr(*binary->rhs);
        if (lhs == nullptr || rhs == nullptr) {
            return nullptr;
        }
        const std::string& op = binary->op;
        if (op == "+") {
            return builder_.CreateAdd(lhs, rhs, "addtmp");
        }
        if (op == "-") {
            return builder_.CreateSub(lhs, rhs, "subtmp");
        }
        if (op == "*") {
            return builder_.CreateMul(lhs, rhs, "multmp");
        }
        if (op == "/") {
            return builder_.CreateSDiv(lhs, rhs, "divtmp");
        }
        if (op == "%") {
            return builder_.CreateSRem(lhs, rhs, "modtmp");
        }
        if (op == "<") {
            return builder_.CreateICmpSLT(lhs, rhs, "cmptmp");
        }
        if (op == "<=") {
            return builder_.CreateICmpSLE(lhs, rhs, "cmptmp");
        }
        if (op == ">") {
            return builder_.CreateICmpSGT(lhs, rhs, "cmptmp");
        }
        if (op == ">=") {
            return builder_.CreateICmpSGE(lhs, rhs, "cmptmp");
        }
        if (op == "==") {
            return builder_.CreateICmpEQ(lhs, rhs, "eqtmp");
        }
        if (op == "!=") {
            return builder_.CreateICmpNE(lhs, rhs, "netmp");
        }
        if (op == "&&") {
            return builder_.CreateAnd(lhs, rhs, "andtmp");
        }
        if (op == "||") {
            return builder_.CreateOr(lhs, rhs, "ortmp");
        }
    }
    if (auto* call = dynamic_cast<const CallExpr*>(&expr)) {
        llvm::Function* callee = module_->getFunction(call->callee);
        if (callee == nullptr) {
            setError("internal error: unknown function '" + call->callee + "'");
            return nullptr;
        }
        std::vector<llvm::Value*> args;
        args.reserve(call->args.size());
        for (const auto& arg : call->args) {
            llvm::Value* value = emitExpr(*arg);
            if (value == nullptr) {
                return nullptr;
            }
            args.push_back(value);
        }
        return builder_.CreateCall(callee, args, call->callee + ".call");
    }

    setError("internal error: unsupported expression during code generation");
    return nullptr;
}

llvm::Value* CodeGenerator::emitCondition(const Expr& expr) {
    llvm::Value* condition = emitExpr(expr);
    if (condition == nullptr) {
        return nullptr;
    }
    return condition;
}

void CodeGenerator::setError(const std::string& message) {
    if (errorMessage_.empty()) {
        errorMessage_ = message;
    }
}

}  // namespace mini
