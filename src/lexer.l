%option noyywrap nounput noinput

%{
#include "parser.hpp";

#include <cstdlib>
#include <cstring>

static int lexer_line = 1;
static int lexer_column = 1;

#define YY_USER_ACTION                                                                    \
    do {                                                                                  \
        yylloc.first_line = lexer_line;                                                   \
        yylloc.first_column = lexer_column;                                               \
        int current_line = lexer_line;                                                    \
        int current_column = lexer_column;                                                \
        for (int i = 0; i < yyleng; ++i) {                                                \
            if (yytext[i] == '\n') {                                                      \
                ++current_line;                                                           \
                current_column = 1;                                                       \
            } else {                                                                      \
                ++current_column;                                                         \
            }                                                                             \
        }                                                                                 \
        yylloc.last_line = current_line;                                                  \
        yylloc.last_column = current_column - 1;                                          \
        lexer_line = current_line;                                                        \
        lexer_column = current_column;                                                    \
    } while (0);
%}

%x COMMENT

%%

[ \t\r]+                     ;
\n+                          ;
"//".*                       ;
"/*"                         { BEGIN(COMMENT); }
<COMMENT>"*/"                { BEGIN(INITIAL); }
<COMMENT>\n                  ;
<COMMENT>.                   ;

"fn"                         { return FN; }
"let"                        { return LET; }
"mut"                        { return MUT; }
"if"                         { return IF; }
"else"                       { return ELSE; }
"for"                        { return FOR; }
"return"                     { return RETURN; }
"switch"                     { return SWITCH; }
"case"                       { return CASE; }
"default"                    { return DEFAULT; }
"break"                      { return BREAK; }
"continue"                   { return CONTINUE; }
"true"                       { return TRUE; }
"false"                      { return FALSE; }
"int"                        { return INT_TY; }
"bool"                       { return BOOL_TY; }
"->"                         { return ARROW; }
"=="                         { return EQ; }
"!="                         { return NE; }
"<="                         { return LE; }
">="                         { return GE; }
"&&"                         { return ANDAND; }
"||"                         { return OROR; }
[0-9]+                       { yylval.int_val = std::strtoll(yytext, nullptr, 10); return INT_LITERAL; }
[A-Za-z_][A-Za-z0-9_]*       { yylval.str = ::strdup(yytext); return IDENT; }

"{"                          { return '{'; }
"}"                          { return '}'; }
"\("                         { return '('; }
"\)"                         { return ')'; }
":"                          { return ':'; }
";"                          { return ';'; }
","                          { return ','; }
"="                          { return '='; }
"+"                          { return '+'; }
"-"                          { return '-'; }
"*"                          { return '*'; }
"/"                          { return '/'; }
"%"                          { return '%'; }
"!"                          { return '!'; }
"<"                          { return '<'; }
">"                          { return '>'; }

.                            { return yytext[0]; }

%%
