#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

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
		num *= 10;
		for (ssize_t i = size - 1; i >= 0; i--)
			if (isdigit(line[i]))
			{
				num += line[i] - '0';
				break;
			}
		sum += num;
	}
	free(line);

	printf("%d\n", sum);

	fclose(input);
	return 0;
}
