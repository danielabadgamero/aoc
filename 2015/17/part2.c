#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int main()
{
  FILE* input = fopen("input", "r");
  int capacities[20];
  for (int i = 0; i != 20; i++)
    fscanf(input, "%d", capacities + i);

  int min = INT_MAX;
  int minimum[20] = {};
  for (size_t i = 0; i != 1ul << 20; i++)
    {
      int vol = 0;
      int count = 0;
      for (size_t b = 0; b != 20; b++)
	if (i & (1 << b)) (vol += capacities[b]), count++;
      if (vol == 150)
	{
	  if (count < min) min = count;
	  minimum[count]++;
	}
    }
  
  printf("%d\n", minimum[min]);
  
  return 0;
}
