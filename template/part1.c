#include <stdio.h>

int main()
{
	FILE* input = fopen("input", "r");
	char* line = NULL;
	size_t len = 0;
	while (getline(&line, &len, input) >= 0)
	{
	}
	free(line);

	return 0;
}
