#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
  FILE* input = fopen("input", "r");
  char* data = NULL;
  size_t len = 0;
  ssize_t n = getline(&data, &len, input);

  int sum = 0;

  for (int i = 0; i < n; i++)
    if (data[i] == '-' || isdigit(data[i]))
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
