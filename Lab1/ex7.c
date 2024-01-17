#include <stdio.h>

const char* msg = 
	"1. Citirea tabloului\n"
	"2. Afisarea tabloului\n"
	"3. Inserarea unui element nou la capatul tabloului\n"
	"4. Inserarea unui element nou la inceputul tabloului\n"
	"(optiune invalida termina programul)\n"
	">";
	
int n;
int* arr;

void citire()
{
	printf("Nr. de elemente: ");
	scanf("%d", &n);
	
	arr = (int*)realloc(arr, n * sizeof(int));
	
	for (int i = 0; i < n; ++i)
		scanf("%d", arr + i);
}

void afisare()
{
	for (int i = 0; i < n; ++i)
		printf("%d ", arr[i]);
	
	putchar('\n');
}

void append()
{
	printf("Element nou: ");
	
	int em;
	scanf("%d", &em);
	
	arr = (int*)realloc(arr, ++n * sizeof(int));
	arr[n - 1] = em;
}

void prepend()
{
	printf("Element nou: ");
	
	int em;
	scanf("%d", &em);
	
	arr = (int*)realloc(arr, ++n * sizeof(int));
	
	for (int i = n - 1; i > 0; --i)
		arr[i] = arr[i - 1];
	
	arr[0] = em;
}

int main()
{
	for (; ; )
	{
		printf(msg);
		
		char o;
		scanf(" %c", &o);
		
		switch (o)
		{
			case '1':
				citire();
				break;
				
			case '2':
				afisare();
				break;
				
			case '3':
				append();
				break;
				
			case '4':
				prepend();
				break;
				
			default:
				free(arr);
				return 0;
		}
	}
}