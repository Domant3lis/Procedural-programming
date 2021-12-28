// Domantas Keturakis © 2021
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int *data;
	size_t size;
} Stack;

void initStack(Stack *stack)
{
	stack->data = NULL;
	stack->size = 0;
}

void printStack(Stack *stack)
{
	for (size_t i = 0; i < stack->size; ++i)
		printf("%d ", stack->data[i]);
}

int getStackSize(Stack *stack)
{
	return stack->size;
}

void push(Stack *stack, int value)
{
	stack->data = realloc(stack->data, stack->size + 1);
	stack->data[stack->size - 1] = value;
}

int pop(Stack *stack)
{
	int temp = stack->data[stack->size - 1];
	stack->data = realloc(stack->data, stack->size - 1);
	return temp;
}

void destroyStack(Stack *stack)
{
	free(stack->data);
	stack->data = NULL;
	stack->size = 0;
}

int top(Stack *stack)
{
	return stack->data[stack->size - 1];
}

int main()
{

	return 0;
}