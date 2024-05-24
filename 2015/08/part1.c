#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  FILE* input = fopen("input", "r");
  char* line = NULL;
  size_t line_size = 0;
  ssize_t n;
  int diff = 0;
  while ((n = getline(&line, &line_size, input)) > 0)
    {
      diff += 2;
      for (int i = 0; i != n; i++)
	if (line[i] == '\\')
	  switch (line[i + 1])
	    {
	    case '\\':
	    case '"':
	      diff++;
	      i++;
	      break;
	    case 'x':
	      diff += 3;
	      i += 3;
	      break;
	    }
    }
  free(line);

  printf("%d\n", diff);

  return 0;
}
