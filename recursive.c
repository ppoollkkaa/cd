#include <stdio.h>
#include <string.h>
char input[100];
int pos = 0;

//declare all nonterminals' functions
void E();
void Eprime();
void T();
void Tprime();
void F();

/*
E  → TE'
E' → +TE' | ε
T  → FT'
T' → *FT' | ε
F  → (E) | i
*/
void match(char symbol){
  if (input[pos] == symbol)
  {
    pos++;
  }
  else
  {
    printf("Error: Expected %c\n", symbol);
  }
}
//E->T'
void E(){
  T();
  Eprime();
}
//E'->+TE'
void Eprime(){
  if (input[pos] == '+') // IF for epsilon grammar only
  {
    match('+');
    T();
    Eprime();
  }
}

void T(){
  F();
  Tprime();
}

void Tprime(){
  if (input[pos] == '*')
  {
    match('*');
    F();
    Tprime();
  }
}
void F(){
  if (input[pos] == 'i')
  {
    match('i');
  }
  else if (input[pos] == '(')
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
  if (input[pos] == '$')
    printf("Expression Accepted\n");
  else
    printf("Expression Rejected\n");
  return 0;
}