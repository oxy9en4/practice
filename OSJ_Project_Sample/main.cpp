#include <stdio.h>

int main()
{
    int n = 0;

    scanf_s("%d", &n);

    int arr[16][16] = { 0 };
    arr[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
            printf("%d", arr[i][j]);
        }
        printf("\n");
    }
}
