#include <stdio.h>
#include <stdbool.h>

// 2 clauses with at most 26 atoms
// each atom tracks the number of themselves and their negations
int atoms[2][26][2];

// the scan is done character by character
// no additional allocation is necessary
int main()
{
	getchar(); // assuming '['
	
	for (; ; )
	{
		char atom = getchar();
		
		if (atom == ',')
			continue;
		
		if (atom == ']')
			break;
		
		if (atom == '~')
		{
			atom = getchar();
			++atoms[0][(atom | ' ') - 'a'][1];
		}
		else
			++atoms[0][(atom | ' ') - 'a'][0];
	}
	
	bool resolvent = false;
	getchar(); // assuming ' ' (space)
	getchar(); // assuming '['
	
	for (; ; )
	{
		char atom = getchar();
		
		if (atom == ',')
			continue;
		
		if (atom == ']')
			break;
		
		// What if we had more than one resolvent?
		// The resolvent clause can't contain an atom and its negation, can it?
		
		if (atom == '~')
		{
			atom = (getchar() | ' ') - 'a'; // case-insensitive
			++atoms[1][atom][1];
			
			if (atoms[0][atom][0] > 0)
			{
				--atoms[1][atom][1];
				--atoms[0][atom][0];
				resolvent = true;
			}
		}
		else
		{
			atom = (atom | ' ') - 'a';
			++atoms[1][atom][0];
			
			if (atoms[0][atom][1] > 0)
			{
				--atoms[1][atom][0];
				--atoms[0][atom][1];
				resolvent = true;
			}
		}
	}
	
	if (!resolvent)
	{
		printf("NO RESOLVENT");
		return 0;
	}
	
	putchar('[');
	bool comma = false;
	
	for (int i = 0; i < 26; ++i)
	{
		// reduce/don't print duplicates
		bool pos = atoms[0][i][0] > 0 || atoms[1][i][0] > 0,
			neg = atoms[0][i][1] > 0 || atoms[1][i][1] > 0;
		
		if (!pos && !neg)
			continue;

		if (comma)
			putchar(',');
		else
			comma = true;
		
		char atom = 'A' + i;
		
		if (pos && neg)
			printf("%c,~%c", atom, atom); // what if the input clauses are 'invalid'?
		else
			printf("~%c" + pos, atom);
	}
	
	putchar(']');
}