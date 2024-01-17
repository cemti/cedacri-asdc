#include <stdio.h>
#include <stdlib.h>

// Comparator pentru qsort
int cmp(const int* a, const int* b)
{
	return *a > *b ? 1 : *a < *b ? -1 : 0;
}

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		printf("Se cere minim 2 parametri.");
		return -1;
	}

	int n1 = atoi(argv[1]),
		n2 = atoi(argv[2]),
		n3 = 0, // v3 se va comporta ca stiva
		*v1 = malloc(n1 * sizeof(int)),
		*v2 = malloc(n2 * sizeof(int)),
		*v3 = malloc((n1 + n2) * sizeof(int)); // simulam stiva
	
	for (int i = 0; i < n1; ++i)
		v1[i] = atoi(argv[i + 3]);
	
	for (int i = 0; i < n2; ++i)
		v2[i] = atoi(argv[i + n1 + 3]);
	
	// Interclasarea tablourilor cere ca ele sa fie sortate
	qsort(v1, n1, sizeof(int), cmp);
	qsort(v2, n2, sizeof(int), cmp);
	
	int it1 = 0, it2 = 0;
	
	// Se face push la cel minim din ambele tablouri
	while (it1 < n1 && it2 < n2)
		v3[n3++] = v1[it1] > v2[it2] ? v2[it2++] : v1[it1++];
	
	while (it1 < n1)
		v3[n3++] = v1[it1++];
	
	while (it2 < n2)
		v3[n3++] = v2[it2++];
	
	for (int i = 0; i < n3; ++i)
		printf("%d ", v3[i]);
	
	free(v1);
	free(v2);
	free(v3);
}