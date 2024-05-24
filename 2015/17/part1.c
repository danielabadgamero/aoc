#include <stdio.h>
#include <stdlib.h>

int main()
{
  FILE* input = fopen("input", "r");
  int capacities[20];

  for (int i = 0; i != 20; i++)
    fscanf(input, "%d", capacities + i);
  
  int count = 0;
  for (size_t i = 0; i != 1ul << 20; i++)
    {
      int vol = 0;
      for (size_t b = 0; b != 20; b++)
	if (i & (1 << b)) vol += capacities[b];
      if (vol == 150)
	count++;
    }
  
  printf("%d\n", count);

  return 0;
}
