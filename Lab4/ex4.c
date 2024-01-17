#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
typedef unsigned long long u64;

struct Operatiune
{
	u64 codBanca, codClient, idOperatiune;
};

struct Tranzactie
{
	u64 codBanca, idOperatiune;
	double sumaOperatiune;
} **tList;

u64 tListN;

int main()
{
	setlocale(LC_NUMERIC, "ro_RO");
	
	{
		FILE* f = fopen("tranzactii.txt", "r");
		struct Tranzactie temp;
		
		while (fscanf(f, "%5llu%13llu%16lf", &temp.codBanca, &temp.idOperatiune, &temp.sumaOperatiune) == 3)
			*((tList = realloc(tList, ++tListN * sizeof(struct Tranzactie*)))[tListN - 1] = malloc(sizeof(struct Tranzactie))) = temp;
			
		fclose(f);
	}
	
	{
		FILE *f = fopen("operatiuni.txt", "r"), *fout = fopen("match.txt", "w");
		struct Operatiune temp;
		
		while (fscanf(f, "%5llu%10llu%13llu", &temp.codBanca, &temp.codClient, &temp.idOperatiune) == 3)
			for (u64 j = 0; j < tListN; ++j)
				if (temp.codBanca == tList[j]->codBanca && temp.idOperatiune == tList[j]->idOperatiune)
					fprintf(fout, "%05llu%010llu%015.3lf\n", temp.codBanca, temp.codClient, tList[j]->sumaOperatiune);

		fclose(f);
		fclose(fout);
	}
	
	for (u64 i = 0; i < tListN; ++i)
		free(tList[i]);
	
	free(tList);
}