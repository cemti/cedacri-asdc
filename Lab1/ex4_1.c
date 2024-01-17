#include <stdio.h>

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		puts("Se cere sirul de caractere ca argument");
		return -1;
	}
	
	char* str = argv[1];
	int vocale = 0, n;
	
	for (n = 0; str[n]; ++n)
	{
		switch (str[n] | ' ')
		{
			case 'a': case 'e': case 'i': case 'o': case 'u':
				++vocale;
		}
	}
	
	printf("Nr. de vocale: %d\n", vocale);
	
	int i = 0;
	--n;
	
	while (i < n)
	{
		str[i] ^= str[n] ^= str[i] ^= str[n];
		++i;
		--n;
	}
	
	printf("Sirul inversat: %s", str);
}