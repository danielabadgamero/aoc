#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  FILE* input = fopen("input", "r");
  char* data = NULL;
  size_t len = 0;
  size_t n = (size_t)getline(&data, &len, input);

  int sum = 0;
  for (size_t i = 0; i != n; i++)
    if (data[i] == '{')
      {
	int depth = 0;
	for (size_t j = i; j != n; j++)
	  {
	    if (data[j] == '{' || data[j] == '[') depth++;
	    else if (data[j] == '}' || data[j] == ']') depth--;
	    if (depth > 1) continue;
	    else if (depth == 0) break;
	    if (strncmp(data + j, "red", 3) == 0)
	      {
		while (depth >= 1)
		  {
		    j++;
		    if (data[j] == '{' || data[j] == '[') depth++;
		    else if (data[j] == '}' || data[j] == ']') depth--;
		  }
		i = j;
		break;
	      }
	  }
      }
    else if (data[i] == '-' || isdigit(data[i]))
      {
	int num = strtol(data + i, NULL, 10);
	if (num != 0) i += log10(abs(num));
	if (num < 0) i++;
	sum += num;
      }

  free(data);
  printf("%d\n", sum);
  
  return 0;
}
