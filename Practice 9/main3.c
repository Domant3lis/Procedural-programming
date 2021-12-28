// Domantas Keturakis © 2021
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	double x, y;
} Point;

typedef struct
{
	Point *data;
	int size;
} Stack;

void printPoint(Point p)
{
	printf("%lf %lf  ", p.x, p.y);
}

void initStack(Stack *stack)
{
	stack->data = NULL;
	stack->size = 0;
}

void printStack(Stack *stack)
{
	for (int i = 0; i < stack->size; ++i)
		printPoint(stack->data[i]);
}

int getStackSize(Stack *stack)
{
	return stack->size;
}

void push(Stack *stack, Point p)
{
	stack->data = realloc(stack->data, (stack->size + 1) * sizeof(Point));
	stack->data[stack->size] = p;
	stack->size += 1;
}

Point pop(Stack *stack)
{
	Point temp = stack->data[stack->size - 1];
	stack->data = realloc(stack->data, (stack->size - 1) * sizeof(Point));
	stack->size -= 1;
	return temp;
}

void destroyStack(Stack *stack)
{
	free(stack->data);
	stack->data = NULL;
	stack->size = 0;
}

Point top(Stack *stack)
{
	return stack->data[stack->size - 1];
}

int main()
{
	Stack foo;
	initStack(&foo);
	printStack(&foo);
	printf("STACK SIZE IS: %d\n", getStackSize(&foo));
	Point p;
	p.x = 1;
	p.y = 1;
	push(&foo, p);
	p.x = 2;
	p.y = 2;
	push(&foo, p);
	printf("POPED: ");
	printPoint(pop(&foo));
	printf("\n");
	p.x = 3;
	p.y = 3;
	push(&foo, p);
	printStack(&foo);
	printf("\nTOP:\n");
	printPoint(top(&foo));
	destroyStack(&foo);
	printStack(&foo);

	return 0;
}