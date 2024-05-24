#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct reindeer_t
{
  int speed;
  int flight_time;
  int resting_time;
  int flying;
  int chrono;
  int distance;
  int points;
} reindeer_t;

void next_num(char* line, int* index)
{
  while (!isdigit(line[*index])) (*index)++;
}

int main()
{
  FILE* input = fopen("input", "r");
  char* line = NULL;
  size_t len = 0;
  ssize_t n;
  reindeer_t r_vec[9];
  int r_index = 0;
  while ((n = getline(&line, &len, input)) > 0)
    {
      int num_index = 0;
      next_num(line, &num_index);
      r_vec[r_index].speed = strtol(line + num_index, NULL, 10);
      num_index += 5;
      next_num(line, &num_index);
      r_vec[r_index].flight_time = strtol(line + num_index, NULL, 10);
      num_index += 5;
      next_num(line, &num_index);
      r_vec[r_index].resting_time = strtol(line + num_index, NULL, 10);
      r_vec[r_index].flying = 1;
      r_vec[r_index].chrono = 0;
      r_vec[r_index].distance = 0;
      r_vec[r_index].points = 0;
      r_index++;
    }
  
  for (int s = 0; s <= 2503; s++)
    {
      int max_dist = 0;
      for (int i = 0; i != 9; i++)
	{
	r_vec[i].chrono++;
	  if (r_vec[i].flying)
	    {
	      r_vec[i].distance += r_vec[i].speed;
	      if (r_vec[i].chrono == r_vec[i].flight_time)
		{
		  r_vec[i].chrono = 0;
		  r_vec[i].flying = 0;
		}
	    }
	  else if (r_vec[i].chrono == r_vec[i].resting_time)
	    {
	      r_vec[i].chrono = 0;
	      r_vec[i].flying = 1;
	    }
	  if (r_vec[i].distance > max_dist) max_dist = r_vec[i].distance;
	}
      for (int i = 0; i != 9; i++)
	if (r_vec[i].distance == max_dist) r_vec[i].points++;
    }
  
  int max_points = 0;
  for (int i = 0; i != 9; i++)
    if (r_vec[i].points > max_points) max_points = r_vec[i].points;
  
  printf("%d\n", max_points);
  
  return 0;
}
