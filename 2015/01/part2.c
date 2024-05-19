#include <stdio.h>

int main()
{
  FILE* input = fopen("input", "r");
  int floor = 0;
  int c;
  while ((c = fgetc(input)) != EOF)
    {
      if (c == '(') floor++;
      else if (c == ')') floor--;
      if (floor < 0) break;
    }
  
  printf("%ld\n", ftell(input));
  
  fclose(input);
  return 0;
}
