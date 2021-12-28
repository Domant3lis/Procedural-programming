// Domantas Keturakis © 2021
#include <stdio.h>
#include <math.h>

typedef struct
{
	double x, y;
} Point;

void printPoint(Point p)
{
	printf("%lf %lf", p.x, p.y);
}

Point createPoint(double x, double y)
{
	Point point;
	point.x = x;
	point.y = y;
	return point;
}

double getDistance(Point a, Point b)
{
	double x = a.x - b.x;
	double y = a.y - b.y;
	return sqrt((x*x) + (y*y));
}

int main()
{
	printf("The distance is: %lf", getDistance(createPoint(2, -3), createPoint(-4, 5)));
	return 0;
}