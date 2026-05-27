#include "ast.hpp"

#include <utility>

namespace mini {

namespace {

template <typename T>
std::vector<std::unique_ptr<T>> adoptVector(std::vector<T*> values) {
    std::vector<std::unique_ptr<T>> result;
    result.reserve(values.size());
    for (T* value : values) {
        result.emplace_back(value);
    }
    return result;
}

}  // namespace

std::string toString(TypeKind type) {
    switch (type) {
        case TypeKind::Int:
            return "int";
        case TypeKind::Bool:
            return "bool";
        case TypeKind::Invalid:
            return "<invalid>";
    }
    return "<invalid>";
}

Param::Param(SourceRange range, std::string name, TypeKind type)
    : Node(range), name(std::move(name)), type(type) {}

IntLiteralExpr::IntLiteralExpr(SourceRange range, std::int64_t value)
    : Expr(range), value(value) {}

BoolLiteralExpr::BoolLiteralExpr(SourceRange range, bool value)
    : Expr(range), value(value) {}

VarExpr::VarExpr(SourceRange range, std::string name)
    : Expr(range), name(std::move(name)) {}

UnaryExpr::UnaryExpr(SourceRange range, std::string op, Expr* operand)
    : Expr(range), op(std::move(op)), operand(operand) {}

BinaryExpr::BinaryExpr(SourceRange range, std::string op, Expr* lhs, Expr* rhs)
    : Expr(range), op(std::move(op)), lhs(lhs), rhs(rhs) {}

CallExpr::CallExpr(SourceRange range, std::string callee, std::vector<Expr*> args)
    : Expr(range), callee(std::move(callee)), args(adoptVector(std::move(args))) {}

BlockStmt::BlockStmt(SourceRange range, std::vector<Stmt*> statements)
    : Stmt(range), statements(adoptVector(std::move(statements))) {}

VarDeclStmt::VarDeclStmt(SourceRange range, std::string name, TypeKind type, bool isMutable, Expr* initializer)
    : Stmt(range), name(std::move(name)), type(type), isMutable(isMutable), initializer(initializer) {}

AssignStmt::AssignStmt(SourceRange range, std::string name, Expr* value)
    : Stmt(range), name(std::move(name)), value(value) {}

ExprStmt::ExprStmt(SourceRange range, Expr* expr)
    : Stmt(range), expr(expr) {}

IfStmt::IfStmt(SourceRange range, Expr* condition, BlockStmt* thenBlock, BlockStmt* elseBlock)
    : Stmt(range), condition(condition), thenBlock(thenBlock), elseBlock(elseBlock) {}

ForStmt::ForStmt(SourceRange range, Stmt* init, Expr* condition, Stmt* step, BlockStmt* body)
    : Stmt(range), init(init), condition(condition), step(step), body(body) {}

ReturnStmt::ReturnStmt(SourceRange range, Expr* value)
    : Stmt(range), value(value) {}

BreakStmt::BreakStmt(SourceRange range)
    : Stmt(range) {}

ContinueStmt::ContinueStmt(SourceRange range)
    : Stmt(range) {}

CaseClause::CaseClause(SourceRange range, bool isDefault, std::int64_t value, BlockStmt* body)
    : Node(range), isDefault(isDefault), value(value), body(body) {}

SwitchStmt::SwitchStmt(SourceRange range, Expr* value, std::vector<CaseClause*> clauses)
    : Stmt(range), value(value), clauses(adoptVector(std::move(clauses))) {}

FunctionDecl::FunctionDecl(SourceRange range, std::string name, std::vector<Param*> params, TypeKind returnType, BlockStmt* body)
    : Node(range), name(std::move(name)), params(adoptVector(std::move(params))), returnType(returnType), body(body) {}

Program::Program(std::vector<FunctionDecl*> functions)
    : Node(SourceRange{}), functions(adoptVector(std::move(functions))) {}

}  // namespace mini

