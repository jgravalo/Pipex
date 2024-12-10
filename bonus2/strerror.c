#include<stdio.h>
#include<string.h>

int main()
{
	for (int i = 0; i < 160; i++)
		printf("%d: %s\n", i, strerror(i));
}
