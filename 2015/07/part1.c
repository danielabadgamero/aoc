#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum op_t
  {
    NONE,
    RSHIFT,
    LSHIFT,
    OR,
    AND,
    NOT
  };

typedef struct wire_t
{
  unsigned short signal;
  int solved;
  char id[3];
  enum op_t op;
  char in1[3];
  unsigned short im1;
  char in2[3];
  unsigned short im2;
} wire_t;

wire_t* wires;
int num_wires;

int count_spaces(const char* line)
{
  int num_spaces = 0;
  for (int i = 0; line[i]; i++)
    if (line[i] == ' ') num_spaces++;
  return num_spaces;
}

unsigned short solve(const char* id)
{
  wire_t* wire = wires;
  while (strcmp(wire->id, id)) wire++;
  if (wire->solved) return wire->signal;
  else switch(wire->op)
	 {
	 case NONE:
	   wire->signal = solve(wire->in1);
	   break;
	 case RSHIFT:
	   wire->signal = (*wire->in1 ? solve(wire->in1) : wire->im1) >> (*wire->in2 ? solve(wire->in2) : wire->im2);
	   break;
	 case LSHIFT:
	   wire->signal = (*wire->in1 ? solve(wire->in1) : wire->im1) << (*wire->in2 ? solve(wire->in2) : wire->im2);
	   break;
	 case OR:
	   wire->signal = (*wire->in1 ? solve(wire->in1) : wire->im1) | (*wire->in2 ? solve(wire->in2) : wire->im2);
	   break;
	 case AND:
	   wire->signal = (*wire->in1 ? solve(wire->in1) : wire->im1) & (*wire->in2 ? solve(wire->in2) : wire->im2);
	   break;
	 case NOT:
	   wire->signal = ~(*wire->in1 ? solve(wire->in1) : wire->im1);
	   break;
	 }
  wire->solved = 1;
  return wire->signal;
}

int main()
{
  FILE* input = fopen("input", "r");
  char* line = NULL;
  size_t line_size = 0;
  ssize_t n;

  wires = malloc(1 * sizeof(wire_t));
  num_wires = 1;

  while ((n = getline(&line, &line_size, input)) > 0)
    {
      wires[num_wires - 1].solved = 0;
      wires[num_wires - 1].in1[0] = 0;
      wires[num_wires - 1].in2[0] = 0;
      if (strstr(line, "NOT"))
	wires[num_wires - 1].op = NOT;
      else if (strstr(line, "RSHIFT"))
	wires[num_wires - 1].op = RSHIFT;
      else if (strstr(line, "LSHIFT"))
	wires[num_wires - 1].op = LSHIFT;
      else if (strstr(line, "AND"))
	wires[num_wires - 1].op = AND;
      else if (strstr(line, "OR"))
	wires[num_wires - 1].op = OR;
      else
	wires[num_wires - 1].op = NONE;

      char* buf = malloc(strlen(line) + 1);
      strcpy(buf, line);
      char* i = strtok(buf, " ");
      switch (count_spaces(line))
	{
	case 2:
	  if (isdigit(*i))
	    {
	      wires[num_wires - 1].signal = strtol(i, NULL, 10);
	      wires[num_wires - 1].solved = 1;
	    }
	  else strcpy(wires[num_wires - 1].in1, i);
	  break;
	case 3:
	  i = strtok(NULL, " ");
	  strcpy(wires[num_wires - 1].in1, i);
	  break;
	case 4:
	  if (isdigit(*i))
	    wires[num_wires - 1].im1 = strtol(i, NULL, 10);
	  else strcpy(wires[num_wires - 1].in1, i);
	  i = strtok(NULL, " ");
	  i = strtok(NULL, " ");

	  if (isdigit(*i))
	    wires[num_wires - 1].im2 = strtol(i, NULL, 10);
	  else strcpy(wires[num_wires - 1].in2, i);
	  break;
	}
      i = strtok(NULL, " ->\n");
      strcpy(wires[num_wires - 1].id, i);
      free(buf);

      wires = realloc(wires, (++num_wires) * sizeof(wire_t));
    }
  free(line);
  free(wires);


  printf("%d\n", solve("a"));

  return 0;
}
