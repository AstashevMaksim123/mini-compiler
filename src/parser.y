%{
#include "ast.hpp"
#include "parser_context.hpp"

#include <cstdlib>
#include <string>
#include <vector>

#ifndef YYLTYPE_IS_DECLARED
struct MiniYYLType {
    int first_line;
    int first_column;
    int last_line;
    int last_column;
};

#define YYLTYPE MiniYYLType
#define YYLTYPE_IS_DECLARED 1
#endif

int yylex(void);
void yyerror(mini::ParserContext& ctx, const char* msg);
extern YYLTYPE yylloc;

static mini::SourceRange makeRange(const YYLTYPE& loc) {
    mini::SourceRange range;
    range.begin.line = loc.first_line;
    range.begin.column = loc.first_column;
    range.end.line = loc.last_line;
    range.end.column = loc.last_column;
    return range;
}
%}

%code requires {
#include "ast.hpp"
#include "parser_context.hpp"

#include <cstdint>
#include <vector>

#ifndef YYLTYPE_IS_DECLARED
struct MiniYYLType {
    int first_line;
    int first_column;
    int last_line;
    int last_column;
};

#define YYLTYPE MiniYYLType
#define YYLTYPE_IS_DECLARED 1
#endif
}

%define parse.error detailed
%locations
%parse-param { mini::ParserContext& ctx }

%union {
    char* str;
    std::int64_t int_val;
    mini::TypeKind type;
    mini::Expr* expr;
    mini::Stmt* stmt;
    mini::BlockStmt* block;
    mini::CaseClause* case_clause;
    mini::FunctionDecl* function;
    mini::Param* param;
    std::vector<mini::Expr*>* expr_list;
    std::vector<mini::Stmt*>* stmt_list;
    std::vector<mini::CaseClause*>* case_list;
    std::vector<mini::FunctionDecl*>* function_list;
    std::vector<mini::Param*>* param_list;
}

%token <str> IDENT
%token <int_val> INT_LITERAL
%token FN LET MUT IF ELSE FOR RETURN SWITCH CASE DEFAULT BREAK CONTINUE TRUE FALSE
%token INT_TY BOOL_TY
%token EQ NE LE GE ANDAND OROR ARROW

%type <type> type
%type <expr> expr logical_or logical_and equality relational additive multiplicative unary primary call
%type <stmt> stmt simple_stmt var_decl_stmt assign_stmt return_stmt break_stmt continue_stmt expr_stmt if_stmt for_stmt switch_stmt
%type <block> block
%type <case_clause> case_clause
%type <function> function
%type <param> param
%type <expr_list> arg_list arg_list_nonempty
%type <stmt_list> stmt_list
%type <case_list> case_list
%type <function_list> function_list
%type <param_list> params param_list_nonempty

%destructor { free($$); } <str>
%left OROR
%left ANDAND
%left EQ NE
%left '<' '>' LE GE
%left '+' '-'
%left '*' '/' '%'
%right UMINUS '!'

%%

program:
    function_list {
        ctx.program = std::make_unique<mini::Program>(*$1);
        delete $1;
    }
    ;

function_list:
    function {
        $$ = new std::vector<mini::FunctionDecl*>();
        $$->push_back($1);
    }
    | function_list function {
        $1->push_back($2);
        $$ = $1;
    }
    ;

function:
    FN IDENT '(' params ')' ARROW type block {
        std::string name($2);
        free($2);
        $$ = new mini::FunctionDecl(makeRange(@$), name, *$4, $7, $8);
        delete $4;
    }
    ;

params:
    {
        $$ = new std::vector<mini::Param*>();
    }
    | param_list_nonempty {
        $$ = $1;
    }
    ;

param_list_nonempty:
    param {
        $$ = new std::vector<mini::Param*>();
        $$->push_back($1);
    }
    | param_list_nonempty ',' param {
        $1->push_back($3);
        $$ = $1;
    }
    ;

param:
    IDENT ':' type {
        std::string name($1);
        free($1);
        $$ = new mini::Param(makeRange(@$), name, $3);
    }
    ;

type:
    INT_TY { $$ = mini::TypeKind::Int; }
    | BOOL_TY { $$ = mini::TypeKind::Bool; }
    ;

block:
    '{' stmt_list '}' {
        $$ = new mini::BlockStmt(makeRange(@$), *$2);
        delete $2;
    }
    ;

stmt_list:
    {
        $$ = new std::vector<mini::Stmt*>();
    }
    | stmt_list stmt {
        $1->push_back($2);
        $$ = $1;
    }
    ;

stmt:
    simple_stmt { $$ = $1; }
    | block { $$ = $1; }
    | if_stmt { $$ = $1; }
    | for_stmt { $$ = $1; }
    | switch_stmt { $$ = $1; }
    ;

simple_stmt:
    var_decl_stmt ';' { $$ = $1; }
    | assign_stmt ';' { $$ = $1; }
    | return_stmt ';' { $$ = $1; }
    | break_stmt ';' { $$ = $1; }
    | continue_stmt ';' { $$ = $1; }
    | expr_stmt ';' { $$ = $1; }
    ;

var_decl_stmt:
    LET MUT IDENT ':' type '=' expr {
        std::string name($3);
        free($3);
        $$ = new mini::VarDeclStmt(makeRange(@$), name, $5, true, $7);
    }
    | LET IDENT ':' type '=' expr {
        std::string name($2);
        free($2);
        $$ = new mini::VarDeclStmt(makeRange(@$), name, $4, false, $6);
    }
    ;

