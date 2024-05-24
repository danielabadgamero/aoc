#include <stdio.h>
#include <string.h>
#include <stdlib.h>

size_t replace(char** line, size_t n)
{
  char* buf = malloc(1);
  size_t j = 0;
  int count = 0;
  char saved = (*line)[0];
  for (size_t i = 0; i != n + 1; i++)
    {
      if (saved && saved != (*line)[i])
	{
	  buf = realloc(buf, j + 3);
	  buf[j++] = count + '0';
	  count = 1;
	  buf[j++] = saved;
	  saved = (*line)[i];
	}
      else count++;
    }
  *line = realloc(*line, j + 1);
  strcpy(*line, buf);
  free(buf);
  return j;
}

int main()
{
  FILE* input = fopen("input", "r");
  char* line = NULL;
  size_t len = 0;
  size_t n = (size_t)getline(&line, &len, input);
  line[n - 1] = 0;

  for (int i = 0; i != 50; i++)
      n = replace(&line, n);

  printf("%ld\n", strlen(line));
  free(line);

  return 0;
}
