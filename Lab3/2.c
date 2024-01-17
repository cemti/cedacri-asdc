#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

struct Stiva
{
	unsigned capacitate;
	int* array;
};

void push(struct Stiva* st, int val)
{
	st->array = realloc(st->array, ++st->capacitate * sizeof(int));	
	st->array[st->capacitate - 1] = val;
}

bool isEmpty(struct Stiva* st)
{
	return st->capacitate == 0;
}

int peek(struct Stiva* st)
{
	if (isEmpty(st))
		assert(0);
	
	return st->array[st->capacitate - 1];
}

int pop(struct Stiva* st)
{
	if (isEmpty(st))
		assert(0);
	
	int temp = peek(st);
	
	if (--st->capacitate == 0)
	{
		free(st->array);
		st->array = NULL;
	}
	else
		st->array = realloc(st->array, st->capacitate * sizeof(int));
	
	return temp;
}

void accumulate(struct Stiva* valori, struct Stiva* operatori)
{
	int b = pop(valori), a = pop(valori);
	char op = pop(operatori);

	switch (op)
	{
	case '+':
		push(valori, a + b);
		break;
	
	case '-':
		push(valori, a - b);
		break;
		
	case '*':
		push(valori, a * b);
		break;
	
	case '/':
		push(valori, a / b);
		break;
		
	default:
		assert(0);
	}
}

int main(int argc, char* argv[])
{
	struct Stiva valori = { 0 }, operatori = { 0 };
	
	for (int i = 1; i < argc; ++i)
	{
		if (argv[i][0] == '(')
		{
			push(&operatori, '(');
			continue;
		}
		
		int val = atoi(argv[i]);
		push(&valori, val);
	
	parseOp:
		if (++i >= argc)
			break;
		
		assert(argv[i][1] == '\0');
		
		char op = argv[i][0];
		int pri1;
		
		switch (op)
		{
		case '+': case '-':
			pri1 = 0;
			break;
			
		case '*': case '/':
			pri1 = 1;
			break;
			
		case ')':
			while (peek(&operatori) != '(')
				accumulate(&valori, &operatori);
			
			pop(&operatori);
			goto parseOp;
			
		default:
			assert(0);
		}
		
		while (!isEmpty(&operatori))
		{			
			char prevOp = peek(&operatori);
			
			if (prevOp == '(')
				break;
			
			int pri2;
			
			switch (prevOp)
			{
			case '+': case '-':
				pri2 = 0;
				break;
				
			case '*': case '/':
				pri2 = 1;
				break;
				
			default:
				assert(0);
			}
			
			if (pri1 > pri2)
				break;
			
			accumulate(&valori, &operatori);
		}
		
		push(&operatori, op);
	}
	
	while (!isEmpty(&operatori))
		accumulate(&valori, &operatori);
	
	printf("%d", peek(&valori));
	
	free(valori.array);
}