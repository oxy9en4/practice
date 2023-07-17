#include <stdio.h>

void hanoi(int n, char from, char by, char to)
{
	if (n == 1)
	{
		printf("1번을 %c에서 %c로 이동\n", from, to);
	}
	else
	{
		hanoi(n - 1, from, to, by);
		printf("%d번을 %c에서 %c로 이동\n", n, from, to);
		hanoi(n - 1, by, from, to);
	}
}

int main() 
{
	int n = 3;
	

	hanoi(n, 'A', 'B', 'C');
}