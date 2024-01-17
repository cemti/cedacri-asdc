#include <stdio.h>

// additional buffer (list) to promote cache locality
int mtx[100][100], listN, list[100], m, c, target;

// find the sum in a buffer instead of doing
// additional offset operations
void findSum()
{
	for (int i = 0; i < listN - 1; ++i)
	{
		int sum = target;
		
		for (int j = i; j < listN; ++j)
		{
			if (list[j] < sum)
				sum -= list[j];
			else
			{
				if (i != j && list[j] == sum)
					++c;
				
				break;
			}
		}
	}
}

// loads elements into a buffer

void fetchListEast(int pI)
{
	for (int i = 0; i < m; ++i)
		list[i] = mtx[pI][i];
	
	listN = m;
	findSum();
}

void fetchListSouth(int pJ)
{
	for (int i = 0; i < m; ++i)
		list[i] = mtx[i][pJ];
	
	listN = m;
	findSum();
}

void fetchListSouthEast(int i, int j)
{
	listN = 0;
	
	for (; i < m && j < m; ++i, ++j)
		list[listN++] = mtx[i][j];
	
	findSum();
}

void fetchListSouthWest(int i, int j)
{
	listN = 0;
	
	for (; i < m && j >= 0; ++i, --j)
		list[listN++] = mtx[i][j];
	
	findSum();
}

int main()
{
	scanf("%d %d", &target, &m);
	
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < m; ++j)
			scanf("%d", mtx[i] + j);
		
	for (int i = 0; i < m; ++i)
	{
		fetchListEast(i);
		fetchListSouth(i);		
		fetchListSouthEast(0, i);		
		fetchListSouthWest(0, m - i - 1);
		
		if (i > 0)
		{
			fetchListSouthEast(i, 0);
			fetchListSouthWest(i, m - 1);
		}
	}
	
	printf("%d", c);
}