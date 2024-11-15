#include <stdio.h>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);  
    int n = 0;
    printf("Введите размер массива: ");
    scanf("%d", &n); 

    int a[n];  

    for (int i = 0; i < n; i++) {
        printf("Введите %d число массива: ", i + 1);
        scanf("%d", &a[i]);  
    }
    
    for (int i=0; i<n; i++){
        for (int j=i+1; j<n; j++){
            if (a[i]>a[j]){
                int temp = a[j];
                a[j]=a[i];
                a[i]=temp;
            }
        }
    }
    
    printf("\nОтсортированные элементы массива: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);  
    }
    printf("\nМинимальное число - %d, максимальное число - %d",a[0],a[n-1]);
    return 0;
}
