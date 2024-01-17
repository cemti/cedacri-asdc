#include <stdio.h>
#include <stdlib.h>

// Memoization to speed up computations
int memo[1000] = { 1, 1, 2, 3, 5, 8 };

int fib(int n)
{
	if (n > 1000)
		return fib(n - 1) + fib(n - 2);
	
	if (memo[n - 1] > 0)
		return memo[n - 1];
	
	memo[n - 1] = fib(n - 1) + fib(n - 2);
	return memo[n - 1];
}

struct Pair
{
	int first, second;
};

int main()
{
	int n;
	scanf("%d", &n); // assuming n > 0

	struct Pair *v = NULL; // stack
	int top = 0;
	
	do
	{
		v = realloc(v, ++top * sizeof(struct Pair)); // push
		
		for (int i = 1; ; ++i)
		{
			int temp = fib(i);
			
			if (temp > n)
				break;
		
			v[top - 1].first = i;
			v[top - 1].second = temp;
			
			if (temp == n)
				goto printResults;
		}
		
		n -= v[top - 1].second;
	} while (n > 0);
	
printResults:
	for (int i = 0; i < top; ++i)
		printf("+F(%d)" + (i == 0), v[i].first);
	
	putchar('=');

	for (int i = 0; i < top; ++i)
		printf("+%d" + (i == 0), v[i].second);
	
	free(v);
}