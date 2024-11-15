#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <dirent.h>

void del();
void enter();
void list();
void edit_a();
void reg();

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    int choose;
    
    while (1) {
        printf("\n\n\nЕсли Вы хотите войти в учетную запись, введите 1.\nЕсли хотите добавить нового пользователя, введите 2.\nЧтобы увидеть список пользователей введите 3.\nЧтобы удалить пользователя введите 4.\nЧтобы изменить пароль пользователя введите 5.\nДля выхода введите 0: ");
        scanf("%d", &choose);

        switch (choose) {
            case 1:
                enter();
                break;
            case 2:
                reg();
                break;
            case 3:
                list();
                break;
            case 4:
                del();
                break;
            case 5:
                edit_a();
                break;
            case 0:
                printf("Выход из программы.\n");
                return 0;
            default:
                printf("Вы ввели некорректное значение.\n");
        }
    }

    return 0;
}

void del(){
    printf("Введите логин пользователя, которого нужно удалить: ");
    char login[25];
    scanf("%s",login);
    char path[50];
    sprintf(path,"6/%s",login);
    FILE* fp = fopen(path, "r");
    if (fp == NULL) {
        printf("Пользователь не найден.");
        return; 
    }
    printf("Введите пароль от логина %s: ",login);
    char pass[50];
    scanf("%s",pass);
    char buffer[50];
    fgets(buffer,50,fp);
    //printf("%s %s",pass,buffer);
    //buffer[strcspn(buffer, "\n")] = 0;
    if (strcmp(buffer, pass) == 0){
        fclose(fp);
        remove(path);
        printf("Пользователь %s удалён",login);
    }
    else {
        printf("Пароль неправильный, пользователь не удалён");
        fclose(fp);
    }
}

void edit_a() {
        struct dirent *dp;
        DIR *dir = opendir("6/");
        if (!dir) return;
        
        while ((dp = readdir(dir)) != NULL) {
            if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
                printf("%s\n", dp->d_name);
            }
        }
        
        closedir(dir);
        printf("Введите логин для которого нужно изменить пароль: ");
        char login[25];
        scanf("%s", login);
        
        char path[50];
        sprintf(path, "6/%s", login);
        
        FILE* fp = fopen(path, "w"); 
        if (fp == NULL) {
            printf("Пользователь не найден.\n");
            return;
        }
        
        printf("Введите новый пароль для пользователя %s: ", login);
        char new_password[25];
        scanf("%s", new_password);

        fprintf(fp, "%s", new_password);
        fclose(fp);
        
        printf("Пароль для пользователя %s успешно изменен.\n", login);

}


void list(){
        struct dirent *dp;
        DIR *dir = opendir("6/");
        if (!dir) return;
        while ((dp = readdir(dir)) != NULL) {
            if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
                printf("%s\n", dp->d_name);
    }
}
 closedir(dir);
}

void reg() {  
        printf("Введите логин нового пользователя: ");
        char login[25];
        scanf("%s",login);
        //login[strcspn(login, "\n")] = 0;
        char path[50];
        sprintf(path,"6/%s",login);
        FILE* fp = fopen(path,"a+");
        printf("\nВведите пароль для пользователя %s: ",login);
        char pass[50];
        scanf("%s",pass);
        fprintf(fp,"%s",pass);
        printf("Пользователь %s с паролем %s создан.",login,pass);
        fclose(fp);

}

void enter() {
    printf("Введите логин: ");
    char login[25];
    scanf("%s",login);
    char path[50];
    sprintf(path,"6/%s",login);
    FILE* fp = fopen(path, "r");
    if (fp == NULL) {
        printf("Пользователь не найден.");
        return; 
    }
    printf("Введите пароль от логина %s: ",login);
    char pass[50];
    scanf("%s",pass);
    char buffer[50];
    fgets(buffer,50,fp);
    //printf("%s %s",pass,buffer);
    //buffer[strcspn(buffer, "\n")] = 0;
    if (strcmp(buffer, pass) == 0){
        printf("Пароль верный");
    }
    else {
        printf("Пароль неправильный");
    }
    fclose(fp);
}