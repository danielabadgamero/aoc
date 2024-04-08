#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t examine(int len, char* buf)
{
	size_t size = 0;
	for (int i = 0; i != len; i++)
	{
		if (buf[i] == '(')
		{
			char* tail;
			int sub_len = strtol(buf + i + 1, &tail, 10);
			int sub_times = strtol(tail + 1, NULL, 10);

			tail = strchr(buf + i, ')');
			i = tail - buf + sub_len;
			size += sub_times * examine(sub_len, tail + 1);
		}
		else size++;
	}
	return size;
}

int main()
{
	FILE* input = fopen("input", "r");

	char* buf = malloc(1);
	size_t n = 1;
	size_t size = (size_t)getline(&buf, &n, input);
	buf[--size] = 0;
	size = examine(size, buf);
	free(buf);

	printf("%ld\n", size);
	
	fclose(input);

	return 0;
}
