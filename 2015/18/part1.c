#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GRID_SIZE 100

void step(int dst[GRID_SIZE][GRID_SIZE], int src[GRID_SIZE][GRID_SIZE])
{
  for (int i = 0; i != GRID_SIZE; i++)
    for (int j = 0; j != GRID_SIZE; j++)
      {
	int neighbours = 0;
	for (int y = j - 1; y != j + 2; y++)
	  for (int x = i - 1; x != i + 2; x++)
	    if (y == j && x == i) continue;
	    else if (x < 0 || y < 0 || x > GRID_SIZE - 1 || y > GRID_SIZE - 1) continue;
	    else neighbours += src[x][y];
	if (src[i][j])
	  dst[i][j] = neighbours == 2 || neighbours == 3;
	else
	  dst[i][j] = neighbours == 3;
      }
}

int main()
{
  FILE* input = fopen("input", "r");
  char* line = NULL;
  size_t len = 0;
  int lights[GRID_SIZE][GRID_SIZE];
  int row = 0;
  while (getline(&line, &len, input) > 0)
    {
      for (int i = 0; i != GRID_SIZE; i++)
	lights[row][i] = line[i] == '#';
      row++;
    }
  free(line);

  for (int i = 0; i != GRID_SIZE; i++)
    {
      int buf[GRID_SIZE][GRID_SIZE];
      step(buf, lights);
      for (int j = 0; j != GRID_SIZE; j++)
	memcpy(lights[j], buf[j], GRID_SIZE * sizeof(int));
    }

  int count = 0;
  for (int i = 0; i != GRID_SIZE; i++)
    for (int j = 0; j != GRID_SIZE; j++)
      count += lights[j][i];

  printf("%d\n", count);

  return 0;
}
