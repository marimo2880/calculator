#include <stdio.h>

enum TokenType
{
  NAME, CONST,
  PLUS, MINUS, TIMES, DIVIDE, EQUAL,
  LEFT_BRACKET, RIGHT_BRACKET
};

union TokenValue
{
  char* name;
  double number;
};

struct Token
{
  TokenType type;
  TokenValue value;
};

int main(int argc, char const *argv[])
{
  TokenValue v;
  v.number = 8;
  Token a = { CONST, v };
  if(a.type == CONST) {
    printf("%f\n", a.value.number);
  } else if(a.type == NAME) {
    printf("%s\n", a.value.name);
  } else {
    printf("other\n");
  }

  return 0;
}