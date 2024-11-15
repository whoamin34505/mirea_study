#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);  
    int a, r, count1 = 0, count2 = 0;
    const char *mas[3];
    mas[0]="камень";
    mas[1]="ножницы";
    mas[2]="бумага";
    while (1) {
        printf("\n\nВы попали в игру Камень-ножницы-бумага!\nКамень - 1, ножницы - 2, бумага - 3.\nВведите 1, 2 или 3: ");
        scanf("%d", &a);
        while (a != 1 && a != 2 && a != 3) {
            printf("\nВы ввели число вне диапазона! Введите 1, 2 или 3: ");
            scanf("%d", &a);
        }
        
        srand(time(NULL));
        r = rand() % 3 + 1;

        if (a == r) {
            printf("\nНичья! Очко никому не достаётся. Текущий баланс очков: компьютер - %d, ты - %d.", count1, count2);
        }
        else if ((a == 1 && r == 2) || (a == 2 && r == 3) || (a == 3 && r == 1)) {
            count2++; 
            printf("\nТы выиграл! Компьютер выбрал %s, ты выбрал %s. Текущий баланс очков: компьютер - %d, ты - %d.", mas[r-1], mas[a-1], count1, count2);
        }
        else {
            count1++; 
            printf("\nКомпьютер выиграл! Компьютер выбрал %s, ты выбрал %s. Текущий баланс очков: компьютер - %d, ты - %d.", mas[r-1], mas[a-1], count1, count2);
        }
    }
    return 0;
}
