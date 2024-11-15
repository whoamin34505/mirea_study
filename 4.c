#include <stdio.h>
#include <stdlib.h>

int* bubble_sort(int* arr, int size) {
    int* sorted_array = malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        sorted_array[i] = arr[i];
    }

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (sorted_array[j] > sorted_array[j + 1]) {
                int temp = sorted_array[j];
                sorted_array[j] = sorted_array[j + 1];
                sorted_array[j + 1] = temp;
            }
        }
    }

    return sorted_array;
}

int main() {
    int n = 0;
    printf("Enter array's size: ");
    scanf("%d", &n);

    int* a = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        printf("Enter %d array's number: ", i + 1);
        scanf("%d", &a[i]);
    }


    int* sorted_array = bubble_sort(a, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", sorted_array[i]);
    }
    printf("\n");

    free(a);
    free(sorted_array);

    return 0;
}
