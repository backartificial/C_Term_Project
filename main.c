/**
 * File: Stack_ClassProject/queue.c
 * Assignment: Final_Project
 * Creation date: July 10, 2018
 * Last Modified: July 13, 2018 
 * 
 * Group Members:
 *    - James Grau
 *    - Bhavay Grover
 *    - Nathaniel Primo
 *    - Saud Siddiqui
 *
 **/

// Include the Needed Header Files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the FLUSH method used for clearing the buffer
#define FLUSH freopen(NULL, "r", stdin)

/**
 * 
 * This structure is used for creating a structure of a student
 * 
 * @item id: is the students ID
 * @item name: is the pointer to the students Name
 * @item schoolName: is the pointer to the name of the school that the student attends
 * @item programName: is the pointer to the  name of the program that the student is in
 * @item graduatingYear: is the year that the student is intended in graduating
 * @item gpa: is the students current GPA
 * @item next: is the pointer to the next item in the stack
 * 
 */
typedef struct node {
    // Declare the needed structure items
    unsigned int id;
    char *name;
    char *schoolName;
    char *programName;
    int graduatingYear;
    float gpa;
    struct node *nextPtr;
} student_t, Student, *StudentPtr;


// Define the function prototypes
void dequeue(StudentPtr, StudentPtr);
void enqueue(StudentPtr, StudentPtr);
void instructions();
void exitQueue(StudentPtr, StudentPtr);
void printTop(StudentPtr);
void printAll(StudentPtr);
void printStudent(StudentPtr);
char isEmpty(StudentPtr);
char isUniqueId(StudentPtr, int);

// Define Class Variables
static const size_t MAX_INPUT_LENGTH = (255 * sizeof(char));
char tmp[255] = {0};

/**
 * 
 * This method is used to run the core of the application section
 * 
 */
int main() {
    // Create the needed variables
    StudentPtr head = NULL; // Create a NULL student head structure
    StudentPtr tail = NULL; // Create a NULL student tail structure
    char choice; // Integer (int) to hold the menu choice of the user

    // Loop through and display the menu options
    while(1) {
        // Call the method used to display the menu options
        instructions();

        // Get the input from stdin and store it into the previousEntry variable
        fgets(tmp, MAX_INPUT_LENGTH, stdin);

        // Check if the entered menu option is valid
        if((choice = atoi(tmp)) != 0 && (choice >= 1 && choice <= 5)) {
            // Select the correct case based on the entered choice
            switch (choice) {
                // Case to print the first student
                case (1):
                    // Call the method to print the first student
                    printTop(head);
                break;
                
                // Case to add a student to the queue
                case (2):
                    // Call the method to add a student to the queue
                    enqueue(&head, &tail);
                break;
                
                // Case to remove a student from the queue
                case (3):
                    // Print the confirmation message to remove the user
                    printf("\nAre you sure that you want to remove the student? [ y/Y - Yes | n/N - No]: ");

                    // Store the entered character into the previousEntry variable
                    int ch = getchar();

                    // Check to make sure that the entered confirmation character is either y/Y
                    if(ch != EOF && (ch == 'y' || ch == 'Y')) {
                        // Remove the student from the queue
                        dequeue(&head, &tail);
                    }else{
                        // Print a new line for formatting
                        printf("\n");
                    }
                break;
                
                // Case to print all students in the queue
                case (4):
                    // Call the Print 
                    printAll(head);
                    break;
                case (5):
                    exitQueue(&head, &tail);
                    // exit(-1); //temp
                    break;
            }

        } else {
            // Display an invalid menu option error message
            printf("\nOops... That's an invalid menu option.  Please try again.\n\n");
        }

        // Flush the buffer
        FLUSH;
    }
}

char isEmpty(StudentPtr headPtr) {

    return headPtr == NULL;
}

void printAll(StudentPtr headPtr) {

    // if queue is empty
    if (headPtr == NULL) {

        puts("\n Queue is empty.\n");
    } // end if
    else {

        StudentPtr current = headPtr;

        puts("The queue is:");

        // while not end of queue
        while (current != NULL) {

            printStudent(current);
            current = current->nextPtr;
        } // end while
        printf("\n");

    } // end else
}

