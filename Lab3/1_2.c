#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct OperatiuneBancara
{
	char codBanca[6], codClient[11], dataOperatiune[11];
	double sumaOperatiune;
	struct OperatiuneBancara* next;
};

void print(const struct OperatiuneBancara* node)
{
	printf("%s,%s,%s,%lf\n", node->codBanca, node->codClient, node->dataOperatiune, node->sumaOperatiune);
}

struct OperatiuneBancara* scan()
{
	struct OperatiuneBancara* node = calloc(1, sizeof(struct OperatiuneBancara));
	scanf(" %s %s %s %lf", node->codBanca, node->codClient, node->dataOperatiune, &node->sumaOperatiune);	
	return node;
}

struct List
{
	struct OperatiuneBancara *front, *back;
};

int cmp(const struct OperatiuneBancara** a, const struct OperatiuneBancara** b)
{
	return (*a)->sumaOperatiune < (*b)->sumaOperatiune ? 1 : (*a)->sumaOperatiune > (*b)->sumaOperatiune ? -1 : 0;
}

void freeList(struct List* list)
{
	while (list->front)
	{
		struct OperatiuneBancara* temp = list->front->next;
		free(list->front);
		list->front = temp;
	}
	
	list->back = NULL;
}

void printList(struct List* list)
{
	struct OperatiuneBancara* node = list->front;
	
	while (node)
	{
		print(node);
		node = node->next;
	}
}

void adauga(struct List* list, struct OperatiuneBancara* node)
{
	if (list->front == NULL)
		list->front = node;
	else
		list->back->next = node;
	
	list->back = node;
}

void sterge(struct List* list)
{
	struct OperatiuneBancara* node = list->front;
	
	while (node)
	{
		if (node->next == NULL)
		{
			free(node);
			list->front = list->back = NULL;
		}
		else if (node->next->next == NULL)
		{
			free(node->next);
			node->next = NULL;
			list->back = node;
		}
		else
		{
			node = node->next;
			continue;
		}
		
		break;
	}
}

void afiseaza(const struct List* list, const char* codClient)
{
	struct OperatiuneBancara* node = list->front;
	
	while (node)
	{
		if (strcmp(codClient, node->codClient) == 0)
			print(node);
		
		node = node->next;
	}
}

double suma(const struct List* list, const char* codClient, const char* dataOperatiune)
{
	struct OperatiuneBancara* node = list->front;
	double s = 0;
	
	while (node)
	{
		if (strcmp(codClient, node->codClient) == 0 && strcmp(dataOperatiune, node->dataOperatiune) == 0)
			s += node->sumaOperatiune;
		
		node = node->next;
	}
	
	return s;
}

void sorteaza(struct List* list)
{
	struct OperatiuneBancara** buffer = NULL, *node = list->front;
	int n = 0;
	
	while (node)
	{
		buffer = realloc(buffer, ++n * sizeof(struct OperatiuneBancara*));
		buffer[n - 1] = node;
		node = node->next;
	}
	
	if (buffer == NULL)
		return;
	
	qsort(buffer, n, sizeof(struct OperatiuneBancara*), cmp);
	
	list->front = buffer[0];
	
	for (int i = 1; i < n; ++i)
		buffer[i - 1]->next = buffer[i];
	
	buffer[n - 1]->next = NULL;
	list->back = buffer[n - 1];
	free(buffer);
}

const char* msg =
	"1. Adaugarea unei noi operatiuni in lista.\n"
	"2. Stergerea ultimei operatiuni.\n"
	"3. Afisarea operatiunilor unui client specific.\n"
	"4. Calculul sumei totale a operatiunilor unui client intr-o perioada specificata.\n"
	"5. Sortarea operatiunilor descrescator dupa suma.\n"
	"6. Afisare lista.\n"
	"*. Iesire.\n"
	">";

int main()
{
	struct List list = { NULL };
	
	for (; ; )
	{
		printf(msg);
		
		char op;
		scanf(" %c", &op);
		
		switch (op)
		{
		case '1':
			adauga(&list, scan());
			break;
			
		case '2':
			sterge(&list);
			break;
			
		case '3':
		{
			char codClient[11];
			scanf(" %s", codClient);
			afiseaza(&list, codClient);
			break;
		}
			
		case '4':
		{
			char codClient[11], dataOperatiune[11];
			scanf(" %s %s", codClient, dataOperatiune);
			printf("%lf\n", suma(&list, codClient, dataOperatiune));
			break;
		}
			
		case '5':
			sorteaza(&list);
			break;
			
		case '6':
			printList(&list);
			break;
			
		default:
			freeList(&list);
			return 0;
		}
	}
}