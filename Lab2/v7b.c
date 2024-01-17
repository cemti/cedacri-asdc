#include <stdio.h>
#include <stdlib.h>

// Comparator pentru qsort
int cmp(const int* a, const int* b)
{
	return *a > *b ? 1 : *a < *b ? -1 : 0;
}

int main(int argc, char* argv[])
{
	int n = argc - 1;

	if (n == 0)
		return 0;

	int *v1 = malloc(n * sizeof(int));
	
	for (int i = 0; i < n; ++i)
		v1[i] = atoi(argv[i + 1]);

	// Se sorteaza elementele cu scopul ca
	// elementele identice sa fie consecutive
	qsort(v1, n, sizeof(int), cmp);
	
	// Avem doua indici pentru elementul stabilit si cel temporar
	int em, emN = 0, emT = v1[0], emTN = 1;
	
	// i = 1 sarim peste primul element deoarece deja il avem
	for (int i = 1; ; ++i)
	{
		if (i >= n || v1[i] != emT)
		{
			// Daca elementul temporar se repeta mai mult
			// decat cel stabilit,
			// se actualizeaza
			if (emTN > emN)
			{
				em = emT;
				emN = emTN;
			}
			
			if (i >= n)
				break;
			
			// Daca mai sunt elemente,
			// Se reinitializeaza elementul temporar
			emT = v1[i];
			emTN = 1;
		}
		else
			++emTN;
	}
	
	printf("num %d is repeated %d times", em, emN);	
	free(v1);
}