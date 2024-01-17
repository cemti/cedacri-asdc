#include <stdio.h>

unsigned long long factorial(unsigned long long n)
{
	unsigned long long r = 1;
	
	while (n > 1)
		r *= n--;
	
	return r;
}

int main()
{
	unsigned long long n;
	scanf("%llu", &n);
	printf("%llu", factorial(n));
}