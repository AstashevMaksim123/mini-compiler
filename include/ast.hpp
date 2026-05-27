#pragma once

#include "location.hpp"

#include <cstdint>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace mini {

enum class TypeKind {
    Int,
    Bool,
    Invalid
};

std::string toString(TypeKind type);

struct Node {
    explicit Node(SourceRange range) : range(range) {}
    virtual ~Node() = default;
    SourceRange range;
};

struct Expr : Node {
    explicit Expr(SourceRange range) : Node(range) {}
    TypeKind inferredType = TypeKind::Invalid;
};

struct Stmt : Node {
    explicit Stmt(SourceRange range) : Node(range) {}
};

struct Param : Node {
    Param(SourceRange range, std::string name, TypeKind type);
    std::string name;
    TypeKind type;
};

struct IntLiteralExpr : Expr {
    IntLiteralExpr(SourceRange range, std::int64_t value);
    std::int64_t value;
};

struct BoolLiteralExpr : Expr {
    BoolLiteralExpr(SourceRange range, bool value);
    bool value;
};

struct VarExpr : Expr {
    VarExpr(SourceRange range, std::string name);
    std::string name;
};

struct UnaryExpr : Expr {
    UnaryExpr(SourceRange range, std::string op, Expr* operand);
    std::string op;
    std::unique_ptr<Expr> operand;
};

struct BinaryExpr : Expr {
    BinaryExpr(SourceRange range, std::string op, Expr* lhs, Expr* rhs);
    std::string op;
    std::unique_ptr<Expr> lhs;
    std::unique_ptr<Expr> rhs;
};

struct CallExpr : Expr {
    CallExpr(SourceRange range, std::string callee, std::vector<Expr*> args);
    std::string callee;
    std::vector<std::unique_ptr<Expr>> args;
};

struct BlockStmt : Stmt {
    BlockStmt(SourceRange range, std::vector<Stmt*> statements);
    std::vector<std::unique_ptr<Stmt>> statements;
};

struct VarDeclStmt : Stmt {
    VarDeclStmt(SourceRange range, std::string name, TypeKind type, bool isMutable, Expr* initializer);
    std::string name;
    TypeKind type;
    bool isMutable;
    std::unique_ptr<Expr> initializer;
};

struct AssignStmt : Stmt {
    AssignStmt(SourceRange range, std::string name, Expr* value);
    std::string name;
    std::unique_ptr<Expr> value;
};

struct ExprStmt : Stmt {
    ExprStmt(SourceRange range, Expr* expr);
    std::unique_ptr<Expr> expr;
};

struct IfStmt : Stmt {
    IfStmt(SourceRange range, Expr* condition, BlockStmt* thenBlock, BlockStmt* elseBlock);
    std::unique_ptr<Expr> condition;
    std::unique_ptr<BlockStmt> thenBlock;
    std::unique_ptr<BlockStmt> elseBlock;
};

struct ForStmt : Stmt {
    ForStmt(SourceRange range, Stmt* init, Expr* condition, Stmt* step, BlockStmt* body);
    std::unique_ptr<Stmt> init;
    std::unique_ptr<Expr> condition;
    std::unique_ptr<Stmt> step;
    std::unique_ptr<BlockStmt> body;
};

struct ReturnStmt : Stmt {
    ReturnStmt(SourceRange range, Expr* value);
    std::unique_ptr<Expr> value;
};

struct BreakStmt : Stmt {
    explicit BreakStmt(SourceRange range);
};

struct ContinueStmt : Stmt {
    explicit ContinueStmt(SourceRange range);
};

struct CaseClause : Node {
    CaseClause(SourceRange range, bool isDefault, std::int64_t value, BlockStmt* body);
    bool isDefault;
    std::int64_t value;
    std::unique_ptr<BlockStmt> body;
};

struct SwitchStmt : Stmt {
    SwitchStmt(SourceRange range, Expr* value, std::vector<CaseClause*> clauses);
    std::unique_ptr<Expr> value;
    std::vector<std::unique_ptr<CaseClause>> clauses;
};

struct FunctionDecl : Node {
    FunctionDecl(SourceRange range, std::string name, std::vector<Param*> params, TypeKind returnType, BlockStmt* body);
    std::string name;
    std::vector<std::unique_ptr<Param>> params;
    TypeKind returnType;
    std::unique_ptr<BlockStmt> body;
};

struct Program : Node {
    explicit Program(std::vector<FunctionDecl*> functions);
    std::vector<std::unique_ptr<FunctionDecl>> functions;
};

}  // namespace mini

