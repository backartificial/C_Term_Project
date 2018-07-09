/**
 * File: Stack_ClassProject_Part_A/structure.c
 * Assignment: Final_Project
 * Creation date: July 3, 2018
 * Last Modified: July 9, 2018 
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
    int id;
    char *name;
    char *schoolName;
    char *programName;
    int graduatingYear;
    float gpa;
    struct node *next;
} Student, *StudentPtr;

// Define the function prototypes
void *push(StudentPtr); // Function used to add an item to the stack
void *pop(StudentPtr); // Function used to remove an item from the stack
char isUniqueId(StudentPtr, int); // Function used to check if the passed int (ID) refers to a unique ID
void *printTop(StudentPtr); // Function used to print only the top item of the stack
void *printAll(StudentPtr); // Function used to print the students in the stack
void *printStudent(StudentPtr); // Function used to display the actual student information to the console
void *exitStack(StudentPtr); // Function used to exit out of the application section
void instructions(); // Function to display the menu options

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
    void *(*methods[])(StudentPtr) = {printTop, push, pop, printAll, exitStack}; // Store pointer to the function
    StudentPtr head = NULL; // Create a NULL student structure
    char choice; // Int to hold the menu choice of the user

    // Loop through and display the menu options
    while(1) {
        // Call the method used to display the menu options
        instructions();
        
        // Get the input from stdin and store it into the tmp variable
        fgets(tmp, MAX_INPUT_LENGTH, stdin);

        // Check if the entered menu option is valid
        if((choice = atoi(tmp)) != 0 && (choice >= 1 && choice <= 5)) {
            // Calls the correct method from the method array
            StudentPtr result;
            
            if(choice == 3) {
                // Print the confirmation message to remove the user
                printf("\nAre you sure that you want to remove the student? [ y/Y - Yes | n/N - No]: ");

                // Store the entered character into the previousEntry variable
                int ch = getchar();

                // Check to make sure that the entered confirmation character is wither y/Y
                if(ch != EOF && (ch == 'y' || ch == 'Y')) {
                    // Pop the student and set it to the result variable
                    result = pop(head);
                }else{
                    // Print a new line for formatting
                    printf("\n");
                }
            }else{
                // Set the tmp result variable to the returned value of the called function
                result = (StudentPtr)(*methods[choice - 1])(head);
            }            

            // Check if the result of the called method is not NULL
            if(result) {
                // Set the head value to the result from the function
                head = result;
            }
        }else{
            // Display an invalid menu option error message
            printf("\nOops... That's an invalid menu option.  Please try again.\n\n");
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
void *push(StudentPtr head) {
    // Create the needed function variables
    StudentPtr tmpStudent = (StudentPtr)malloc(sizeof(Student));
    int tmpInt = 0, tmpStringLength = 0;
    float tmpFloat = -1;
    
    // Check if memory cannot be allocate for the tmpStudent
    if(tmpStudent == NULL) {
        // Display an error message
        printf("Oops... Memory cannot be allocated for adding a new student.  The application is closing as it cannot go any further.");
        
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
        fgets(tmp, MAX_INPUT_LENGTH, stdin);
        
        // Remove the new line character from the string
        tmp[strcspn(tmp, "\n")] = 0;        
        
        // Check if the entered ID is valid
        if((tmpInt = atoi(tmp)) == 0 || tmpInt < 1 || !isUniqueId(head, tmpInt)) {
            // Display an error message
            printf("\nOops... That's an invalid Student Id.  Please try again.\n\n");
            
            // Set the tmpId to 0 for error and loop continuation
            tmpInt = 0;
        }else{
            // Assign the tmpStudent it's id
            tmpStudent->id = tmpInt;
        }
        
        // Flush the buffer
        FLUSH;
    } while(tmpInt == 0);    

    // Perform a loop to get the Students Name
    do {
        // Display prompt message getting the students name
        printf("Please Enter the Students Name: ");
        
        // Get the input of the students name
        fgets(tmp, MAX_INPUT_LENGTH, stdin);
        
        // Remove the new line character from the string
        tmp[strcspn(tmp, "\n")] = 0;
        
        // Hold the length of the string + 1 (NULL Terminating) to tmpStringLength
        tmpStringLength = strlen(tmp) + 1;
        
        // Check if a name has been entered
        if(tmpStringLength == 1) {
            // Display error message
            printf("\nOops... That's an invalid Student Name.  Please try again.\n\n");
        }else{
            // Allocate the space for the students name on the heap
            tmpStudent->name = (char*)malloc(tmpStringLength * sizeof(char));
            
            // Assign the student to it's name
            tmpStudent->name = strncpy(tmpStudent->name, tmp, tmpStringLength);
        }
        
        // Flush the Buffer
        FLUSH;
    } while(tmpStringLength == 1);

    // Perform the loop and get the Students School Name
    do {
        // Display prompt message getting the students school name
        printf("Please Enter the Students School Name: ");
        
        // Get the input of the students school name
        fgets(tmp, MAX_INPUT_LENGTH, stdin);
        
        // Remove the new line and return character from the string
        tmp[strcspn(tmp, "\n")] = 0;
        
        // Hold the length of the string + 1 (NULL terminating) to tmpStringLength
        tmpStringLength = strlen(tmp) + 1;
        
        // Check if a school name has been entered
        if(tmpStringLength == 1) {
            // Display error message
            printf("\nOops... That's an invalid School Name.  Please try again.\n\n");                        
        }else{
            // Allocate the space for the students school name on the heap
            tmpStudent->schoolName = (char*)malloc(tmpStringLength * sizeof(char));
            
            // Assign the student to it's school name
            tmpStudent->schoolName = strncpy(tmpStudent->schoolName, tmp, tmpStringLength);
        }
        
        // Flush the Buffer
        FLUSH;
    } while(tmpStringLength == 1);
            
    // Perform the loop and get the Students Program Name
    do {
        // Display prompt message getting the students program name
        printf("Please Enter the Students Program Name: ");
        
        // Get the input of the students program name
        fgets(tmp, MAX_INPUT_LENGTH, stdin);
        
        // Remove the new line and return character from the string
        tmp[strcspn(tmp, "\n")] = 0;
        
        // Hold the length of the string + 1 (NULL terminating) to tmpStringLength
        tmpStringLength = strlen(tmp) + 1;
        
        // Check if a program name has been entered
        if(tmpStringLength == 1) {
            // Display error message
            printf("\nOops... That's an invalid Program Name.  Please try again.\n\n");
        }else{
            // Allocate the space for the students program name on the heap
            tmpStudent->programName = (char*)malloc(tmpStringLength * sizeof(char));
            
            // Assign the student to it's program name
            tmpStudent->programName = strncpy(tmpStudent->programName, tmp, tmpStringLength);
        }
        
        // Flush the Buffer
        FLUSH;
    } while(tmpStringLength == 1);
    
    // Perform a loop to get the Students graduating year
    do {
        // Display the prompt for the students graduating year
        printf("Please Enter the Students Graduating Year: ");
        
        // Get the input from stdin and store it into the tmp array
        fgets(tmp, MAX_INPUT_LENGTH, stdin);
        
        // Remove the new line character from the string
        tmp[strcspn(tmp, "\n")] = 0;
        
        // Check if the entered year is valid
        if((tmpInt = atoi(tmp)) == 0 || tmpInt < 2018) {
            // Display an error message
            printf("\nOops... That's an invalid Graduating Year.  Please try again.\n\n");
            
            // Set the tmpGraduatingYear to 0 for error and loop continuation
            tmpInt = 0;
        }else{
            // Assign the tmpStudent it's graduating year
            tmpStudent->graduatingYear = tmpInt;
        }
        
        // Flush the buffer
        FLUSH;
    } while(tmpInt == 0);

    // Perform a loop to get the Students GPA
    do {
        // Display the prompt for the students GPA
        printf("Please Enter the Students GPA: ");
        
        // Get the input from the user
        fgets(tmp, MAX_INPUT_LENGTH, stdin);
        
        // Remove the new line character
        tmp[strcmp(tmp, "\n")] = '\0';
        
        // Check if the entered GPA is valid
        if((((tmpFloat = atof(tmp)) == 0) && tmp[0] != '0') || tmpFloat < 0) {
            // Display an error message
            printf("\nOops... That's an invalid GPA.  Please try again.\n\n");
            
            // Set the tmpGpa to 0 for error and loop continuation
            tmpFloat = -1;
        }else{
            // Assign the tmpStudent it's GPA
            tmpStudent->gpa = tmpFloat;
        }
    
        // Flush the buffer
        FLUSH;
    } while(tmpFloat == -1);
    
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
void *pop(StudentPtr head) {
    // Check if the head is NULL
    if (head == NULL) {
        // Display error message 
        printf("\nOops... Unable to remove student from the list as there are no students in the list.\n\n");
        
        // Return NULL as nothing has changed on the stack
        return NULL;
    }else{        
        // Create a new student item that holds the head item
        StudentPtr poppedStudent = head;

        // Move the head to the next stack item
        head = head->next;
        
        // Free the memory assignment of the popped students name
        free(poppedStudent->name);

        // Free the memory assignment of the popped students school name
        free(poppedStudent->schoolName);

        // Free the memory assignment of the popped students program name
        free(poppedStudent->programName);

        // Free the memory assignment of the popped student item
        free(poppedStudent);

        // Display Success pop message
        printf("\nStudent Successfully removed from the List.\n\n");

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
char isUniqueId(StudentPtr head, int id) {
    // Create a current student that points to the head of the student stack used for iteration
    StudentPtr current = head;
    
    // Loop through the student stack while the current item is not NULL
    while(current != NULL) {
        // Check if the iterated student ID is the same as the passed id
        if (current->id == id) {
            // Return false (passed id is not unique)
            return 0;
        }

        // Move to the next item in the stack
        current = current->next;
    }
    
    // Return true (passed id is unique)
    return 1;
}

/**
 * 
 * This function is used to print the top student in the stack
 * 
 * @param head: is the top item in the student stack
 *
 */
