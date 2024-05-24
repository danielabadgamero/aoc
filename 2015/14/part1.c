#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct reindeer_t
{
  int speed;
  int flight_time;
  int resting_time;
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
      r_index++;
    }
  free(line);

  double max_speed = 0;
  int fastest;
  for (int r = 0; r != 9; r++)
    {
      double mean_speed = (double)(r_vec[r].speed * r_vec[r].flight_time) / (double)(r_vec[r].resting_time + r_vec[r].flight_time);
      if (mean_speed > max_speed) (max_speed = mean_speed), (fastest = r);
    }
  
  const int time = 2503;
  int distance = r_vec[fastest].flight_time * r_vec[fastest].speed * (1 + (time - (time % (r_vec[fastest].flight_time + r_vec[fastest].resting_time))) / (r_vec[fastest].flight_time + r_vec[fastest].resting_time));
  
  printf("%d\n", distance);
  
  return 0;
}
