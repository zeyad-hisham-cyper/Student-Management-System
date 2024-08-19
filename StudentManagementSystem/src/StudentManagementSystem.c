/*
 ============================================================================
 Name        : StudentManagementSystem.c
 Author      : Zeyad Hisham Elsayed
 Version     :
 Description : Student Management System Project
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define MINIMUM_UNI_STUDENT_AGE 15
#define MINIMUM_GPA 0.0
#define MAXIMUM_GPA 4.0

typedef struct {
	int id; /* Student ID */
	char name[50]; /* Student Name */
	int age; /* Student Age */
	float gpa; /* Student GPA */
} student;

/* Defining the node structure */
struct node {
	student data;
	struct node *next;
};

struct node *head = NULL;

void displayMenu(void);
int getUserChoice(void);
void getStudentData(student *s);
struct node* checkIfStudentExist(int id);
void addStudent(const student *const ptr);
void displayStudents(void);
void searchStudentByID(int id);
void updateStudent(int id);
float calculateAverageGPA(void);
void searchHighestGPA(void);
void deleteStudent(int id);
void freeAllStudents(void);
void saveStudentData(const char *filename);

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	int choice;
	student s;
	int id;
	const char *fileName = "Students.csv";
	printf("__          __  _                            _                           _____           _           _\n");
	printf("\\ \\        / / | |                          (_)                         |  __ \\         (_)         | |\n");
	printf(" \\ \\  /\\  / /__| | ___ ___  _ __ ___   ___   _ _ __    _ __ ___  _   _  | |__) | __ ___  _  ___  ___| |_\n");
	printf("  \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | | '_ \\  | '_ ` _ \\| | | | |  ___/ '__/ _ \\| |/ _ \\/ __| __|\n");
	printf("   \\  /\\  /  __/ | (_| (_) | | | | | |  __/ | | | | | | | | | | | |_| | | |   | | | (_) | |  __/ (__| |_\n");
	printf("    \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___| |_|_| |_| |_| |_| |_|\\__, | |_|   |_|  \\___/| |\\___|\\___|\\__|\n");
	printf("                                                                  __/ |                _/ |\n");
	printf("                                                                 |___/                |__/\n\n");
	printf("\nc:\\Users\\>I AM AT YOUR COMMAND\n\n");
	printf("Made By	   : Eng. Zeyad Hisham\n");
	printf("Github User: zeyad-hisham-cyper\n\n");
	printf("*********************************************************************************************************\n\n");
	do {
		displayMenu();
		choice = getUserChoice();
		switch (choice) {
		case 1:
			getStudentData(&s);
			addStudent(&s);
			break;
		case 2:
			displayStudents();
			break;
		case 3:
			printf("Enter Student ID: ");
			scanf("%d", &id);
			searchStudentByID(id);
			break;
		case 4:
			printf("Enter Student ID: ");
			scanf("%d", &id);
			updateStudent(id);
			break;
		case 5:
			printf("Enter Student ID: ");
			scanf("%d", &id);
			deleteStudent(id);
			break;
		case 6:
			printf("Average GPA: %.2f\n", calculateAverageGPA());
			break;
		case 7:
			searchHighestGPA();
			break;
		case 8:
			printf("Thanks, Have a Nice Day :)\nExiting...\n");
			saveStudentData(fileName);
			freeAllStudents();
			break;
		default:
			printf("Invalid Choice, Please Enter Number from 1 - 8 \n");
		}
	} while (choice != 8);
	return 0;
}
/*
 * Function Description: Function to Display User Choices
 * Function Arguments  : Void
 * Function Returns    : Void
 */
void displayMenu(void) {
	printf("1. Add Student\n");
	printf("2. Display Students\n");
	printf("3. Search Student by ID\n");
	printf("4. Update Student Information\n");
	printf("5. Delete Student\n");
	printf("6. Calculate Average GPA\n");
	printf("7. Search for Student With Highest GPA\n");
	printf("8. Exit\n");
	printf("========================\n");
}
/*
 * Function Description: Function to Take User Choice
 * Function Arguments  : Void
 * Function Returns    : User Choice
 */
