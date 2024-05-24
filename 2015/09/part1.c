#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

int next_permutation(int* arr, int size)
{
  int K = -1;
  for (int k = 0; k < size - 1; k++)
    if (arr[k] < arr[k + 1]) K = k;
  if (K < 0) return 0;

  int I = -1;
  for (int i = 0; i < size; i++)
    if (arr[K] < arr[i]) I = i;

  {
    int temp = arr[I];
    arr[I] = arr[K];
    arr[K] = temp;
  }

  {
    int temp_size = size - (K + 1);
    int* temp = malloc(temp_size * sizeof(int));
    for (int i = 0; i != temp_size; i++)
      temp[i] = arr[size - i - 1];
    memcpy(arr + K + 1, temp, temp_size * sizeof(int));
    free(temp);
  }

  return 1;
}

int distances[8][8];

int get_distance(int* arr, int size)
{
  int distance = 0;
  for (int i = 0; i < size - 1; i++)
    distance += distances[arr[i]][arr[i + 1]];
  return distance;
}

int main()
{
  FILE* input = fopen("input", "r");
  char* line = NULL;
  char lines[28][34];
  size_t len = 0;
  ssize_t n;
  int line_index = 0;
  while ((n = getline(&line, &len, input)) > 0)
    strcpy(lines[line_index++], line);
  free(line);

  for (int i = 0; i != 28; i++)
    lines[i][strlen(lines[i]) - 1] = 0;

  for (int i = 0; i != 8; i++)
    for (int j = 0; j != 8; j++)
      {
	if (i == j) continue;

	int s,d;
	if (i < j)
	  {
	    s = i;
	    d = j;
	  }
	else
	  {
	    s = j;
	    d = i;
	  }

	int source_offset = s * (15 - s) / 2;
	
	char buf[34];
	strcpy(buf, lines[source_offset + d - (s + 1)]);
	strtok(buf, "=");
	int dist = strtol(strtok(NULL, "="), NULL, 10);
	distances[s][d] = dist;
	distances[d][s] = dist;
      }

  int order[8];
  for (int i = 0; i != 8; i++) order[i] = i;

  int min_distance = INT_MAX;
  do
  {
    int distance = get_distance(order, 8);
    if (distance < min_distance) min_distance = distance;
  }
  while (next_permutation(order, 8));

  printf("%d\n", min_distance);

  return 0;
}
