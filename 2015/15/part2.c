#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void next_num(char* line, int* index)
{
  while (!isdigit(line[*index]) && line[*index] != '-') (*index)++;
}

int main()
{
  FILE* input = fopen("input", "r");
  char* line = NULL;
  size_t len = 0;
  ssize_t n;
  int i[4][5];
  int i_index = 0;
  while ((n = getline(&line, &len, input)) > 0)
    {
      int num_index = 0;
      for (int j = 0; j != 5; j++)
	{
	  next_num(line, &num_index);
	  i[i_index][j] = strtol(line + num_index, NULL, 10);
	  num_index += 3;
	}
      i_index++;
    }
  free(line);

  int max_score = 0;
  
  for (int a = 1; a != 98; a++)
    for (int b = 1; b != 98; b++)
      for (int c = 1; c != 98; c++)
	for (int d = 1; d != 98; d++)
	  if (a + b + c + d != 100) continue;
	  else
	    {
	      if (a * i[0][4] + b * i[1][4] + c * i[2][4] + d * i[3][4] != 500) continue;
	      int score = 1;
	      for (int j = 0; j != 4; j++)
		{
		  int ingredient = a * i[0][j] + b * i[1][j] +
		      c * i[2][j] + d * i[3][j];
		  if (ingredient < 0) ingredient = 0;
		  score *= ingredient;
		};
	      if (score > max_score) max_score = score;
	    }
  
  printf("%d\n", max_score);
  
  return 0;
}