void *printTop(StudentPtr head) {
    // Check if the head item of the stack is empty
    if (head == NULL) {
        // Display an empty student stack message
        printf("\nLooks like the Student List is empty.  Please add an item to the list to view to the first student.\n\n");
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
void *printAll(StudentPtr head) {
    // Check if the passed in head is NULL
    if(head == NULL) {
        // Display an empty student stack message
        printf("\nLooks like the Student List is empty.  Please add items to the list to view them.\n\n");
    }else{
        // Create a tmp student that points to the head of the student stack used for iteration
        StudentPtr current = head;
        
        // Print function starter
        printf("\n\n--------------- Printing Students List --------------\n");
        
        // Look through the student stack while the current item is not NULL
        while(current != NULL) {
            // Call the function that prints student information in the console for the iterated student in the stack
            printStudent(current);

            // Move to the next item in the stack
            current = current->next;
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
void *printStudent(StudentPtr student) {
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
void *exitStack(StudentPtr head) {
    // Check if the head (top) of the stack is empty
    if(head != NULL) {
        // Create a tmp student that points to the head of the student stack used for iteration
        StudentPtr current = head;

        // Look through the student stack while the current item is not NULL
        while(current != NULL){
            // Pop the current iterated student from the stack
           head = current = pop(current);
        }

        // Free the head and current student from memory
        free(head);
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
    printf("Student List Management\n------------------------------------------------\n1. Print First Student\n2. Add Student\n3. Remove First Student\n4. Print Student List\n5. Close Section\n------------------------------------------------\nPlease Enter Menu Option: ");
}