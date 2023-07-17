// 마방진. 매직스퀘어. n이 홀수일 때, 보편적으로 적용되는 풀이방식을 재현.
//첫 열의 중간에서 시작하여 x좌표와 y좌표가 1씩 동시에 증감하고, 해당 위치에 이미 값이 존재한다면 아래로 한 칸 이동.

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
	
	printf("10이하의 홀수를 입력하시오.");
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