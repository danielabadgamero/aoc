#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
  FILE* input = fopen("input", "r");

  char* line = NULL;
  size_t line_size = 0;
  ssize_t n;

  int nice_count = 0;
  
  while ((n = getline(&line, &line_size, input)) != -1)
    {
      if (strstr(line, "ab") || strstr(line, "cd") || strstr(line, "pq") || strstr(line, "xy"))
	continue;
      int vowel_count = 0;
      for (int i = 0; i != n; i++)
	{
	  if (vowel_count >= 3) break;
	  if (line[i] == 'a' || line[i] == 'e' || line[i] == 'i' || line[i] == 'o' || line[i] == 'u')
	    vowel_count++;
	}
      if (vowel_count < 3) continue;
      for (int i = 0; i != n - 1; i++)
	if (line[i] == line[i + 1])
	  {
	    nice_count++;
	    break;
	  }
    }
  free(line);

  printf("%d\n", nice_count);
	
  return 0;
}