void enqueue(StudentPtr *headPtr, StudentPtr *tailPtr) {
// Create the needed function variables
    StudentPtr newStudent = (StudentPtr) malloc(sizeof(Student));

    // Check if memory cannot be allocate for the tmpStudent
    if (newStudent == NULL) {

        // Display an error message
        printf("Oops.. Memory cannot be allocated for adding a new student.  The application is closing as it cannot go any further.");

        // Exit the application in error
        exit(-1);
    }

    newStudent->nextPtr = NULL;

    // Stores the values to be validated
    static union {

        // Declare the needed member for the union
        size_t previousSize; // Stores the length of the previous string
        int previousInt; // Stores the value of the previous received integer
        float previousFloat; // Stores the value of the previous received floating point number
    } previousValidation;

    // Print prompt for entering student information
    printf("\nPlease Fill the Following Prompts to add a Student to the List:\n");

    // Perform a loop to get the Students ID
    do {

        // Display a prompt message for the students id
        printf("\n\tPlease Enter the Students ID (Number): ");

        // Get the input from stdin and store it into the previousEntry array
        fgets(tmp, MAX_INPUT_LENGTH, stdin);

        previousValidation.previousInt = atof(tmp);

        // Check if the entered ID is valid
        if (previousValidation.previousInt == 0 && *tmp != '0' || previousValidation.previousInt < 0 ||
            !isUniqueId(*headPtr, previousValidation.previousInt)) {

            // Display an error message
            printf("\n\tOops... That is an invalid Student Id.  Please try again.\n\n");

            // Set the tmpId to 0 for error and loop continuation
            previousValidation.previousInt = -1;
        } else {

            // Assign the tmpStudent it's id
            newStudent->id = previousValidation.previousInt;
        }

        // Flush the buffer
        FLUSH;
    } while (previousValidation.previousInt == -1);

    // Perform a loop to get the Students Name
    do {

        // Display prompt message getting the students name
        printf("\tPlease Enter the Students Name: ");

        // Get the input of the students name
        fgets(tmp, MAX_INPUT_LENGTH, stdin);

        // Remove the new line character from the string
        tmp[strcspn(tmp, "\n")] = 0;

        // The the String length + 1 for the entered student name
        previousValidation.previousSize = strlen(tmp) + 1;

        // Check if a name has been entered
        if (previousValidation.previousSize == 1) {

            // Display error message
            printf("\n\tOops... That's an invalid Student Name.  Please try again.\n\n");
        } else {

            // Allocate the space for the students name on the heap
            newStudent->name = (char *) malloc(previousValidation.previousSize * sizeof(char));

            // Check if memory cannot be allocate for the tmpStudent's name
            if (newStudent->name == NULL) {

                // Display an error message
                printf("Oops.. Memory cannot be allocated for adding a new student.  The application is closing as it cannot go any further.");

                // Exit the application in error
                exit(-1);
            }

            // Assign the student to it's name
            memcpy(newStudent->name, tmp, previousValidation.previousSize);
        }

        // Flush the Buffer
        FLUSH;
    } while (previousValidation.previousSize == 1);

    // Perform the loop and get the Students School Name
    do {

        // Display prompt message getting the students school name
        printf("\tPlease Enter the Students School Name: ");

        // Get the input of the students school name
        fgets(tmp, MAX_INPUT_LENGTH, stdin);

        // Remove the new line and return character from the string
        tmp[strcspn(tmp, "\n")] = 0;

        // The the String length + 1 for the entered school name
        previousValidation.previousSize = strlen(tmp) + 1;

        // Check if a school name has been entered
        if (previousValidation.previousSize == 1) {

            // Display error message
            printf("\n\tOops... That's an invalid School Name.  Please try again.\n\n");
        } else {

            // Allocate the space for the students school name on the heap
            newStudent->schoolName = (char *) malloc(previousValidation.previousSize * sizeof(char));

            // Check if memory cannot be allocate for the tmpStudent's school name
            if (newStudent->schoolName == NULL) {

                // Display an error message
                printf("Oops.. Memory cannot be allocated for adding a new student.  The application is closing as it cannot go any further.");

                // Exit the application in error
                exit(-1);
            }

            // Assign the student to it's school name
            memcpy(newStudent->schoolName, tmp, previousValidation.previousSize);
        }

        // Flush the Buffer
        FLUSH;
    } while (previousValidation.previousSize == 1);

    // Perform the loop and get the Students Program Name
    do {

        // Display prompt message getting the students program name
        printf("\tPlease Enter the Students Program Name: ");

        // Get the input of the students program name
        fgets(tmp, MAX_INPUT_LENGTH, stdin);

        // Remove the new line and return character from the string
        tmp[strcspn(tmp, "\n")] = 0;

        // Store the length of the string + 1 for the program name
        previousValidation.previousSize = strlen(tmp) + 1;

        // Check if a program name has been entered
        if (previousValidation.previousSize == 1) {

            // Display error message
            printf("\n\tOops... That's an invalid Program Name.  Please try again.\n\n");
        } else {

            // Allocate the space for the students program name on the heap
            newStudent->programName = (char *) malloc(previousValidation.previousSize * sizeof(char));

            // Check if memory cannot be allocate for the tmpStudent's program name
            if (newStudent->programName == NULL) {

                // Display an error message
                printf("Oops.. Memory cannot be allocated for adding a new student.  The application is closing as it cannot go any further.");

                // Exit the application in error
                exit(-1);
            }

            // Assign the student to it's program name
            memcpy(newStudent->programName, tmp, previousValidation.previousSize);
        }

        // Flush the Buffer
        FLUSH;
    } while (previousValidation.previousSize == 1);

    // Perform a loop to get the Students graduating year
    do {

        // Display the prompt for the students graduating year
        printf("\tPlease Enter the Students Graduating Year: ");

        // Get the input from stdin and store it into the previousEntry array
        fgets(tmp, MAX_INPUT_LENGTH, stdin);

        previousValidation.previousInt = atoi(tmp);

        // Check if the entered year is valid
        if (previousValidation.previousInt == 0 || previousValidation.previousInt < 2018) {

            // Display an error message
            printf("\n\tOops... That's an invalid Graduating Year.  Please try again.\n\n");

            // Set the tmpGraduatingYear to 0 for error and loop continuation
            previousValidation.previousInt = 0;
        } else {

            // Assign the tmpStudent it's graduating year
            newStudent->graduatingYear = previousValidation.previousInt;
        }

        // Flush the buffer
        FLUSH;
    } while (previousValidation.previousInt == 0);

    // Perform a loop to get the Students GPA
    do {

        // Display the prompt for the students GPA
        printf("\tPlease Enter the Students GPA: ");

        // Get the input from the user
        fgets(tmp, MAX_INPUT_LENGTH, stdin);

        previousValidation.previousFloat = atof(tmp);

        // Check if the entered GPA is valid
        if (previousValidation.previousFloat == 0 && *tmp != '0' || previousValidation.previousFloat < 0) {

            // Display an error message
            printf("\n\tOops... That's an invalid GPA.  Please try again.\n\n");

            // Set the tmpGpa to 0 for error and loop continuation
            previousValidation.previousFloat = -1;
        } else {

            // Assign the tmpStudent it's GPA
            newStudent->gpa = previousValidation.previousFloat;
        }

        // Flush the buffer
        FLUSH;
    } while (previousValidation.previousFloat == -1);

    // Puts the newly created student at the top of the list while pushing everything down
    if (isEmpty(*headPtr)) {

        *headPtr = newStudent;
        *tailPtr = newStudent;
    } else {

        (*tailPtr)->nextPtr = newStudent;
        *tailPtr = newStudent;
    }

    // Print success message and new line for formatting
    printf("\n\tStudent Added Successfully!\n\n");
}


