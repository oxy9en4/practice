// ������. ����������. n�� Ȧ���� ��, ���������� ����Ǵ� Ǯ�̹���� ����.
//ù ���� �߰����� �����Ͽ� x��ǥ�� y��ǥ�� 1�� ���ÿ� �����ϰ�, �ش� ��ġ�� �̹� ���� �����Ѵٸ� �Ʒ��� �� ĭ �̵�.

#include <stdio.h>
#include <stdlib.h>


void move(int n, int count, int **arr, int *x, int *y)
{
	if (count <= n * n)
	{
		arr[*x][*y] = count++;
		int nextX = (*x + n - 1) % n;
		int nextY = (*y + 1) % n;

		if (arr[nextX][nextY] == 0) {
			*x = nextX, * y = nextY;
		}
		else {
			*x = (*x + 1) % n;
		}
		move(n, count, arr, x, y);
	}
}

void print(int **arr, int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%2d ", arr[i][j]);
		}
		printf("\n");

	}
		
}



int main()
{
	int n = 0;
	
	printf("10������ Ȧ���� �Է��Ͻÿ�.");
	do {
		scanf_s("%d", &n);
	} while (n > 10 || n % 2 == 0);

	int** arr = (int**)malloc(sizeof(int*)*n);
	for (int i = 0; i < n; i++)
	{
		arr[i] = (int*)malloc(sizeof(int)*n);
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			arr[i][j] = 0;
	int x = 0;
	int y = n / 2;
	int count = 1;
	
	move(n,  count , arr, &x, &y);

	print(arr, n);

	for (int i = 0; i < n; i++)
		free(arr[i]);
	free(arr);

	

	

	return 0;
}