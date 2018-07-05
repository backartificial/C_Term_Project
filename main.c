/**
 * File: Stack_ClassProject_Part_A/structure.c
 * Assignment: Final_Project
 * Creation date: July 3, 2018
 * Last Modified: July 5, 2018 
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
#include <stdbool.h>
#include <string.h>

// Define the FLUSH method used for clearing the buffer
#define FLUSH freopen(NULL, "r", stdin);

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
    int id;
    char *name;
    char *schoolName;
    char *programName;
    int graduatingYear;
    float gpa;
    struct node *next;
} student_t;

// Define the function prototypes
void *pop(student_t*); // Function used to remove an item from the stack
void *push(student_t*); // Function used to add an item to the stack
void *printAll(student_t*); // Function used to print the students in the stack
void *exitStack(student_t*); // Function used to exit out of the application section
void *printTop(student_t*); // Function used to print only the top item of the stack
void *printStudent(student_t*); // Function used to display the actual student information to the console
bool checkUniqueID(student_t*, int); // Function used to check if the passed int (ID) refers to a unique ID
void instructions();

/**
 * 
 * This method is used to run the core of the application section
 * 
 * @return 0 on application ending
 * 
 */
int main() {
    // Create the needed variables
    void *(*methods[])(student_t *) = {printTop, push, pop, printAll, exitStack}; // Store pointer to the function
    student_t *head = NULL; // Create a NULL student structure
    int choice; // Int to hold the menu choice of the user

    // Loop through and display the menu options
    while(true) {
        // Call the method used to display the menu options
        instructions();

        // Check if the entered menu option is valid
        if(scanf("%d", &choice) && choice >= 1 && choice <= 5) {
            // Flush the buffer
            FLUSH;
            
            // Calls the correct method from the method array
            student_t *result = (student_t *)(*methods[choice - 1])(head);

            // Check if the result of the called method is not NULL
            if(result) {
                // Set the head value to the result from the function
                head = result;
            }
        }else{
            // Display an invalid menu option error message
            printf("\nOops... That is an invalid menu option.  Please try again.\n\n");
            
            // Flush the buffer
            FLUSH;
        }
    }
    
    // Return successful
    return 0;
}

/**
 * 
 * This function is used to print the top student in the stack
 * 
 * @param head: is the top item in the student stack
 *
 */
void *printTop(student_t *head) {
    // Check if the head item of the stack is empty
    if (head == NULL) {
        // Display an empty student stack message
        printf("\nLooks like the Student Stack is empty.  Please add an item to the stack to view to the top item.\n\n");
    }else{
        // Call the function that prints student information in the console for the first (top) student in the stack
        printStudent(head);
    }
    
    // Return NULL as nothing is being changed on the stack
    return NULL;
}

/**
 * 
 * This function is used to remove the top item from the stack
 * 
 * @param head: is the first (top) student in the stack
 * @return the new head stack item
 * 
 */
void *pop(student_t *head) {
    // Check if the head is NULL
    if (head == NULL) {
        // Display error message 
        printf("Oops... Unable to remove student from stack as there are not students in the stack.");
        
        // Return NULL as nothing has changed on the stack
        return NULL;
    }else{
        // Create a new student item that holds the head item
        student_t *popped = head;

        // Move the head to the next stack item
        head = head->next;

        // Check if the popped item name is not NULL
        if (popped->name) {
            // Free the memory assignment of the popped students name
            free(popped->name);
        }

        // Check if the popped item school name is not NULL
        if (popped->schoolName) {
            // Free the memory assignment of the popped students school name
            free(popped->schoolName);
        }

        // Check if the popped item program name is not NULL
        if (popped->programName) {
            // Free the memory assignment of the popped students program name
            free(popped->programName);
        }

        // Free the memory assignment of the popped student item
        free(popped);

        // Return the new head of the students stack
        return head;
    }
}

/**
 * 
 * This function is used to add an item to the stack
 * 
 * @param head: is the top item of the stack
 * @return the new top item of the stack
 * 
 */
