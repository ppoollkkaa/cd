//for.l
%{
#include "y.tab.h"
%}

%%

for return FOR;

[a-zA-Z_][a-zA-Z0-9_]* return ID;

[0-9]+ return NUM;

"++" return INC;
"--" return DEC;

"<=" return LE;
">=" return GE;
"==" return EQ;
"!=" return NE;

[<>=;(){}+*\-/] return yytext[0];

[ \t\n] ;

. return yytext[0];

%%

int yywrap()
{
    return 1;
}

//for.y
%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(char *s);
%}

%token FOR ID NUM INC DEC LE GE EQ NE

%%

S : FOR '(' ASSIGN ';' COND ';' UPDATE ')' '{' '}'
    {
        printf("Valid FOR Statement\n");
    }
    ;

ASSIGN : ID '=' NUM
       | ID '=' ID
       ;

COND : ID '<' NUM
     | ID '>' NUM
     | ID LE NUM
     | ID GE NUM
     | ID EQ NUM
     | ID NE NUM
     ;

UPDATE : ID INC
       | ID DEC
       | ID '=' ID '+' NUM
       | ID '=' ID '-' NUM
       ;

%%

void yyerror(char *s)
{
    printf("Invalid FOR Statement\n");
}

int main()
{
    printf("Enter FOR Statement: ");
    yyparse();
    return 0;
}