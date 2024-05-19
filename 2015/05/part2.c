#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main()
{
  FILE* input = fopen("input", "r");

  char* line = malloc(1);
  size_t line_size = 1;
  ssize_t n;

  int nice_count = 0;
  
  while ((n = getline(&line, &line_size, input)) != -1)
    {
      int nice1 = 0;
      for (int i = 0; i != n - 1; i++)
	{
	  const char pair[] = { line[i], line[i + 1] };
	  if (abs((int)(strstr(line, pair) - line) - i) > 1)
	    {
	      nice1 = 1;
	      break;
	    }
	}
      int nice2 = 0;
      for (int i = 0; i != n - 2; i++)
	if (line[i] == line[i + 2])
	  {
	    nice2 = 1;
	    break;
	  }
      nice_count += nice1 & nice2;
    }
  
  printf("%d\n", nice_count);
  
  return 0;
}
