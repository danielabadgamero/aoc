#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int values[9][9];

int calculate_happiness(int* arr, size_t size)
{
  int happiness = 0;

  for (size_t i = 0; i != size; i++)
    {
      happiness += values[arr[i]][arr[(i + 1) % size]];
      happiness += values[arr[(i + 1) % size]][arr[i]];
    }
  
  return happiness;
}

int main()
{
  FILE* input = fopen("input", "r");
  char* line = NULL;
  size_t len = 0;
  ssize_t n;
  int table[9];
  for (int i = 0; i != 9; i++) table[i] = i;
  int i = 0;
  int j = 0;
  while ((n = getline(&line, &len, input)) > 0)
    {
      if (j == 8)
	{
	  j = 0;
	  i++;
	}
      if (i == j) j++;
      if (j == 8) break;
      int number_index = 0;
      while (!isdigit(line[number_index])) number_index++;
      values[i][j] = strtol(line + number_index, NULL, 10);
      if (strstr(line, "lose") != NULL) values[i][j] *= -1;
      j++;
    }
  free(line);

  for (i = 0; i != 9; i++)
    {
      values[8][i] = 0;
      values[i][8] = 0;
    }

  int max_happiness = 0;
  do
    {
      int happiness = calculate_happiness(table, 9);
      if (happiness > max_happiness) max_happiness = happiness;
    }
  while (next_permutation(table, 9));

  printf("%d\n", max_happiness);

  return 0;
}
