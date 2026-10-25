#include <stdio.h>
#include <string.h>
char input[100];
int pos = 0;
void E();
void Eprime();
void T();
void Tprime();
void F();
void match(char symbol)
{
if(input[pos] == symbol)
{
pos++;
}
else
{
printf("Error: Expected %c\n", symbol);
}
}


void E()
{
T();
Eprime();
}
void Eprime()
{
if(input[pos] == '+')
{
match('+');
T();
Eprime();
}
}
void T()
{
F();
Tprime();
}
void Tprime()
{
if(input[pos] == '*')
{
match('*');
F();
Tprime();
}
}
void F()
{
if(input[pos] == 'i')
{
match('i');
}
else if(input[pos] == '(')
{
match('(');
E();
match(')');
}
else
{
printf("Error: Invalid symbol %c\n", input[pos]);
}
}
int main()
{
printf("Enter expression (use i for identifier): ");


scanf("%s", input);
strcat(input, "$");
E();
if(input[pos] == '$')
printf("Expression Accepted\n");
else
printf("Expression Rejected\n");
return 0;
}