#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function declarations */
void addStudent();
void viewStudents();
void searchStudent();
void deleteStudent();

/* Structure */
struct student {
    char first_name[20];
    char last_name[20];
    int roll_no;
    char class_name[10];
    char address[30];
    float percentage;
};

int main() {
    int choice = 0;

    while (choice != 5) {
        printf("\n=============================================");
        printf("\n   STUDENT DATABASE MANAGEMENT SYSTEM");
        printf("\n=============================================");
        printf("\n1. Add Student Record");
        printf("\n2. View Student Records");
        printf("\n3. Search Student");
        printf("\n4. Delete Student Record");
        printf("\n5. Exit");
        printf("\n---------------------------------------------");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            viewStudents();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            deleteStudent();
            break;
        case 5:
            printf("\nThank you for using this system.\n");
            exit(0);
        default:
            printf("\nInvalid choice! Try again.\n");
        }
    }

    return 0;
}

/* Add student record */
void addStudent() {
    FILE *fp;
    struct student s;
    char choice;

    fp = fopen("student_info.dat", "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    do {
        printf("\n----- Add Student Information -----\n");

        printf("First Name: ");
        scanf("%s", s.first_name);

        printf("Last Name: ");
        scanf("%s", s.last_name);

        printf("Roll Number: ");
        scanf("%d", &s.roll_no);

        printf("Class: ");
        scanf("%s", s.class_name);

        printf("Address: ");
        scanf("%s", s.address);

        printf("Percentage: ");
        scanf("%f", &s.percentage);

        fwrite(&s, sizeof(struct student), 1, fp);
        printf("\nRecord added successfully!\n");

        printf("\nAdd another record? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    fclose(fp);
}

/* View all student records */
void viewStudents() {
    FILE *fp;
    struct student s;

    fp = fopen("student_info.dat", "rb");
    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\n----- Student Records -----\n");

    while (fread(&s, sizeof(struct student), 1, fp)) {
        printf("\nName       : %s %s", s.first_name, s.last_name);
        printf("\nRoll No    : %d", s.roll_no);
        printf("\nClass      : %s", s.class_name);
        printf("\nAddress    : %s", s.address);
        printf("\nPercentage : %.2f", s.percentage);
        printf("\n-------------------------------");
    }

    fclose(fp);
}

/* Search student by roll number */
void searchStudent() {
    FILE *fp;
    struct student s;
    int roll, found = 0;

    fp = fopen("student_info.dat", "rb");
    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\nEnter roll number to search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct student), 1, fp)) {
        if (s.roll_no == roll) {
            found = 1;
            printf("\n----- Student Found -----\n");
            printf("Name       : %s %s", s.first_name, s.last_name);
            printf("\nRoll No    : %d", s.roll_no);
            printf("\nClass      : %s", s.class_name);
            printf("\nAddress    : %s", s.address);
            printf("\nPercentage : %.2f\n", s.percentage);
            break;
        }
    }

    if (!found) {
        printf("\nStudent record not found!\n");
    }

    fclose(fp);
}

/* Delete student record */
void deleteStudent() {
    FILE *fp, *temp;
    struct student s;
    int roll, found = 0;

    fp = fopen("student_info.dat", "rb");
    temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL) {
        printf("\nError opening file!\n");
        return;
    }

    printf("\nEnter roll number to delete: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct student), 1, fp)) {
        if (s.roll_no == roll) {
            found = 1;
        } else {
            fwrite(&s, sizeof(struct student), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("student_info.dat");
    rename("temp.dat", "student_info.dat");

    if (found) {
        printf("\nRecord deleted successfully!\n");
    } else {
        printf("\nRecord not found!\n");
    }
}
