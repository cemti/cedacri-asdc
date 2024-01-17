#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int n = argc - 1;

	if (n < 3)
	{
		printf("Se necesita cel putin trei elemente a vectorului ca argumente.");
		return -1;
	}

	// Se afiseaza in mod invers primele trei elemente
	printf("%s %s %s ", argv[3], argv[2], argv[1]);
	
	// Se afiseaza celelalte elemente
	for (int i = 4; i <= n; ++i)
		printf("%s ", argv[i]);
}