int getUserChoice(void) {
	int choice = 0;
	printf("Enter Choice: ");
	while(scanf("%d", &choice) != 1){
		printf("Invalid Input, Please Enter Integer Number\n");
		while(getchar() != '\n'); // to discard unwanted characters and avoiding infinite loop
	}

	/*To ensure the user entered a valid choice I used the following condition*/
	printf("========================\n");
	return choice;
}
/*
 * Function Description: Function to Take Student Data
 * Function Arguments  : Address of student structure
 * Function Returns    : void
 */
void getStudentData(student *s) {
	/*
	 * scanf function return 0 if failed or 1 of executed successfully.
	 * I use this property to validate if the user entered a valid input or not
	 */
	printf("Enter Student ID: ");
	while (scanf("%d", &s->id) != 1) {
		printf("Invalid Input, Please Try Again ^_^\n");
		while (getchar() != '\n');
	}
	printf("Enter Student Name: ");
	while (scanf("%s", s->name) != 1) {
		printf("Invalid Input, Please Try Again ^_^\n");
		while (getchar() != '\n');
	}
	printf("Enter Age: ");
	while (scanf("%d", &s->age) != 1 || s->age < MINIMUM_UNI_STUDENT_AGE) {
		printf("Invalid Input, Please Try Again ^_^\n");
		while (getchar() != '\n');
	}
	printf("Enter GPA: ");
	while (scanf("%f", &s->gpa) != 1 || (s->gpa < MINIMUM_GPA) || (s->gpa > MAXIMUM_GPA)) {
		printf("Invalid Input, Please Try Again ^_^\n");
		while (getchar() != '\n');
	}
	printf("========================\n");
}
/*
 * Function Description: Function to Check if the Student Exists or not
 * Function Arguments  : Student ID
 * Function Returns    : Pointer to the node if the student exists
 *                       NULL if the student does not exist
 */
