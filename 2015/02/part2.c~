#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int comp_int(const void* a, const void* b)
{
	return *((int*)a) - *((int*)b);
}

void get_sides(int* arr, char* headptr)
{
	char* tailptr = NULL;
	arr[0] = strtol(headptr, &tailptr, 10);
	headptr = tailptr + 1;
	arr[1] = strtol(headptr, &tailptr, 10);
	headptr = tailptr + 1;
	arr[2] = strtol(headptr, &tailptr, 10);
	qsort(arr, 3, sizeof(int), comp_int);
}

int main()
{
	FILE* input = fopen("input", "r");
	char* line = NULL;
	size_t len = 0;
	int total_area = 0;
	while (getline(&line, &len, input) >= 0)
	{
		int sides[3];
		get_sides(sides, line);
		total_area += 3 * sides[0] * sides[1] +
			2 * sides[0] * sides[2] +
			2 * sides[1] * sides[2];

	}
	free(line);

	printf("%d\n", total_area);

	fclose(input);
	return 0;
}
