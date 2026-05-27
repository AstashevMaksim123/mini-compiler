#pragma once

#include "ast.hpp"

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace mini {

class CodeGenerator {
public:
    CodeGenerator(std::string moduleName, std::string targetTriple);

    bool generate(const Program& program, std::string& errorMessage);
    llvm::Module& module();
    const std::string& targetTriple() const;

private:
    struct VariableInfo {
        llvm::AllocaInst* alloca = nullptr;
        TypeKind type = TypeKind::Invalid;
    };

    llvm::LLVMContext context_;
    std::unique_ptr<llvm::Module> module_;
    llvm::IRBuilder<> builder_;
    std::string targetTriple_;
    std::vector<std::unordered_map<std::string, VariableInfo>> scopes_;
    std::unordered_map<std::string, llvm::Function*> functionTable_;
    std::unordered_map<std::string, FunctionDecl*> astFunctions_;
    std::vector<llvm::BasicBlock*> breakTargets_;
    std::vector<llvm::BasicBlock*> continueTargets_;
    std::string errorMessage_;

    void pushScope();
    void popScope();
    void bindVariable(const std::string& name, VariableInfo info);
    VariableInfo* lookupVariable(const std::string& name);

    llvm::Type* llvmType(TypeKind type);
    llvm::AllocaInst* createEntryBlockAlloca(llvm::Function* function, const std::string& name, llvm::Type* type);
    bool declareFunctions(const Program& program);
    bool emitFunction(const FunctionDecl& function);
    bool emitBlock(const BlockStmt& block);
    bool emitStmt(const Stmt& stmt);
    llvm::Value* emitExpr(const Expr& expr);
    llvm::Value* emitCondition(const Expr& expr);
    void setError(const std::string& message);
};

}  // namespace mini

