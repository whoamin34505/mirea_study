#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

struct Student {
    char fio[50];
    int ID;
    int age;
    int course;
};

void registration();
void view_form();
void list();
void find();
void ex();

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);    
    while (1) {
        system("cls");
        printf("Welcome to students database!\n");
        printf("Choose an option: \n");
        printf("1 - user registration\n");
        printf("2 - displaying a specific form\n");
        printf("3 - displaying the general list of students\n");
        printf("4 - student search by various data\n");
        printf("0 - exit\n");
        printf("Enter your choice: ");
        int choose;
        scanf("%d", &choose);
        switch (choose) {
            case 1:
                registration();
                break;
            case 2:
                view_form();
                break;
            case 3:
                list();
                break;
            case 4:
                find();
                break;
            case 0:
                ex();
                break;
            default:
                printf("You are invalid! Try again.\n");
                system("pause");
                break;
        }
    }
    return 0;
}

void registration() {
    system("cls");
    struct Student reg;

    printf("Enter your FIO: ");
    scanf("%s",&reg.fio);

    printf("Enter your age: ");
    scanf("%d", &reg.age);

    printf("Enter your course: ");
    scanf("%d", &reg.course);


    char file[50];
    FILE *fp = NULL;
    for (int i = 0; i < 1000; i++) {
        sprintf(file, "7/student_%d", i);
        fp = fopen(file, "r");
        if (fp == NULL) { 
            reg.ID = i;
            break;
        }
        fclose(fp);
    }

    if (fp == NULL) {
        fp = fopen(file, "w");
        if (fp == NULL) {
            printf("Error creating file!\n");
            system("pause");
            return;
        }
        fprintf(fp, "%s\n%d\n%d\n%d\n", reg.fio, reg.age, reg.course, reg.ID);
        fclose(fp);
        printf("Student data saved successfully!\n");
    } else {
        printf("Error: Could not find an available file slot.\n");
    }
    system("pause");
}

void view_form() {
    system("cls");
    printf("Enter student's ID to view: ");
    int n;
    scanf("%d",&n);
    char path[50];
    sprintf(path,"7/student_%s",n);
    FILE* fp = fopen(path, "r");
    if (fp == NULL) {
        printf("Counld not find a student."); 
    }
    
    fclose(fp);
    system("pause");
}

void list() {
    system("cls");
    printf("List of students functionality is not implemented yet.\n");
    system("pause");
}

void find() {
    system("cls");
    printf("Search functionality is not implemented yet.\n");
    system("pause");
}

void ex() {
    exit(0);
}
