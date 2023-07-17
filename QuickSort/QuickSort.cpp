#include <iostream>
#include <iomanip>

// �迭 ��Ҹ� ��ȯ�ϴ� �Լ�
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// �迭�� ����ϴ� �Լ�
void printArray(int arr[], int size, int low, int high, int pivot) {
    for (int i = 0; i < size; i++) {
        if (i == low)
            std::cout << "\033[33m" << std::setw(4) << std::left << std::setfill(' ') << arr[i] << "\033[0m";
        else if (i == high)
            std::cout << "\033[31m" << std::setw(4) << std::left << std::setfill(' ') << arr[i] << "\033[0m";
        else if (i == pivot)
            std::cout << "\033[4m" << std::setw(4) << std::left << std::setfill(' ') << arr[i] << "\033[0m";
        else
            std::cout << std::setw(4) << std::left << std::setfill(' ') << arr[i];
    }
    std::cout << std::endl;
}

// �� ���� �Լ�
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // �ǹ� ����
        int pivot = arr[high];
        int i = low - 1;

        // �ǹ��� �������� �迭 ����
        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(&arr[i], &arr[j]);
            }
        }
        swap(&arr[i + 1], &arr[high]);

        // ���� �ڵ�, �迭, low, high, pivot �� ���
        std::cout << "Array: ";
        printArray(arr, high + 1, low, high, i + 1);

        // ���� �κ� �迭 ����
        quickSort(arr, low, i);

        // ������ �κ� �迭 ����
        quickSort(arr, i + 2, high);
    }
}

int main() {
    int arr[] = { 9, 3, 7, 1, 5, 10, 6, 2, 4, 8 };
    int n = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Initial Array: ";
    printArray(arr, n, -1, -1, -1);

    std::cout << std::endl << "Quick Sort Progress:" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "Array: ";
        printArray(arr, n, 0, n - 1, i);
        quickSort(arr, 0, i);
    }

    std::cout << std::endl << "Sorted Array: ";
    printArray(arr, n, -1, -1, -1);

    return 0;
}
