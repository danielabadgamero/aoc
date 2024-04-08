#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* numbers[] =
{
	"one", "two", "three", "four", "five",
	"six", "seven", "eight", "nine"
};

int main()
{
	FILE* input = fopen("input", "r");

	size_t n = 1;
	ssize_t size;
	char* line = malloc(n);
	int sum = 0;
	while ((size = getline(&line, &n, input)) > 0)
	{
		int num = 0;
		for (ssize_t i = 0; i != size; i++)
			if (isdigit(line[i]))
			{
				num = line[i] - '0';
				break;
			}
			else
			{
				int digit = 0;
				for (int d = 0; d != 9 && digit == 0; d++)
					if (strncmp(line + i, numbers[d], strlen(numbers[d])) == 0)
						digit = d + 1;
				if (digit)
				{
					num = digit;
					break;
				}
			}
		num *= 10;
		for (ssize_t i = size - 1; i >= 0; i--)
			if (isdigit(line[i]))
			{
				num += line[i] - '0';
				break;
			}
			else
			{
				int digit = 0;
				for (int d = 0; d != 9 && digit == 0; d++)
					if (strncmp(line + i, numbers[d], strlen(numbers[d])) == 0)
						digit = d + 1;
				if (digit)
				{
					num += digit;
					break;
				}
			}
		sum += num;
		printf("%d\n", num);
	}
	free(line);

	printf("%d\n", sum);

	fclose(input);
	return 0;
}