void *push(student_t *head) {
    // Create the needed function variables
    student_t* tmpStudent;
    char tmp[255];
    
    // Check if memory cannot be allocate for the tmpStudent
    if(tmpStudent == NULL) {
        // Display an error message
        printf("Oops.. Memory cannot be allocated for adding a new student.  The application is closing as it cannot go any further.");
        
        // Exit the application in error
        exit(-1);
    }
    
    
    int tmpId;
    char *tempName;
    char *tempSchoolName;
    char *tempProgramName;
    int tempGraduatingYear = 0;
    float tempGpa = 0.0;
    int len = 0;
    int len2 = 0;
    int len3 = 0;

    // Perform a loop to get the Students ID
    do {
        // Display a prompt message for the students id
        printf("\nPlease Enter the Student's ID (Number): ");
        
        // Check if the entered ID is valid
        if (scanf("%d", &tmpId) || tmpId < 1 || !checkUniqueID(head, tmpId)) {
            // Display an error message
            printf("\nOops... That is an invalid Student Id.  Please try again.\n\n");
            
            // Set the tmpId to 0 for error and loop continuation
            tmpId = 0;
        }else{
            // Assign the tmpStudent it's id
            tmpStudent->id = tmpId;
        }
    } while(tmpId == 0); // Loop while tmpId is 0

    // Perform a loop to get the Students Name
    do {
        // Display prompt message getting the students name
        printf("Please Enter the Student's Name: ");
        
        // Get the input of the 
        fgets (tempName, 39, stdin);
        tempName[strcspn(tempName, "\n")] = 0;
        tempName[strcspn(tempName, "\r")] = 0;
        len = strlen(tempName);
    } while(tempName == NULL || len == 0);

    tempSchoolName = malloc(sizeof (char)*80);

    do {
        printf("Please enter a valid school name \n");
        fgets (tempSchoolName, 79, stdin);
        tempName[strcspn(tempSchoolName, "\n")] = 0;
        len2 = strlen(tempSchoolName);
    } while(tempSchoolName == NULL || len2 < 2);

    tempProgramName = malloc(sizeof (char)*80);

    do {
        printf("Please enter a valid program name \n");
        fgets (tempProgramName, 79, stdin);
        tempName[strcspn(tempProgramName, "\n")] = 0;
        len3 = strlen(tempProgramName);

    } while(tempProgramName == NULL || len3 < 2);


    do {
        printf("Please enter a valid graduating year\n");
        scanf("%d",&tempGraduatingYear);
        FLUSH;
    } while(tempGraduatingYear == 0 );

    do {
        printf("Please enter a GPA\n");
        scanf("%f",&tempGpa);
        FLUSH;
    } while(tempGpa == 0.0);

    // create space for new node using malloc()
    newPtr = (student_t*)malloc(sizeof(student_t));

    if(newPtr != NULL) {  // new node pointer is not NULL
          // Push new node onto stack
          newPtr->id = tmpId;
          newPtr->name = tempName;
          newPtr->schoolName = tempSchoolName;
          newPtr->programName = tempProgramName;
          newPtr->graduatingYear = tempGraduatingYear;
          newPtr->gpa = tempGpa;
          newPtr->next = head;
          head = newPtr;
    } else {
    printf("%d and it's information not inserted. No memory available.\n", tmpId);
    }
    
    // Ensure to return pointer to new top of stack
    return head;
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
bool checkUniqueID(student_t *head, int id) {
    // Check if the head item is not NULL
    if(head != NULL) {
        // Create a tmp student that points to the head of the student stack used for iteration
        student_t *current = head;

        // Look through the student stack while the next item is not NULL
        while (current->next != NULL) {
            // Check if the iterated student ID is the same as the passed id
            if (current->id == id) {
                // Return false (passed id is not unique)
                return false;
            }

            // Move to the next item in the stack
            current = current->next;
        }
    }
    
    // Return true (passed id is unique)
    return true;
}

/**
 * 
 * This function is used to iterate through the students stack and print their information
 * 
 * @param head: is the first item in the student stack
 * 
 */
void *printAll(student_t *head) {
    // Check if the passed in head is NULL
    if(head == NULL) {
        // Display an empty student stack message
        printf("\nLooks like the Student Stack is empty.  Please add an item to the stack to view to the top item.\n\n");
    }else{
        // Create a tmp student that points to the head of the student stack used for iteration
        student_t *current = head;

        // Look through the student stack while the next item is not NULL
        while (current->next != NULL) {
            // Call the function that prints student information in the console for the iterated student in the stack
            printStudent(current);

            // Move to the next item in the stack
            current = current->next;
        }
    }
}

/**
 * 
 * This function is used to close the application section while preventing a memory leak
 * 
 * @param head: is the top item of the student stack (used to pop from the stack to account for memory leakage)
 * 
 */
void *exitStack(student_t *head) {
    // Create a tmp student that points to the head of the student stack used for iteration
    student_t *current = head;
    
    // Look through the student stack while the next item is not NULL
    while (current->next != NULL) {
        // Pop the current iteration student from the stack
        pop(current);
    }
    
    // Free the current and head student from memory
    free(current);
    free(head);
    
    // Print the exiting message
    printf("Exiting Stack Application Section");
    
    // Exit the application without error
    exit(0);
}

/**
 * 
 * This function is used to display the menu of the stack application
 * 
 */
void instructions() {
    // Display the different menu options
    printf("Student Stack Management\n------------------------------------------------\n1. Top (Print the Top item of the Student Stack)\n2. Push (Add an item to the Student Stack)\n3. Pop (Remove an item from the Student Stack\n4. Print (Prints the items of the Student Stack)\n5. Exit Stack Section\n------------------------------------------------\nPlease Enter Menu Option: ");
}

/**
 * 
 * This function is used to display the students information in the console
 * 
 * @param student: is the student that is to be displayed
 * 
 */
void *printStudent(student_t *student) {
    // Display the separator and student information
    printf("-----------------------------------------------------\n");
    printf("ID: %d\nName: %s\nGraduating Year: %d\nGPA: %.2lf\nProgram Name: %s\nSchool Name: %s\n", student->id, student->name, student->graduatingYear, student->gpa, student->programName, student->schoolName);
    printf("-----------------------------------------------------\n");
}