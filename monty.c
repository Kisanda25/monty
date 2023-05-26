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
			handler(data, &stack, index, file);
		}
		free(data);
	}
	free_stack(stack);
	fclose(file);
return (0);
}

/**
 * free_stack - Frees the memory of a doubly linked list-based stack.
 * @head: Pointer to the head node of the stack.
 *
 * This function traverses a doubly linked list stack and frees the memory
 * allocated for each node in the stack. It starts from the head node and
 * iterates through the list, deallocating the memory for each node until the
 * end of the stack is reached. After freeing all nodes, the head pointer is
 * set to NULL to indicate an empty stack.
 */
void free_stack(stack_t *head)
{
	stack_t *current = head;

	while (current != NULL)
{
	stack_t *temp = current;

	current = current->next;
	free(temp);
	}
}

/**
* handler - handles the opcode
* @stack: head linked list - stack
* @index: index
* @file: poiner to monty file
* @data: data
* Return: no return
*/
int handler(char *data, stack_t **stack, unsigned int index, FILE *file)
{
	instruction_t opst[] = {
				{"push", f_push}, {"pall", f_pall}, {"pint", f_pint},
				{"pop", f_pop}
				{"swap", f_swap},
				{"add", f_add},
				{"nop", f_nop}
				};
	unsigned int i = 0;
	char *op;

	op = strtok(data, " \n\t");
	if (op && op[0] == '#')
		return (0);
	state.arg = strtok(NULL, " \n\t");
	while (opst[i].opcode && op)
	{
		if (strcmp(op, opst[i].opcode) == 0)
		{	opst[i].f(stack, index);
			return (0);
		}
		i++;
	}
	if (op && opst[i].opcode == NULL)
	{ fprintf(stderr, "L%d: unknown instruction %s\n", counter, op);
		fclose(file);
		free(data);
		free_stack(*stack);
		exit(EXIT_FAILURE); }
	return (1);
}
