#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <direct.h>
#include <ctype.h>

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
void edit();
void ex();
int is_number(const char *str);

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
        printf("5 - edit a specific form\n");
        printf("0 - exit\n");
        printf("Enter your choice: ");
        
        int choose;
        if (scanf("%d", &choose) != 1) {
            printf("Invalid input! Please enter a number.\n");
            system("pause");
            continue;
        }

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
            case 5:
                edit();
                break;
            case 0:
                ex();
                break;
            default:
                printf("Invalid choice! Try again.\n");
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
    scanf(" %[^\n]s", reg.fio);

    while (1) {
        printf("Enter your age: ");
        if (scanf("%d", &reg.age) != 1 || reg.age < 1) {
            printf("Invalid age! Please enter a positive integer.\n");
            while (getchar() != '\n');
        } else {
            break;
        }
    }

    while (1) {
        printf("Enter your course: ");
        if (scanf("%d", &reg.course) != 1 || reg.course < 1) {
            printf("Invalid course! Please enter a positive integer.\n");
            while (getchar() != '\n'); 
        } else {
            break;
        }
    }

    _mkdir("7");

    char file[50];
    FILE *fp = NULL;

    for (int i = 0; i < 1000; i++) {
        sprintf(file, "7/student_%d", i);
        fp = fopen(file, "rb");
        if (fp == NULL) { 
            reg.ID = i; 
            break;
        }
        fclose(fp);
    }

    fp = fopen(file, "wb");
    if (fp == NULL) {
        printf("Error creating file! Please check file permissions.\n");
        system("pause");
        return;
    }

    fwrite(&reg, sizeof(reg), 1, fp); 
    fclose(fp);

    printf("Student data saved successfully! ID: %d\n", reg.ID);
    system("pause");
}





void view_form() {
    system("cls");
    printf("Enter student's ID to view: ");
    int n;
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Invalid ID!\n");
        system("pause");
        return;
    }

    char path[50];
    sprintf(path, "7/student_%d", n);
    FILE* fp = fopen(path, "rb");
    if (fp == NULL) {
        printf("Could not find a student.\n");
        system("pause");
        return;
    }

    struct Student form;
    fread(&form, sizeof(form), 1, fp);
    fclose(fp);

    printf("Student details:\n");
    printf("FIO: %s\n", form.fio);
    printf("Age: %d\n", form.age);
    printf("Course: %d\n", form.course);
    printf("ID: %d\n", form.ID);
    system("pause");
}

void list() {
    system("cls");
    struct Student view;
    char file[50];
    FILE *fp = NULL;
    for (int i = 0; i < 1000; i++) {
        sprintf(file, "7/student_%d", i);
        fp = fopen(file, "rb");
        if (fp != NULL) { 
            fread(&view, sizeof(view), 1, fp);
            printf("Student ID:%d\t", view.ID);
            printf("FIO: %s\t", view.fio);
            printf("Age: %d\t", view.age);
            printf("Course: %d\n", view.course);
        }
        fclose(fp);
    }
    system("pause");
}

void find() {
    system("cls");
    printf("Enter search query: ");
    char query[50];
    scanf(" %[^\n]s", query);

    struct Student student;
    char file[50];
    FILE *fp = NULL;
    int found = 0;

    for (int i = 0; i < 1000; i++) {
        sprintf(file, "7/student_%d", i);
        fp = fopen(file, "rb");

        if (fp != NULL) {
            fread(&student, sizeof(student), 1, fp);
            fclose(fp);

            if (strstr(student.fio, query) != NULL) {
                printf("Student found:\n");
                printf("ID: %d\n", student.ID);
                printf("FIO: %s\n", student.fio);
                printf("Age: %d\n", student.age);
                printf("Course: %d\n", student.course);
                printf("\n");
                found = 1;
            }

            if (is_number(query)) {
                int query_num = atoi(query);
                if (student.age == query_num || student.course == query_num || student.ID == query_num) {
                    printf("Student found:\n");
                    printf("ID: %d\n", student.ID);
                    printf("FIO: %s\n", student.fio);
                    printf("Age: %d\n", student.age);
                    printf("Course: %d\n", student.course);
                    printf("\n");
                    found = 1;
                }
            }
        }
    }

    if (!found) {
        printf("No students found matching the query.\n");
    }

    system("pause");
}



void edit() {
    system("cls");
    printf("Enter student's ID: ");
    int n;
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Invalid ID!\n");
        while (getchar() != '\n'); 
        system("pause");
        return;
    }

    char path[50];
    sprintf(path, "7/student_%d", n);

    FILE* fp = fopen(path, "rb");
    if (fp == NULL) {
        printf("Could not find a student with ID %d.\n", n);
        system("pause");
        return;
    }

    struct Student form;
    fread(&form, sizeof(form), 1, fp);
    fclose(fp);

    printf("Student details:\n");
    printf("Student ID: %d\n", form.ID);
    printf("FIO: %s\n", form.fio);
    printf("Age: %d\n", form.age);
    printf("Course: %d\n", form.course);

    printf("Choose the data to edit:\n");
    printf("1 - Delete student\n");
    printf("2 - Edit FIO\n");
    printf("3 - Edit age\n");
    printf("4 - Edit course\n");
    printf("0 - Exit\n");
    printf("Enter your choice: ");

    int choice;
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input! Please enter a number.\n");
        while (getchar() != '\n'); 
        system("pause");
        return;
    }

    switch (choice) {
        case 1: { 
            printf("Are you sure you want to delete this student? Type 'yes' to confirm: ");
            char confirm[4];
            scanf("%3s", confirm);
            if (strcmp(confirm, "yes") == 0) {
                if (remove(path) == 0) {
                    printf("Student deleted successfully.\n");
                } else {
                    perror("Error deleting student file"); 
                }
            } else {
                printf("Deletion cancelled.\n");
            }
            system("pause");
            return;
}


        case 2: { 
            printf("Enter new FIO: ");
            scanf(" %[^\n]s", form.fio);
            break;
        }
        case 3: { 
            while (1) {
                printf("Enter new age: ");
                if (scanf("%d", &form.age) == 1 && form.age > 0) break;
                printf("Invalid age! Please enter a positive integer.\n");
                while (getchar() != '\n'); 
            }
            break;
        }
        case 4: { 
            while (1) {
                printf("Enter new course: ");
                if (scanf("%d", &form.course) == 1 && form.course > 0) break;
                printf("Invalid course! Please enter a positive integer.\n");
                while (getchar() != '\n'); 
            }
            break;
        }
        case 0: 
            printf("Exiting edit mode.\n");
            return;
        default:
            printf("Invalid choice! Try again.\n");
            system("pause");
            return;
    }


    fp = fopen(path, "wb");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        system("pause");
        return;
    }
    fwrite(&form, sizeof(form), 1, fp);
    fclose(fp);

    printf("Changes saved successfully.\n");
    system("pause");
}


void ex() {
    printf("Exiting program. Goodbye!\n");
    exit(0);
}

int is_number(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0; 
        }
    }
    return 1; 
}