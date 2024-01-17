#include <stdio.h>

double aria(double b, double h)
{
	return b * h * .5;
}

int main()
{
	double b, h;
	puts("Baza, inaltime:");
	scanf("%lf%lf", &b, &h);
	printf("%lf", aria(b, h));
}