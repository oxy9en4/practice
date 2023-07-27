#include <stdio.h>

int main(void)
{
    int n, m;
    int arr[3][30] = { 0 };

    scanf_s("%d %d", &n, &m);
    int n_tmp = n;
    int m_tmp = m;
    for (int i = 2; i <= n; i++) {
        while (n_tmp % i == 0) {
            n_tmp /= i;
            arr[0][i]++;
        }

    }
    for (int i = 2; i <= m; i++) {
        while (m_tmp % i == 0) {
            m_tmp /= i;
            arr[1][i]++;
        }
    }
    int result = 1;
    for (int i = 2; i < 30; i++) {
        int max = (arr[0][i] > arr[1][i]) ? arr[0][i] : arr[1][i];
        while (max > 0) {
            result = result * i;
            max--;
        }
    }
    printf("%d", result);

    return 0;
}