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
  point pos[2] = {{}};
  int c;
  int t;
  while ((c = fgetc(input)) != EOF)
    {
      t = !t;
      switch (c)
	{
	case '^': pos[t].y++; break;
	case '<': pos[t].x--; break;
	case '>': pos[t].x++; break;
	case 'v': pos[t].y--; break;
	}
      if (pos[t].x < min_pos.x) min_pos.x = pos[t].x;
      if (pos[t].y < min_pos.y) min_pos.y = pos[t].y;
      if (pos[t].x > max_pos.x) max_pos.x = pos[t].x;
      if (pos[t].y > max_pos.y) max_pos.y = pos[t].y;
    }
  pos[0].x = pos[1].x = -min_pos.x;
  pos[0].y = pos[1].y = -min_pos.y;
  int (*grid)[max_pos.y - min_pos.y + 1] = malloc(sizeof(int[max_pos.x - min_pos.x + 1][max_pos.y - min_pos.y + 1]));
  fseek(input, 0, SEEK_SET);
  int count = 0;
  t = 0;
  while ((c = fgetc(input)) != EOF)
    {
      t = !t;
      if (grid[pos[t].x][pos[t].y] == 0) count++;
      grid[pos[t].x][pos[t].y]++;
      switch (c)
	{
	case '^': pos[t].y++; break;
	case '<': pos[t].x--; break;
	case '>': pos[t].x++; break;
	case 'v': pos[t].y--; break;
	}
    }
  free(grid);
  
  printf("%d\n", count);
  
  fclose(input);
  return 0;
}
