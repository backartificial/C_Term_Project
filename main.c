/**
 * File: Stack_ClassProject_Part_A/structure.c
 * Assignment: Final_Project
 * Creation date: July 3, 2018
 * Last Modified: July 6, 2018 
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
void *push(student_t*); // Function used to add an item to the stack
void *pop(student_t*); // Function used to remove an item from the stack
bool isUniqueId(student_t*, int); // Function used to check if the passed int (ID) refers to a unique ID
void *printTop(student_t*); // Function used to print only the top item of the stack
void *printAll(student_t*); // Function used to print the students in the stack
void *printStudent(student_t*); // Function used to display the actual student information to the console
void *exitStack(student_t*); // Function used to exit out of the application section
void instructions(); // Function to display the menu options

// Define Class Variables
char tmp[255] = {0};
bool exitingApplication = false;

/**
 * 
 * This method is used to run the core of the application section
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
        
        // Get the input from stdin and store it into the tmp variable
        fgets(tmp, (255 * sizeof(char)), stdin);

        // Check if the entered menu option is valid
        if((choice = (int)strtol(tmp, NULL, 10)) != 0 && (choice >= 1 && choice <= 5)) {
            // Calls the correct method from the method array
            student_t *result = (student_t *)(*methods[choice - 1])(head);

            // Check if the result of the called method is not NULL
            if(result || (choice == 3 && head->next != NULL)) {
                // Set the head value to the result from the function
                head = result;
            }
        }else{
            // Display an invalid menu option error message
            printf("\nOops... That is an invalid menu option.  Please try again.\n\n");
        }
        
        // Flush the buffer
        FLUSH;
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
    student_t* tmpStudent = (student_t*)malloc(sizeof(student_t));
    int tmpId = 0;
    int tmpGraduatingYear = 0;
    float tmpGpa = -1;
    
    // Check if memory cannot be allocate for the tmpStudent
    if(tmpStudent == NULL) {
        // Display an error message
        printf("Oops.. Memory cannot be allocated for adding a new student.  The application is closing as it cannot go any further.");
        
        // Exit the application in error
        exit(-1);
    }

    // Print prompt for entering student information
    printf("\nPlease Fill the Following Prompts to add a Student to the List\n");
    
    // Perform a loop to get the Students ID
    do {
        // Display a prompt message for the students id
        printf("Please Enter the Students ID (Number): ");
        
        // Get the input from stdin and store it into the tmp array
        fgets(tmp, (255 * sizeof(char)), stdin);
        
        // Remove the new line character from the string
        tmp[strcspn(tmp, "\n")] = 0;        
        
        // Check if the entered ID is valid
        if((tmpId = (int)strtol(tmp, NULL, 10)) == 0 || tmpId < 1 || !isUniqueId(head, tmpId)) {
            // Display an error message
            printf("\nOops... That is an invalid Student Id.  Please try again.\n\n");
            
            // Set the tmpId to 0 for error and loop continuation
            tmpId = 0;
        }else{
            // Assign the tmpStudent it's id
            tmpStudent->id = tmpId;
        }
        
        // Flush the buffer
        FLUSH;
    } while(tmpId == 0);    

    // Perform a loop to get the Students Name
    do {
        // Display prompt message getting the students name
        printf("Please Enter the Students Name: ");
        
        // Get the input of the students name
        fgets(tmp, (255 * sizeof(char)), stdin);
        
        // Remove the new line character from the string
        tmp[strcspn(tmp, "\n")] = 0;
        
        // Check if a name has been entered
        if(strlen(tmp) == 0) {
            // Display error message
            printf("\nOops... That's an invalid Student Name.  Please try again.\n\n");
        }else{
            // Allocate the space for the students name on the heap
            tmpStudent->name = (char*)malloc((strlen(tmp) + 1) * sizeof(char));
            
            // Assign the student to it's name
            tmpStudent->name = strncpy(tmpStudent->name, tmp, (strlen(tmp) + 1));
        }
        
        // Flush the Buffer
        FLUSH;
    } while(strlen(tmp) == 0);

    // Perform the loop and get the Students School Name
    do {
        // Display prompt message getting the students school name
        printf("Please Enter the Students School Name: ");
        
        // Get the input of the students school name
        fgets(tmp, (255 * sizeof(char)), stdin);
        
        // Remove the new line and return character from the string
        tmp[strcspn(tmp, "\n")] = 0;
        
        // Check if a school name has been entered
        if(strlen(tmp) == 0) {
            // Display error message
            printf("\nOops... That's an invalid School Name.  Please try again.\n\n");                        
        }else{
            // Allocate the space for the students school name on the heap
            tmpStudent->schoolName = (char*)malloc((strlen(tmp) + 1) * sizeof(char));
            
            // Assign the student to it's school name
            tmpStudent->schoolName = strncpy(tmpStudent->schoolName, tmp, (strlen(tmp) + 1));
        }
        
        // Flush the Buffer
        FLUSH;
    } while(strlen(tmp) == 0);
            
    // Perform the loop and get the Students Program Name
    do {
        // Display prompt message getting the students program name
        printf("Please Enter the Students Program Name: ");
        
        // Get the input of the students program name
        fgets(tmp, (255 * sizeof(char)), stdin);
        
        // Remove the new line and return character from the string
        tmp[strcspn(tmp, "\n")] = 0;
        
        // Check if a program name has been entered
        if(strlen(tmp) == 0) {
            // Display error message
            printf("\nOops... That's an invalid Program Name.  Please try again.\n\n");
        }else{
            // Allocate the space for the students program name on the heap
            tmpStudent->programName = (char*)malloc((strlen(tmp) + 1) * sizeof(char));
            
            // Assign the student to it's program name
            tmpStudent->programName = strncpy(tmpStudent->programName, tmp, (strlen(tmp) + 1));
        }
        
        // Flush the Buffer
        FLUSH;
    } while(strlen(tmp) == 0);
    
    // Perform a loop to get the Students graduating year
    do {
        // Display the prompt for the students graduating year
        printf("Please Enter the Students Graduating Year: ");
        
        // Get the input from stdin and store it into the tmp array
        fgets(tmp, (255 * sizeof(char)), stdin);
        
        // Remove the new line character from the string
        tmp[strcspn(tmp, "\n")] = 0;
        
        // Check if the entered year is valid
        if((tmpGraduatingYear = (int)strtol(tmp, NULL, 10)) == 0 || tmpGraduatingYear < 2018) {
            // Display an error message
            printf("\nOops... That's an invalid Graduating Year.  Please try again.\n\n");
            
            // Set the tmpGraduatingYear to 0 for error and loop continuation
            tmpGraduatingYear = 0;
        }else{
            // Assign the tmpStudent it's graduating year
            tmpStudent->graduatingYear = tmpGraduatingYear;
        }
        
        // Flush the buffer
        FLUSH;
    } while(tmpGraduatingYear == 0);

    // Perform a loop to get the Students GPA
    do {
        // Display the prompt for the students GPA
        printf("Please Enter the Students GPA: ");
        
        // Get the input from the user
        fgets(tmp, (255 * sizeof(char)), stdin);
        
        // Remove the new line character
        tmp[strcmp(tmp, "\n")] = '\0';
        
        // Check if the entered GPA is valid
        if((((tmpGpa = (float)strtof(tmp, NULL)) == 0) && tmp[0] != '0') || tmpGpa < 0) {
            // Display an error message
            printf("\nOops... That's an invalid GPA.  Please try again.\n\n");
            
            // Set the tmpGpa to 0 for error and loop continuation
            tmpGpa = -1;
        }else{
            // Assign the tmpStudent it's GPA
            tmpStudent->gpa = tmpGpa;
        }
    
        // Flush the buffer
        FLUSH;
    } while(tmpGpa == -1);
    
    // Check if head is not NULL
    if(head != NULL) {
        // Assign the next item in the stack to the current stack item
        tmpStudent->next = head;
    }else{
        // Assign the next item in the stack to the current stack item
        tmpStudent->next = NULL;
    }
    
    // Assign the head to the created student
    head = tmpStudent;
    
    // Print success message and new line for formatting
    printf("\nStudent Added Successfully!\n\n");
    
    // Return the new stack head (top) pointer
    return head;
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
        printf("\nOops... Unable to remove student from the list as there are no students in the list.\n\n");
        
        // Return NULL as nothing has changed on the stack
        return NULL;
    }else{
        // Check if the user is exiting the application and skip the confirmation of removal
        if(!exitingApplication) {
            // Print the confirmation message to remove the user
            printf("\nAre you sure that you want to remove the student? [y/Y - Yes | n/N - No]: ");

            // Store the entered character into the tmp variable
            int ch = getchar();

            // Check if the user really wants to remove the student
            if(ch != EOF && (ch != 'y' && ch != 'Y')) {
                // Formatting new line string
                printf("\n");

                // Flush the Buffer
                FLUSH;

                // Return null as the nothing has modified the stack
                return NULL;
            }
        }
        
        // Create a new student item that holds the head item
        student_t *popped = head;

        // Check if there is another item in the stack
        if(head->next != NULL) {
            // Move the head to the next stack item
            head = head->next;
        }else{
            // Set the head node to NULL
            head = NULL;
        }

        // Free the memory assignment of the popped students name
        free(popped->name);

        // Free the memory assignment of the popped students school name
        free(popped->schoolName);

        // Free the memory assignment of the popped students program name
        free(popped->programName);

        // Free the memory assignment of the popped student item
        free(popped);

        // Display Success pop message
        printf("\nFirst Student Successfully removed from the List.\n\n");

        // Flush the Buffer
        FLUSH;

        // Return the new head of the students stack
        return head;
    }
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
bool isUniqueId(student_t *head, int id) {
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
        
        // Check if the last student ID is the same as the passed id
        if (current->id == id) {
            // Return false (passed id is not unique)
            return false;
        }
    }
    
    // Return true (passed id is unique)
    return true;
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
        printf("\nLooks like the Student List is empty.  Please add an item to the list to view to the top student.\n\n");
    }else{
        // Print function starter
        printf("\n\n------------ Printing the First Student -------------\n");
        
        // Call the function that prints student information in the console for the first (top) student in the stack
        printStudent(head);
    }
    
    // Return NULL as nothing is being changed on the stack
    return NULL;
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
        printf("\nLooks like the Student List is empty.  Please add items to the list to view them.\n\n");
    }else{
        // Create a tmp student that points to the head of the student stack used for iteration
        student_t *current = head;
        
        // Print function starter
        printf("\n\n--------------- Printing Students List --------------\n");
        
        // Check if the next pointer is NULL or not
        if(current->next == NULL) {
            // Call the function that prints student information in the console for the iterated student in the stack
            printStudent(current);
        }else{
            // Look through the student stack while the next item is not NULL
            while (current->next != NULL) {
                // Call the function that prints student information in the console for the iterated student in the stack
                printStudent(current);

                // Move to the next item in the stack
                current = current->next;
            }
            
            // Check if the next pointer is NULL or not
            if(current->next == NULL) {
                // Call the function that prints student information in the console for the iterated student in the stack
                printStudent(current);
            }
        }
    }
    
    // Return NULL as nothing is being changed on the stack
    return NULL;
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
    printf("-----------------------------------------------------\n\n");
    
    // Return NULL as nothing is changing on the stack
    return NULL;
}

/**
 * 
 * This function is used to close the application section while preventing a memory leak
 * 
 * @param head: is the top item of the student stack (used to pop from the stack to account for memory leakage)
 * 
 */
void *exitStack(student_t *head) {
    // Check if the head (top) of the stack is empty
    if(head != NULL) {
        // Create a tmp student that points to the head of the student stack used for iteration
        student_t *current = head;
        
        // Set the flag to application is closing (true)
        exitingApplication = true;

        // Look through the student stack while the next item is not NULL
        while (current->next != NULL) {
            // Pop the current iteration student from the stack
            pop(current);
        }

        // Free the current student from memory
        free(current);
    }
    
    // Print the exiting message
    printf("\nClosing Application Section.\n\n");
    
    // Exit the application without error
    exit(0);
}

/**
 * 
 * This function is used to display the menu of the stack application
 * 
 */
void instructions() {
    // Display the menu options
    printf("Student List Management\n------------------------------------------------\n1. Print First Student\n2. Add Student\n3. Remove First Student\n4. Prints Student List\n5. Close Section\n------------------------------------------------\nPlease Enter Menu Option: ");
}