assign_stmt:
    IDENT '=' expr {
        std::string name($1);
        free($1);
        $$ = new mini::AssignStmt(makeRange(@$), name, $3);
    }
    ;

return_stmt:
    RETURN expr {
        $$ = new mini::ReturnStmt(makeRange(@$), $2);
    }
    ;

break_stmt:
    BREAK {
        $$ = new mini::BreakStmt(makeRange(@$));
    }
    ;

continue_stmt:
    CONTINUE {
        $$ = new mini::ContinueStmt(makeRange(@$));
    }
    ;

expr_stmt:
    expr {
        $$ = new mini::ExprStmt(makeRange(@$), $1);
    }
    ;

if_stmt:
    IF expr block ELSE block {
        $$ = new mini::IfStmt(makeRange(@$), $2, $3, $5);
    }
    | IF expr block {
        $$ = new mini::IfStmt(makeRange(@$), $2, $3, nullptr);
    }
    ;

for_stmt:
    FOR var_decl_stmt ';' expr ';' assign_stmt block {
        $$ = new mini::ForStmt(makeRange(@$), $2, $4, $6, $7);
    }
    | FOR assign_stmt ';' expr ';' assign_stmt block {
        $$ = new mini::ForStmt(makeRange(@$), $2, $4, $6, $7);
    }
    ;

switch_stmt:
    SWITCH expr '{' case_list '}' {
        $$ = new mini::SwitchStmt(makeRange(@$), $2, *$4);
        delete $4;
    }
    ;

case_list:
    case_clause {
        $$ = new std::vector<mini::CaseClause*>();
        $$->push_back($1);
    }
    | case_list case_clause {
        $1->push_back($2);
        $$ = $1;
    }
    ;

case_clause:
    CASE INT_LITERAL block {
        $$ = new mini::CaseClause(makeRange(@$), false, $2, $3);
    }
    | DEFAULT block {
        $$ = new mini::CaseClause(makeRange(@$), true, 0, $2);
    }
    ;

expr:
    logical_or { $$ = $1; }
    ;

logical_or:
    logical_or OROR logical_and { $$ = new mini::BinaryExpr(makeRange(@$), "||", $1, $3); }
    | logical_and { $$ = $1; }
    ;

logical_and:
    logical_and ANDAND equality { $$ = new mini::BinaryExpr(makeRange(@$), "&&", $1, $3); }
    | equality { $$ = $1; }
    ;

equality:
    equality EQ relational { $$ = new mini::BinaryExpr(makeRange(@$), "==", $1, $3); }
    | equality NE relational { $$ = new mini::BinaryExpr(makeRange(@$), "!=", $1, $3); }
    | relational { $$ = $1; }
    ;

relational:
    relational '<' additive { $$ = new mini::BinaryExpr(makeRange(@$), "<", $1, $3); }
    | relational '>' additive { $$ = new mini::BinaryExpr(makeRange(@$), ">", $1, $3); }
    | relational LE additive { $$ = new mini::BinaryExpr(makeRange(@$), "<=", $1, $3); }
    | relational GE additive { $$ = new mini::BinaryExpr(makeRange(@$), ">=", $1, $3); }
    | additive { $$ = $1; }
    ;

additive:
    additive '+' multiplicative { $$ = new mini::BinaryExpr(makeRange(@$), "+", $1, $3); }
    | additive '-' multiplicative { $$ = new mini::BinaryExpr(makeRange(@$), "-", $1, $3); }
    | multiplicative { $$ = $1; }
    ;

multiplicative:
    multiplicative '*' unary { $$ = new mini::BinaryExpr(makeRange(@$), "*", $1, $3); }
    | multiplicative '/' unary { $$ = new mini::BinaryExpr(makeRange(@$), "/", $1, $3); }
    | multiplicative '%' unary { $$ = new mini::BinaryExpr(makeRange(@$), "%", $1, $3); }
    | unary { $$ = $1; }
    ;

unary:
    '-' unary %prec UMINUS { $$ = new mini::UnaryExpr(makeRange(@$), "-", $2); }
    | '!' unary { $$ = new mini::UnaryExpr(makeRange(@$), "!", $2); }
    | call { $$ = $1; }
    ;

call:
    IDENT '(' arg_list ')' {
        std::string callee($1);
        free($1);
        $$ = new mini::CallExpr(makeRange(@$), callee, *$3);
        delete $3;
    }
    | primary { $$ = $1; }
    ;

arg_list:
    {
        $$ = new std::vector<mini::Expr*>();
    }
    | arg_list_nonempty { $$ = $1; }
    ;

arg_list_nonempty:
    expr {
        $$ = new std::vector<mini::Expr*>();
        $$->push_back($1);
    }
    | arg_list_nonempty ',' expr {
        $1->push_back($3);
        $$ = $1;
    }
    ;

primary:
    INT_LITERAL { $$ = new mini::IntLiteralExpr(makeRange(@$), $1); }
    | TRUE { $$ = new mini::BoolLiteralExpr(makeRange(@$), true); }
    | FALSE { $$ = new mini::BoolLiteralExpr(makeRange(@$), false); }
    | IDENT {
        std::string name($1);
        free($1);
        $$ = new mini::VarExpr(makeRange(@$), name);
    }
    | '(' expr ')' { $$ = $2; }
    ;

%%

void yyerror(mini::ParserContext& ctx, const char* msg) {
    ctx.report(makeRange(yylloc), msg);
}
