#include <stdio.h>

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		printf("Se necesita inaltimea si latimea matricei.");
		return -1;
	}
	
	int n = atoi(argv[1]), m = atoi(argv[2]);
	
	// Aici matricea deja o avem de la linia de comanda	
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < i; ++j)
			printf("%s ", argv[3 + i * m + m - j - 1]); // mtx[i][m - j - 1]
}