struct node* checkIfStudentExist(int id) {
    struct node *current = head;
    while (current != NULL) {
        if (current->data.id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}
/*
 * Function Description: Function to Add Student at the end of the Linked List
 * Function Arguments  : address of the student structure
 * The Address stored in const pointer to const structure as the data or its address are unchangeable
 * Function Returns    : void
 */
void addStudent(const student *const ptr) {
    // Check if the Student ID is Exists using "checkIfStudentExist" Function
    if (checkIfStudentExist(ptr->id) != NULL) {
        printf("This Student ID is Already Exists\n");
        printf("========================\n");
        return;
    }

    struct node *current = NULL;
    struct node *link = (struct node*) malloc(sizeof(struct node));
    if (link == NULL) {
        printf("Error!! Can't Allocate Memory for the New Student\n");
        printf("========================\n");
        return;
    }

    link->data = *ptr;
    link->next = NULL;

    if (head == NULL) {
        head = link;
    } else {
        current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = link;
    }

    printf("Student Added Successfully!\n");
    printf("========================\n");
}
/*
 * Function Description: Function to All students data in the Linked List
 * Function Arguments  : void
 * Function Returns    : void
 */
void displayStudents(void) {
	struct node *current = head;
	if (current == NULL) {
		printf("Error!! The List is Empty\n");
		printf("========================\n");
		return;
	}
	printf("Students Are: \n");
	while (current != NULL) {
		printf("[ ID: %d, Name: %s, Age: %d, GPA: %0.2f ]\n", current->data.id,
				current->data.name, current->data.age, current->data.gpa);
		current = current->next;
	}
	printf("========================\n");
}
/*
 * Function Description: Function to Search for Student with his ID
 * Function Arguments  : Student ID
 * Function Returns    : void
 */
void searchStudentByID(int id) {
	struct node *current = head;
	if (current == NULL) {
		printf("Error!! The List is Empty\n");
		printf("========================\n");
		return;
	}
	while (current != NULL) {
		if (current->data.id == id) {
			printf("Student Found:\n");
			printf("[ ID: %d, Name: %s, Age: %d, GPA: %0.2f ]\n",
					current->data.id, current->data.name, current->data.age,
					current->data.gpa);
			printf("========================\n");
			return;
		}
		current = current->next;
	}
	printf("There is no Student with this ID\n");
	printf("========================\n");
}
/*
 * Function Description: Function to Update Student Data with his ID
 * Function Arguments  : Student ID
 * Function Returns    : void
 */
void updateStudent(int id) {
    struct node *studentNode = checkIfStudentExist(id);
    if (studentNode == NULL) {
        printf("The Student is not Found\n");
        printf("========================\n");
        return;
    }

    printf("Enter Student Name: ");
    while (scanf("%s", studentNode->data.name) != 1) {
        printf("Invalid Input, Please Try Again ^_^\n");
        while (getchar() != '\n');
    }

    printf("Enter Age: ");
    while (scanf("%d", &studentNode->data.age) != 1 || studentNode->data.age < MINIMUM_UNI_STUDENT_AGE) {
        printf("Invalid Input, Please Try Again ^_^\n");
        while (getchar() != '\n');
    }

    printf("Enter GPA: ");
    while (scanf("%f", &studentNode->data.gpa) != 1 || (studentNode->data.gpa < MINIMUM_GPA) || (studentNode->data.gpa > MAXIMUM_GPA)) {
        printf("Invalid Input, Please Try Again ^_^\n");
        while (getchar() != '\n');
    }

    printf("========================\n");
    printf("Student Updated Successfully!\n");
    printf("========================\n");
}


/*
 * Function Description: Function to Calculate the Average GPA
 * Function Arguments  : void
 * Function Returns    : Average GPA
 */
float calculateAverageGPA(void) {
	float avg = 0.0, sum = 0.0;
	int counter = 0;
	struct node *current = head;
	if (current == NULL) {
		printf("Error!! Linked List is Empty\n");
		printf("========================\n");
		return avg;
	}
	while (current != NULL) {
		counter++;
		sum += current->data.gpa;
		current = current->next;
	}
	avg = sum / counter;
	return avg;
}
/*
 * Function Description: Function to Search for the Highest GPA in the List
 * Function Arguments  : void
 * Function Returns    : void
 */
void searchHighestGPA(void) {
	struct node *current = head;
	struct node *maxLocation = current;
	float max = 0.0;
	if (current == NULL) {
		printf("Error!! List is Empty\n");
		printf("========================\n");
		return;
	} else {
		max = current->data.gpa;
		while (current != NULL) {
			if (current->data.gpa > max) {
				max = current->data.gpa;
				maxLocation = current;
			}
			current = current->next;
		}
		printf("Student With the Highest GPA: \n");
		printf("[ ID: %d, Name: %s, Age: %d, GPA: %0.2f ]\n",
				maxLocation->data.id, maxLocation->data.name,
				maxLocation->data.age, maxLocation->data.gpa);
		printf("========================\n");
		return;
	}

}
/*
 * Function Description: Function to Delete Student
 * Function Arguments  : Student ID
 * Function Returns    : void
 */
void deleteStudent(int id) {
    struct node *current = head;
    struct node *prev = NULL;

    if (current == NULL) {
        printf("Error!! The List is Empty\n");
        printf("========================\n");
        return;
    }

    struct node *studentNode = checkIfStudentExist(id);
    if (studentNode == NULL) {
        printf("The Student is not Exist\n");
        printf("========================\n");
        return;
    }

    // If the student to be deleted is the head of the list
    if (studentNode == head) {
        head = head->next;
        free(studentNode);
        printf("Student Deleted Successfully\n");
        printf("========================\n");
        return;
    }

    // Find the previous node
    while (current->next != studentNode) {
        current = current->next;
    }
    prev = current;

    prev->next = studentNode->next;
    free(studentNode);

    printf("Student Deleted Successfully\n");
    printf("========================\n");
}
/*
 * Function Description: Function to Free all Lists from heap after user decide to exit
 * Function Arguments  : void
 * Function Returns    : void
 */
void freeAllStudents(void) {
	struct node *current = head;
	struct node *temp = NULL;
	while (current != NULL) {
		temp = current->next;
		free(current);
		current = temp;
	}
	head = NULL;
}
/*
 * Function Description: For Better user experience This function to save the data in CSV File.
 * Function Arguments  : void
 * Function Returns    : void
 */
void saveStudentData(const char *filename) {
	FILE *file = fopen(filename, "w");
	if (!file) {
		printf("Error while openning the file\n");
		return;
	}
	struct node *current = head;
	if (current == NULL) {
		printf("List is Empty\n");
		fclose(file);
		return;
	}
	fprintf(file, "ID,Name,Age,GPA\n");
	while (current != NULL) {
		fprintf(file, "%d,%s,%d,%0.2f\n", current->data.id, current->data.name,
				current->data.age, current->data.gpa);
		current = current->next;
	}
	fclose(file);
}
