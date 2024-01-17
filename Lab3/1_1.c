#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node
{
	int data;
	struct Node* link;
};

struct List
{
	struct Node *front;
};

bool isEmpty(struct List* l)
{
	return l->front == NULL;
}

void prepend(struct List* l, int em)
{
	struct Node* temp = malloc(sizeof(struct Node));
	temp->data = em;
	temp->link = l->front;
	l->front = temp;
}

void removeNode(struct List* l, int em)
{
	struct Node* n = l->front, *prev = NULL;
	
	while (n)
	{
		if (n->data == em)
		{
			if (prev)
				prev->link = n->link;
			else
				l->front = n->link;
			
			free(n);
			break;
		}
		
		prev = n;
		n = n->link;
	}
}

void print(struct List* l)
{
	struct Node* n = l->front;
	
	while (n)
	{
		printf("%d ", n->data);
		n = n->link;
	}
}

void reassign(struct List* l, int oldEm, int newEm)
{
	struct Node* n = l->front;
	
	while (n)
	{
		if (n->data == oldEm)
		{
			n->data = newEm;
			break;
		}
		
		n = n->link;
	}
}

void freeList(struct List* l)
{
	while (l->front)
	{
		struct Node* temp = l->front->link;
		free(l->front);
		l->front = temp;
	}
}

const char* msg =
	"a. Verifica daca lista e goala.\n"
	"b. Insereaza un nod la inceputul listei.\n"
	"c. Sterge un nod dupa valoare.\n"
	"d. Afiseaza lista.\n"
	"e. Modifica un nod.\n"
	"*. Iesire.\n"
	">";

int main()
{
	struct List l = { NULL };
	
	for (; ; )
	{
		printf(msg);
		
		char o;
		scanf(" %c", &o);
		
		switch (o)
		{
		case 'a':
			printf("%s\n", isEmpty(&l) ? "da" : "nu");
			break;
		
		case 'b':
		{
			int em;
			printf("Element nou: ");
			scanf("%d", &em);
			prepend(&l, em);
			break;
		}
		
		case 'c':
		{
			int em;
			printf("Element de sters: ");
			scanf("%d", &em);
			removeNode(&l, em);
			break;
		}
			
		case 'd':
			print(&l);
			putchar('\n');
			break;
			
		case 'e':
		{
			int oldEm, newEm;
			printf("Elementul vechi si cel nou:\n");
			scanf("%d%d", &oldEm, &newEm);
			reassign(&l, oldEm, newEm);
			break;
		}
			
		default:
			freeList(&l);
			return 0;
		}
	}
}