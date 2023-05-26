#include "monty.h"
monty_state state;

/**
* main - the monty program
* @argc: num of args
* @argv: monty file
* Return: 0 on success
*/
int main(int argc, char *argv[])
{
	char *data;
	FILE *file;
	size_t size = 0;
	ssize_t get_line = 1;
	stack_t *stack = NULL;
	unsigned int index = 0;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	file = fopen(argv[1], "r");
	state.file = file;
	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	while (get_line > 0)
	{
		data = NULL;
		get_line = getline(&data, &size, file);
		state.data = data;
		index++;
		if (get_line > 0)
		{
			execute(data, &stack, index, file);
		}
		free(data);
	}
	free_stack(stack);
	fclose(file);
return (0);
}
