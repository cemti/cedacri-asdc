#include <stdio.h>

// __uint128_t lucreaza numai pe GCC
// Presupunem ca CLion are GCC
__uint128_t factorial(__uint128_t n)
{
	__uint128_t r = 1;
	
	while (n > 1)
		r *= n--;
	
	return r;
}

// Nu putem afisa direct un numar cu printf
void afiseaza(__uint128_t n)
{
    if (n > 9)
        afiseaza(n / 10);
    
    printf("%d", (int)(n % 10));
}

int main()
{
	unsigned long long n;
	scanf("%llu", &n);
	
	// max 34
	afiseaza(factorial(n));
}