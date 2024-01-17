#include <stdio.h>
#include <stdlib.h>

// Tabela hash pentru a reduce
// complexitatea temporala a problemei
// (element, nr. de repetari)
struct Entry
{
	int em, count;
} *hashTable;

int n;

// Obtimem pointer spre structura
struct Entry* GetKey(int em)
{
	// "functia" hash pentru a indica locatia
	int pos = em % n;
	
	// Versiunea simplificata deoarece avem
	// garantat n elemente, nu in plus
	while (hashTable[pos].count != 0 && hashTable[pos].em != em)
		pos = (pos + 1) % n;
	
	if (hashTable[pos].count == 0)
	{
		hashTable[pos].em = em;
		hashTable[pos].count = 0;
	}

	return hashTable + pos;
}

int main(int argc, char* argv[])
{
	n = argc - 1;

	if (n < 0)
	{
		printf("Se necesita cel putin primul element a vectorului ca argument.");
		return -1;
	}

	int *v1 = malloc(n * sizeof(int));
	
	hashTable = calloc(n, sizeof(struct Entry));
	
	// Se contorizeaza fiecare element
	for (int i = 0; i < n; ++i)
	{
		v1[i] = atoi(argv[i + 1]);
		++GetKey(v1[i])->count;
	}
		
	int top = n;
	
	// Se sterg elementele cu nr. de repetari = 1
	for (int i = 0; i < top; )
	{
		if (GetKey(v1[i])->count == 1)
		{
			--top; // se reduce marimea tabloului cu 1
			v1[i] ^= v1[top] ^= v1[i] ^= v1[top]; // interschimbare XOR cu ultimul element
		}
		else
			++i;
	}
	
	for (int i = 0; i < top; ++i)
		printf("%d ", v1[i]);
	
	free(hashTable);
	free(v1);
}