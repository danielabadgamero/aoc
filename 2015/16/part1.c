#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int match(const char* item, int num, const char* line)
{
  const char* info = strstr(line, item);
  if (!info) return 1;
  int index = info - line;
  while (!isdigit(line[index])) index++;
  return num == strtol(line + index, NULL, 10);
}

const char* items[10] =
  {
    "children",
    "cats",
    "samoyeds",
    "pomeranians",
    "akitas",
    "vizslas",
    "goldfish",
    "trees",
    "cars",
    "perfumes"
  };

int count[10] = { 3, 7, 2, 3, 0, 0, 5, 3, 2, 1 };

int main()
{
  FILE* input = fopen("input", "r");
  char* line = NULL;
  size_t len = 0;
  int counter = 0;
  while (getline(&line, &len, input) > 0)
    {
      counter++;
      int matches = 1;
      for (int i = 0; i != 10; i++)
	matches *= match(items[i], count[i], line);
      if (matches) break;
    }
  free(line);

  printf("%d\n", counter);

  return 0;
}
