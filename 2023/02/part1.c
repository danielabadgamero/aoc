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
		int possible = 1;
		for (int i = 8; line[i]; i++)
		{
			char* tail;
			int num = strtol(line + i, &tail, 10);
			switch (tail[1])
			{
			case 'r': if (num > 12) possible = 0; break;
			case 'g': if (num > 13) possible = 0; break;
			case 'b': if (num > 14) possible = 0; break;
			}
			while (!isdigit(line[i + 1]) && line[i + 1]) i++;
		}
		if (possible) sum += strtol(line + 5, NULL, 10);
	}
	free(line);

	printf("%d\n", sum);

	fclose(input);
	return 0;
}
