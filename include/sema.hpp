#pragma once

#include "parser_context.hpp"

#include <string>
#include <unordered_map>
#include <vector>

namespace mini {

class SemanticAnalyzer {
public:
    explicit SemanticAnalyzer(ParserContext& context);

    bool analyze(Program& program);

private:
    struct VariableInfo {
        TypeKind type = TypeKind::Invalid;
        bool isMutable = false;
    };

    struct FunctionInfo {
        TypeKind returnType = TypeKind::Invalid;
        std::vector<TypeKind> paramTypes;
    };

    ParserContext& context_;
    std::unordered_map<std::string, FunctionInfo> functions_;
    std::vector<std::unordered_map<std::string, VariableInfo>> scopes_;
    TypeKind currentReturnType_ = TypeKind::Invalid;
    int loopDepth_ = 0;
    int switchDepth_ = 0;

    void pushScope();
    void popScope();
    bool declareVariable(const std::string& name, VariableInfo info, const SourceRange& range);
    VariableInfo* lookupVariable(const std::string& name);
    FunctionInfo* lookupFunction(const std::string& name);

    void analyzeFunction(FunctionDecl& function);
    void analyzeBlock(BlockStmt& block);
    void analyzeStmt(Stmt& stmt);
    TypeKind analyzeExpr(Expr& expr);
    bool stmtAlwaysReturns(const Stmt& stmt) const;
    bool blockAlwaysReturns(const BlockStmt& block) const;
    void report(const SourceRange& range, const std::string& message);
};

}  // namespace mini

