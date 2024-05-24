#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int valid(char* pass, size_t len)
{
  int straight = 0;
  for (size_t i = 0; i != len - 2; i++)
    if (pass[i] + 1 == pass[i + 1] && pass[i] + 2 == pass[i + 2])
      {
	straight = 1;
	break;
      }
  if (!straight) return 0;
  
  if (strchr(pass, 'i') != NULL) return 0;
  if (strchr(pass, 'o') != NULL) return 0;
  if (strchr(pass, 'l') != NULL) return 0;

  int first_pair = 0;
  for (size_t i = 0; i < len - 1; i++)
    if (pass[i] == pass[i + 1])
      {
	if (first_pair) return 1;
	else (first_pair = 1), i++;
      }
  return 0;
}

void inc(char** pass, size_t len)
{
  for (size_t i = len - 1; i < len; i--)
    if ((*pass)[i] < 'z')
      {
	(*pass)[i]++;
	break;
      }
    else (*pass)[i] = 'a';
  
  for (size_t i = 0; i != len; i++)
    if ((*pass)[i] == 'i' || (*pass)[i] == 'o' || (*pass)[i] == 'l')
      {
	(*pass)[i]++;
	for (size_t j = i + 1; j != len; j++)
	  (*pass)[j] = 'a';
      }
}

int main()
{
  FILE* input = fopen("input", "r");
  char* pass = NULL;
  size_t len = 0;
  ssize_t n = getline(&pass, &len, input);
  pass[n - 1] = 0;

  do inc(&pass, 8);
  while (!valid(pass, 8));
  do inc(&pass, 8);
  while (!valid(pass, 8));

  puts(pass);

  return 0;
}