// remove node from queue head
void dequeue(StudentPtr *headPtr, StudentPtr *tailPtr) {

    if (isEmpty(*headPtr)) {

        printf("Cannot deque because no student has been added");
        return;
    }

    StudentPtr lostNode = (*headPtr);

    *headPtr = (*headPtr)->nextPtr;

    if (isEmpty(*headPtr)) { // if queue is empty at this point
        // then set tail-pointer to NULL
        *tailPtr = NULL;
    }

    //deallocate memory of dequeued node
    free(lostNode->name);
    free(lostNode->schoolName);
    free(lostNode->programName);
    free(lostNode);

}

void printTop(StudentPtr student) {
    if(student == NULL) {
        printf("\nQueue is empty. ");
        printf("\n");
    }else{
        printStudent(student);
    }
}

void printStudent(StudentPtr student) {
    // Display the separator and student information
    printf("-----------------------------------------------------\n");
    printf("ID: %d\nName: %s\nGraduating Year: %d\nGPA: %.2lf\nProgram Name: %s\nSchool Name: %s\n", student->id,
           student->name, student->graduatingYear, student->gpa, student->programName, student->schoolName);
    printf("-----------------------------------------------------\n\n");
}

/**
 * 
 * This function is used to display the menu of the stack application
 * 
 */
void instructions() {
    // Display the menu options
    printf("Student List Management"
           "\n------------------------------------------------"
           "\n1. Print First Student"
           "\n2. Add Student"
           "\n3. Remove First Student"
           "\n4. Print Student List"
           "\n5. Close Section"
           "\n------------------------------------------------"
           "\nPlease Enter Menu Option: ");
}


void exitQueue(StudentPtr *head, StudentPtr *tail) {

    StudentPtr current = *head;

    while (current != NULL) {

        dequeue(&current, tail);
    }

    printf("\nexited..\n");

    exit(0);

}


/**
 *
 * This function is used to iterate through the stack and check if the passed id is unique
 *
 * @param head: is the first item in the stack
 * @param id: is the ID to check if unique among the stack
 * @return [true - When the passed id is unique | false - When the passed id is not unique]
 *
 */
char isUniqueId(StudentPtr head, int id) {

    // Create a previousEntry student that points to the head of the student stack used for iteration
    StudentPtr current = head;

    // Look through the student stack while the next item is not NULL
    while (current != NULL) {

        // Removed redundant NULL check Check if the iterated student ID is the same as the passed id
        if (current->id == id) {

            // Return false (passed id is not unique)
            return 0;
        }

        // Move to the next item in the stack
        current = current->nextPtr;
    }

    // Return true (passed id is unique)
    return 1;
}
