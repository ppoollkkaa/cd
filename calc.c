/* ---------- calc.l (LEX) ---------- */

%{
#include "y.tab.h"
#include <stdlib.h>
%}

%%

[0-9]+ {
    yylval = atoi(yytext);
    return NUM;
}

[ \t] ;
\n return '\n';

. return yytext[0];

%%

int yywrap()
{
    return 1;
}


/* ---------- calc.y (YACC) ---------- */

%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(char *s);
%}

%token NUM

%left '+' '-'
%left '*' '/'

%%

S : E '\n'
    {
        printf("Result = %d\n", $1);
    }
    ;

E : E '+' E   { $$ = $1 + $3; }
  | E '-' E   { $$ = $1 - $3; }
  | E '*' E   { $$ = $1 * $3; }
  | E '/' E   { $$ = $1 / $3; }
  | '(' E ')' { $$ = $2; }
  | NUM       { $$ = $1; }
  ;

%%

void yyerror(char *s)
{
    printf("Invalid Expression\n");
}

int main()
{
    printf("Enter Arithmetic Expression: ");
    yyparse();
    return 0;
}

/*
yacc -d calc.y
lex calc.l
gcc lex.yy.c y.tab.c -o calc -ll
./calc
*/