// ast.l
%{
#include "y.tab.h"
#include <stdlib.h>
%}

%%

[0-9]+ {
    yylval.num = atoi(yytext);
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

//ast.y
%{
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    char op;
    int val;
    struct node *left;
    struct node *right;
} node;

node *mknode(char op, int val, node *left, node *right)
{
    node *temp = (node *)malloc(sizeof(node));

    temp->op = op;
    temp->val = val;
    temp->left = left;
    temp->right = right;

    return temp;
}

void preorder(node *root)
{
    if (root)
    {
        if (root->op == 'N')
            printf("%d ", root->val);
        else
            printf("%c ", root->op);

        preorder(root->left);
        preorder(root->right);
    }
}

int yylex();
void yyerror(char *s);
%}

%union
{
    int num;
    node *ptr;
}

%token <num> NUM
%type <ptr> E

%left '+' '-'
%left '*' '/'

%%

S : E '\n'
    {
        printf("Preorder AST: ");
        preorder($1);
        printf("\n");
    }
    ;

E : E '+' E   { $$ = mknode('+', 0, $1, $3); }
  | E '-' E   { $$ = mknode('-', 0, $1, $3); }
  | E '*' E   { $$ = mknode('*', 0, $1, $3); }
  | E '/' E   { $$ = mknode('/', 0, $1, $3); }
  | '(' E ')' { $$ = $2; }
  | NUM       { $$ = mknode('N', $1, NULL, NULL); }
  ;

%%

void yyerror(char *s)
{
    printf("Invalid Expression\n");
}

int main()
{
    printf("Enter Expression: ");
    yyparse();

    return 0;
}
