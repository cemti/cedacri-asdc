#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char mtx[20][20], word[21];
bool mark[20][20];

// additional lookup table to index the letters
// at most 20 * 20 = 400 indexes
int len, n, lookupN[26], lookup[26][400][2];

// replicating C++ template
#define FIND(name, cond, oX, oY)\
bool find ## name (int pI, int pJ, bool rev) {\
	if (cond)\
		return false;\
	for (int i = 0; i < len; ++i)\
		if (mtx[pI + oX][pJ + oY] != word[rev ? len - i - 1 : i])\
			return false;\
	for (int i = 0; i < len; ++i)\
		mark[pI + oX][pJ + oY] = true;\
	return true;\
}

FIND(East, 20 - pJ <= len, 0, i)
FIND(South, 20 - pI <= len, i, 0)
FIND(SouthEast, 20 - pI <= len && 20 - pJ <= len, i, i)
FIND(SouthWest, 20 - pI <= len && pJ + 1 >= len, i, -i)

// find the word and its form in reserse
#define LOOP(letter, rev)\
	for (int k = 0; k < lookupN[letter]; ++k) {\
		int i = lookup[letter][k][0], j = lookup[letter][k][1];\
		if (findEast(i, j, rev) || findSouth(i, j, rev) || findSouthEast(i, j, rev) || findSouthWest(i, j, rev))\
			return;\
	}

void findWord()
{
	LOOP(word[0] - 'A', false)
	LOOP(word[len - 1] - 'A', true)
}

int main()
{
	scanf("%d", &n);
	
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
		{
			char temp;
			scanf(" %c ", &temp);
			mtx[i][j] = temp;
			
			temp -= 'A';
			
			int *ptr = lookup[temp][lookupN[temp]++];
			ptr[0] = i;
			ptr[1] = j;
		}
		
	for (; ; )
	{
		scanf("%s%n", word, &len);
		--len;
		
		if (word[len - 1] == '.')
		{
			--len;
			findWord();
			break;
		}
		
		findWord();
	}
	
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (!mark[i][j])
				putchar(mtx[i][j]);
}
