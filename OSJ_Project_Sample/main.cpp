#include <stdio.h>

void solve(int n)
{
    /* 여기에 코드를 작성해 주세요 */
    for (int i = 1; i < n; i++) {
        if (n % i == 0) printf("%d ", i);
    }
    printf("%d", n);
}

int main(void)
{
    int n;
    scanf_s("%d", &n);

    solve(n);

    return 0;
}