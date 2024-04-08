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
		int min_r = 0;
		int min_g = 0;
		int min_b = 0;
		for (int i = 8; line[i]; i++)
		{
			char* tail;
			int num = strtol(line + i, &tail, 10);
			switch (tail[1])
			{
			case 'r': if (num > min_r) min_r = num; break;
			case 'g': if (num > min_g) min_g = num; break;
			case 'b': if (num > min_b) min_b = num; break;
			}
			while (!isdigit(line[i + 1]) && line[i + 1]) i++;
		}
		sum += min_r * min_g * min_b;
	}
	free(line);

	printf("%d\n", sum);

	fclose(input);
	return 0;
}
