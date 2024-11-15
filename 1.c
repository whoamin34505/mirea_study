#include <stdio.h>
#include <windows.h>

int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);  

    int a, b, c, d, e;
    printf("Введите 5 чисел через пробел: ");
    scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);

    printf("\nСумма всех чисел: %d", a + b + c + d + e);
    printf("\nРазность всех чисел: %d", a - b - c - d - e);
    printf("\nПроизведение всех чисел: %d", a * b * c * d * e);
    printf("\nОстаток от деления каждого числа на 10: %d %d %d %d %d", a % 10, b % 10, c % 10, d % 10, e % 10);
    printf("\nРазмер переменной каждого числа: %lu %lu %lu %lu %lu", sizeof(a), sizeof(b), sizeof(c), sizeof(d), sizeof(e));
    
    return 0;
}
