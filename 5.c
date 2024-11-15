#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

double opred(double** b, int size) {
    int swaps = 0; 

    for (int i = 0; i < size; i++) {
        if (b[i][i] == 0) {
            for (int j = i + 1; j < size; j++) {
                if (b[j][i] != 0) { 
                    double* temp = b[i];
                    b[i] = b[j];
                    b[j] = temp;
                    swaps++; 
                    break;
                }
            }
            if (b[i][i] == 0) {
                return 0;
            }
        }

        for (int j = i + 1; j < size; j++) {
            double mn = b[j][i] / b[i][i];
            for (int k = i; k < size; k++) {
                b[j][k] -= mn * b[i][k]; 
            }
        }

        printf("\nМатрица после %d-го шага:\n", i + 1);
        for (int x = 0; x < size; x++) {
            for (int y = 0; y < size; y++) {
                printf("%.2f ", b[x][y]);
            }
            printf("\n");
        }
        printf("\n");
    }

    double determinant = 1;
    for (int i = 0; i < size; i++) {
        determinant *= b[i][i]; 
    }

    if (swaps % 2 != 0) {
        determinant = -determinant;
    }

    return determinant;
}

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    int choose;
    printf("Введите 1 если вы хотите автоматически заполнить матрицу, введите 2 если вручную: ");
    scanf("%d", &choose);
    
    if (choose != 1 && choose != 2) {
        printf("Ошибка: введите 1 или 2.\n");
        return 1;
    }

    int n;
    printf("Введите размер: ");
    scanf("%d", &n);
    
    double** b = malloc(sizeof(double*) * n);
    for (int i = 0; i < n; i++) {
        b[i] = malloc(sizeof(double) * n);
    }

    switch (choose) {
        case 1:
            srand(time(NULL));
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    b[i][j] = rand() % 10; 
                }
            }
            printf("Случайный массив:\n");
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    printf("%.2f ", b[i][j]);
                }
                printf("\n");
            }
            break;

        case 2:
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    printf("Введите %d элемент %d строки: ", j + 1, i + 1);
                    scanf("%lf", &b[i][j]);
                }
            }
            break;
    }

    double determinant = opred(b, n);
    if (determinant == 0) {
        printf("\nОпределитель равен нулю.\n");
    } else {
        printf("Определитель = %.2f\n", determinant);
    }

    for (int i = 0; i < n; i++) {
        free(b[i]);
    }
    free(b);
    return 0;
}
