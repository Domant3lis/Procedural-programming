// Domantas Keturakis © 2021
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int *data;
	int size;
} Stack;

void initStack(Stack *stack)
{
	stack->data = NULL;
	stack->size = 0;
}

void printStack(Stack *stack)
{
	for (int i = 0; i < stack->size; ++i)
		printf("%d ", stack->data[i]);
}

int getStackSize(Stack *stack)
{
	return stack->size;
}

void push(Stack *stack, int value)
{
	stack->data = realloc(stack->data, (stack->size + 1) * sizeof(int));
	stack->data[stack->size] = value;
	stack->size += 1;
}

int pop(Stack *stack)
{
	int temp = stack->data[stack->size - 1];
	stack->data = realloc(stack->data, (stack->size - 1) * sizeof(int));
	stack->size -= 1;
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
	Stack foo;
	initStack(&foo);
	printStack(&foo);
	printf("STACK SIZE IS: %d\n", getStackSize(&foo));
	push(&foo, 1);
	push(&foo, 2);
	printf("POPED: %d\n", pop(&foo));
	push(&foo, 3);
	printStack(&foo);
	printf("\nTOP: %d\n", top(&foo));
	destroyStack(&foo);
	printStack(&foo);

	return 0;
}