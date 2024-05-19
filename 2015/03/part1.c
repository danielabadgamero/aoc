#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct point
{
  int x;
  int y;
} point;

int main()
{
  FILE* input = fopen("input", "r");
  point min_pos = { INT_MAX, INT_MAX };
  point max_pos = { INT_MIN, INT_MIN };
  point pos = { 0, 0 };
  int c;
  while ((c = fgetc(input)) != EOF)
    {
      switch (c)
	{
	case '^': pos.y++; break;
	case '<': pos.x--; break;
	case '>': pos.x++; break;
	case 'v': pos.y--; break;
	}
      if (pos.x < min_pos.x) min_pos.x = pos.x;
      if (pos.y < min_pos.y) min_pos.y = pos.y;
      if (pos.x > max_pos.x) max_pos.x = pos.x;
      if (pos.y > max_pos.y) max_pos.y = pos.y;
    }
  pos.x = -min_pos.x;
  pos.y = -min_pos.y;
  int (*grid)[max_pos.y - min_pos.y + 1] = malloc(sizeof(int[max_pos.x - min_pos.x + 1][max_pos.y - min_pos.y + 1]));
  fseek(input, 0, SEEK_SET);
  int count = 0;
  while ((c = fgetc(input)) != EOF)
    {
      if (grid[pos.x][pos.y] == 0) count++;
      grid[pos.x][pos.y]++;
      switch (c)
	{
	case '^': pos.y++; break;
	case '<': pos.x--; break;
	case '>': pos.x++; break;
	case 'v': pos.y--; break;
	}
    }
  free(grid);
  
  printf("%d\n", count);
  
  fclose(input);
  return 0;
}
