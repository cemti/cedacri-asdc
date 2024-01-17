#include <stdio.h>
#include <stdlib.h>

int cmp(const double* a, const double* b)
{
	return *a < *b ? -1 : *a > *b;
}

int main()
{
	printf("Nr. elemente: ");
	
	int n;
	scanf("%d", &n);
	
	if (n <= 0)
		return 0;
	
	double* arr = malloc(n * sizeof(double)), mx;
	
	int* pos = malloc(n * sizeof(int)), posN = 0;
	
	for (int i = 0; i < n; ++i)
	{
		scanf("%lf", arr + i);
		
		if (posN == 0)
		{
			mx = arr[i];
			pos[posN++] = i;
		}
		else if (arr[i] == mx)
			pos[posN++] = i;
		else if (arr[i] > mx)
		{
			mx = arr[i];
			posN = 1;
			pos[0] = i;
		}
	}
	
	printf("Elementul maxim: %lf, pe pozitiile: ", mx);
	
	for (int i = 0; i < posN; ++i)
		printf("%d ", pos[i]);
	
	qsort(arr, n, sizeof(double), cmp);
	printf("\nTabloul sortat: ");
	
	for (int i = 0; i < n; ++i)
		printf("%lf ", arr[i]);
	
	free(arr);
	free(pos);
}