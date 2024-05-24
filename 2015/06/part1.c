#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lights[1000][1000] = {};

int main()
{
  FILE* input = fopen("input", "r");
  char* line = NULL;
  size_t line_size = 0;
  ssize_t n;
  while ((n = getline(&line, &line_size, input)) > 0)
    {
      int coords[4];
      char* tail = line;
      for (int i = 0; i != 4; i++)
	{
	  while (!isdigit(*tail)) tail++;
	  coords[i] = strtol(tail, &tail, 10);
	}
      
      if (strstr(line, "toggle"))
	{
	  for (int i = coords[0]; i <= coords[2]; i++)
	    for (int j = coords[1]; j <= coords[3]; j++)
	      lights[j][i] = !lights[j][i];
	}
      else if (strstr(line, "turn on"))
	{
	  for (int i = coords[0]; i <= coords[2]; i++)
	    for (int j = coords[1]; j <= coords[3]; j++)
	      lights[j][i] = 1;
	}
      else if (strstr(line, "turn off"))
	{
	  for (int i = coords[0]; i <= coords[2]; i++)
	    for (int j = coords[1]; j <= coords[3]; j++)
	      lights[j][i] = 0;
	}
    }
  free(line);

  int count = 0;
  for (int i = 0; i != 1000; i++)
    for (int j = 0; j != 1000; j++)
      count += lights[j][i];

  printf("%d\n", count);

  return 0;
}
