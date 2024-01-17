#include <stdio.h>
#include <stdlib.h>

int* readGrades(int* n)
{
	scanf("%d", n);
	int *grades = malloc(*n * sizeof(int));
	
	for (int i = 0; i < *n; ++i)
		scanf("%d", grades + i);
	
	return grades;
}

int* computeFrequencies(const int* grades, int n)
{
	int* histogram = calloc(10, sizeof(int)); // zeroed
	
	for (int i = 0; i < n; ++i)
		++histogram[grades[i] - 1];
	
	return histogram;
}

void printHistogram(const int* histogram)
{
	int mx = histogram[0]; // max is the bar height
	
	for (int i = 1; i < 10; ++i)
		if (mx < histogram[i])
			mx = histogram[i];
		
	for (int i = mx; i > 0; --i)
	{
		for (int j = 0; j < 10; ++j)
			printf("%c ", i > histogram[j] ? '.' : '*');
		
		putchar('\n');
	}
		
	for (int i = 1; i <= 10; ++i)
		printf("%d ", i);
}

int main()
{
	int n,
		*grades = readGrades(&n), 
		*histogram = computeFrequencies(grades, n);
		
	printHistogram(histogram);
	
	free(histogram);
	free(grades);
}