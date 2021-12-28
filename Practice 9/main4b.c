// Domantas Keturakis © 2021
#include <stdio.h>
#include <stdlib.h>
typedef struct
{
	double x, y;
} Point;

typedef struct List List;
struct List
{
	Point point;
	List *next;	
};

void printPoint(Point p)
{
	printf("%lf %lf  ", p.x, p.y);
}

List *createList(Point p)
{
	List *new = calloc(sizeof(List), 1);
	new->point = p;
	new->next = NULL;
	return new;
}

void printList(List *list)
{
	printPoint(list->point);
	if (list->next != NULL)
		printList(list->next);
}

int getListSize(List *list)
{
	List *next = list->next;
	int count = 1;
	while(next != NULL)
	{
		next = next->next;
		++count;
	}
	return count;
}

void insertElement(List **list, Point p)
{
	List *new = createList(p);
	new->next = *list;
	*list = new;
}

Point getElement(List *list)
{
	return list->point;
}

Point deleteElement(List **list)
{
	Point temp = getElement(*list);
	List *next = (*list)->next;
	free(*list);
	*list = next;
	return temp;
}

void destroyList(List **list)
{
	List *next;
	List *current = (*list);

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}

	(*list) = NULL;
}

int main()
{
	Point p;
	p.x = 1;
	p.y = 1;
	List *foo = createList(p);
	p.x = 2;
	p.y = 2;
	insertElement(&foo, p);
	p.x = 3;
	p.y = 3;
	insertElement(&foo, p);
	p.x = 4;
	p.y = 4;
	insertElement(&foo, p);
	p.x = 5;
	p.y = 5;
	insertElement(&foo, p);
	printList(foo);
	printf("SIZE: %d\n", getListSize(foo));
	Point bar = deleteElement(&foo);
	printf("DESTROY: %lf %lf\n", bar.x, bar.y);
	printList(foo);
	destroyList(&foo);
	printf("\nPlz, segfaultu \n");
	printList(foo);

	return 0;
}