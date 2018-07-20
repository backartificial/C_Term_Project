/**
 * File: Data_Structures_C_ClassProject/Part_B/queue.c
 * Assignment: Final_Project
 * Creation date: July 16, 2018
 * Last Modified: July 20, 2018
 *
 * GitHub Link: https://github.com/groverb/Data_Structures_C_ClassProject
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
 * @item leftPtr: is the pointer to the left child in the tree
 * @item rightPtr: is the pointer to the right child in the tree
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
    struct node *leftPtr;
    struct node *rightPtr;
} student_t, Student, *StudentPtr;

// Define the function prototypes
void insertStudent(StudentPtr*);
void inOrder(StudentPtr);
void getInputs(StudentPtr* );
void preOrder(StudentPtr);
void postOrder(StudentPtr);
void printStudent(StudentPtr);
void deleteStudent(StudentPtr*, int);
void searchNode(StudentPtr*, int, StudentPtr*, StudentPtr*, int*);

// Define Class Variables
static const size_t MAX_INPUT_LENGTH = (255 * sizeof(char));
char tmp[255] = {0};

// Stores the values to be validated in a global union
static union {
    // Declare the needed member for the union
    // Declare the needed member for the union
    size_t stringSize; // Stores the length of the string
    int enteredInt; // Stores the value of the entered integer number
    float enteredFloat; // Stores the value of the entered float number
} tmpValidation;

/**
 *
 * This method is used to run the core of the application section
 *
 */
int main(){
    // Create the needed variables
    StudentPtr root = NULL; // Create the tree root student    
    char choice; // Integer (int) to hold the menu choice of the user

    // Loop through and display the menu options
    while(choice != 6) {
        // Call the method used to display the menu options
        instructions();

        // Get the input from stdin and store it into the tmp variable
        fgets(tmp, MAX_INPUT_LENGTH, stdin);
        
        // Convert the entered menu option to an int
        choice = atoi(tmp);

        // Check if the entered menu option is valid
        if(choice != 0 && (choice >= 1 && choice <= 6)) {
            // Select the correct case based on the entered choice
            switch (choice) {
                // Case to add a student
                case (1):
                    // Call the method to add a student
                    insertStudent(root);
                break;

                // Case to remove a student
                case (2):
                    // Ask the user to enter an Id
                    // Search to make sure that the id is valid
                    // Confirm that the user wants to remove the student
                    // Pass the pointer to the deleteNode method and remove student
                    // Call the method to remove a student from the list
                    // Print the confirmation message to remove the user
                    printf("\nAre you sure that you want to remove the student? [ y/Y - Yes | n/N - No]: ");

                    // Store the entered character into the ch variable
                    int ch = getchar();

                    // Check to make sure that the entered confirmation character is either y/Y
                    if(ch != EOF && (ch == 'y' || ch == 'Y')) {
                        // Remove the student from the queue
                        deleteStudent();
                    }else{
                        // Print a new line for formatting
                        printf("\n");
                    }
                break;

                // Case to sort and print the students in pre-order
                case (3):
                    // Pass the root to preOrder to be sorted using that method
                    preOrder(root);
                break;

                // Case to sort and print the students in post-order
                case (4):
                    // Pass the root to postOrder to be sorted using that method
                    postOrder(root);
                break;

                // Case to sort and print the students in in-order
                case (5):
                    // Pass the root to inOrder to be sorted using that method
                    inOrder(root);
                break;
            }
        }else{
            // Display an invalid menu option error message
            printf("\nOops...  That's an invalid menu option.  Please try again.\n\n");
        }

        // Flush the buffer
        FLUSH;
    }

    // Call the method to clear out the tree and then exits the application section
}

/**
 *
 * This function is used to display the menu of the tree application
 *
 */
void instructions() {
    // Display the menu options
    printf("Student List Management"
           "\n------------------------------------------------"
           "\n1. Add Student"
           "\n2. Remove Student"
           "\n3. Pre-Order Sort Student List"
           "\n4. Post-Order Sort Student List"
           "\n5. In-Order Print Students List"
           "\n6. Close Section"
           "\n------------------------------------------------"
           "\nPlease Enter Menu Option: ");
}

/**
 * 
 * This function is used to insert a student into the tree
 * 
 * @param root: is the pointer to the root of the tree
 * 
 */
void insertStudent(StudentPtr *root) {
    // Create the needed variables
    StudentPtr tmpStudent = NULL; // Create a NULL student	

    // Check to see if the tmpValidation.enteredInt in 0 for allowing the entrance of a new student
    if(tmpValidation.enteredInt == 0){
        // Loop though and get the students id
        do {
            // Display a prompt message for the students id
            printf("\n\tPlease Enter the Students ID (Number): ");

            // Get the input from stdin and store it into the previousEntry array
            fgets(tmp, MAX_INPUT_LENGTH, stdin);

            // Store the entered id into the validation.int union
            tmpValidation.enteredInt = atoi(tmp);

            // Check if the entered ID is valid
            if(tmpValidation.enteredInt == 0 && *tmp != '0' || tmpValidation.enteredInt < 0 ) {
                // Display an error message
                printf("\n\tOops... That is an invalid Student Id.  Please try again.\n\n");

                // Set the tmpId to 0 for error and loop continuation
                tmpValidation.enteredInt = 0;
            }

            // Flush the buffer
            FLUSH;
        } while(tmpValidation.enteredInt == 0);
    }

    // Check if root is NULL and perform action for empty tree
    if (*root == NULL) {
        // Allocate Space on the heap for the student
        *root = (StudentPtr)malloc(sizeof(Student));
        
        // Check if the root could not be initialized on the heap
        if (*root == NULL) {
            // Display an error message
            printf("Oops...  Memory cannot be allocated for adding a new student.  The application is closing as it cannot go any further.");

            // Exit the application in error
            //exitApplication();
        }
        
        // Set the root attributes
        (*root)->id = tmpValidation.enteredInt; // Set the student id to the entered id
        getInputs(root); // Pass the root pointer to the method that prompts the user to enter the other needed attributes
        (*root)->leftPtr = NULL; // Set the left child pointer to NULL
        (*root)->rightPtr = NULL; // Set th right child pointer to NULL
   }else{
        // Check if the entered int (id) is less than the root's id
        if(tmpValidation.enteredInt < (*root)->id) {
            // Check if the left pointer of root is not NULL
            if((*root)->leftPtr != NULL){
                // Recursively call the method again
                insertStudent(&((*root)->leftPtr));
            }else{
                // Set the tmpStudent to a place on the heap
                tmpStudent = (StudentPtr)malloc(sizeof(Student));
                
                // Set the tmpStudent attributes
                tmpStudent->id = tmpValidation.enteredInt; // Set the student id to the entered id
                getInputs(&tmpStudent); // Pass the tmpStudent pointer to the method that prompts the user to enter the other needed attributes
                
                // Set the student node left child to the tmpStudent
                (*root)->leftPtr = tmpStudent;
            }         
        }else if(tmpValidation.enteredInt > (*root)->id) {
            // Check if the right pointer of root is not NULL
            if((*root)->rightPtr != NULL){
                // Recursively call the method again
                insertStudent(&((*root)->rightPtr));
            }else{
                // Set the tmpStudent to a place on the heap
                tmpStudent = (StudentPtr)malloc(sizeof(Student));
                
                // Set the tmpStudent attributes
                tmpStudent->id = tmpValidation.enteredInt; // Set the student id to the entered id
                getInputs(&tmpStudent); // Pass the tmpStudent pointer to the method that prompts the user to enter the other needed attributes
                
                // Set the student node left child to the tmpStudent
                (*root)->rightPtr = tmpStudent;
            }          
        }else{
            printf("-duplicate-not-inserted\n");  
        }
        
        // Set the child pointers to NULL
        (*tmpStudent)->leftPtr = NULL; // Set the left child pointer to NULL
        (*tmpStudent)->rightPtr = NULL; // Set th right child pointer to NULL
    }
    
    // Set the tmpValidation.enteredInt to 0 to act as a clear
    tmpValidation.enteredInt = 0;
} 

/**
 * 
 * This function is used to print the students using in order sort
 * 
* @param node: is a node of the tree (in iteration)
 * 
 */
void inOrder(StudentPtr node) {
    // Check to make sure that the list/tree is not NULL
    if(node == NULL) {
        // Display an empty student tree message
        printf("\nLooks like the Student List is empty.  Please add items to the list to view them.\n\n");
    }else{
        // Check to make sure that there is a child to the left
        if(node->leftPtr != NULL) {
            // Traverse to the left child
            inOrder(node->leftPtr);
        }

        // Print the student's information to the screen
        printStudent(node);

        // Check to make sure that there is a child to the right
        if(node->rightPtr != NULL) {
            // Traverse to the right child
            inOrder(node->rightPtr);
        } 
    }
}

/**
 * 
 * This function is used to print the students using pre order sort
 * 
* @param node: is a node of the tree (in iteration)
 * 
 */
void preOrder(StudentPtr node) {    
    // Check to make sure that the list/tree is not NULL
    if(node == NULL) {
        // Display an empty student tree message
        printf("\nLooks like the Student List is empty.  Please add items to the list to view them.\n\n");
    }else{
        // Print the student's information to the screen
        printStudent(node);
        
        // Check to make sure that there is a child to the left
        if(node->leftPtr != NULL) {
            // Traverse to the left child
            preOrder(node->leftPtr);
        }

        // Check to make sure that there is a child to the right
        if(node->rightPtr != NULL) {
            // Traverse to the right child
            preOrder(node->rightPtr);
        } 
    }
} 

/**
 * 
 * This function is used to print the students using post order sort
 * 
 * @param node: is a node of the tree (in iteration)
 * 
 */
void postOrder(StudentPtr root) {
    // Check to make sure that the list/tree is not NULL
    if(node == NULL) {
        // Display an empty student tree message
        printf("\nLooks like the Student List is empty.  Please add items to the list to view them.\n\n");
    }else{        
        // Check to make sure that there is a child to the left
        if(node->leftPtr != NULL) {
            // Traverse to the left child
            preOrder(node->leftPtr);
        }

        // Check to make sure that there is a child to the right
        if(node->rightPtr != NULL) {
            // Traverse to the right child
            preOrder(node->rightPtr);
        }
        
        // Print the student's information to the screen
        printStudent(node);
    }
}

/**
 * 
 * This function is used to prompt the user for the other student attributes (not including id, leftPtr, or rightPtr)
 * 
 * @param node: is the student node adding values to
 * 
 */
void getInputs(StudentPtr* node){
    // Perform the loop and get the Students Name
    do {
        // Display prompt message getting the students name
        printf("\tPlease Enter the Students Name: ");

        // Get the input of the students name
        fgets(tmp, MAX_INPUT_LENGTH, stdin);

        // Remove the new line character from the string
        tmp[strcspn(tmp, "\n")] = 0;

        // Store he length of the string ( + 1 - NULL terminator) to the validation.size
        tmpValidation.stringSize = strlen(tmp) + 1;

        // Check if a name has been entered
        if(tmpValidation.stringSize == 1) {
            // Display error message
            printf("\n\tOops...  That's an invalid Student Name.  Please try again.\n\n");
        }else{
            // Allocate the space for the students name on the heap
            (*node)->name = (char *)malloc(tmpValidation.stringSize * sizeof(char));

            // Check if memory cannot be allocate for the (*rootPtr)'s name
            if((*node)->name == NULL) {
                // Display an error message
                printf("Oops...  Memory cannot be allocated for adding a new student.  The application is closing as it cannot go any further.");

                // Free the current tmp student
                free((*node));

                // Exit the application in error
                // exitQueue(head, tail);
            }

            // Assign the student to it's name
            memcpy((*node)->name, tmp, tmpValidation.stringSize);
        }

        // Flush the Buffer
        FLUSH;
    } while(tmpValidation.stringSize == 1);

    // Perform the loop and get the Students School Name
    do {
        // Display prompt message getting the students school name
        printf("\tPlease Enter the Students School Name: ");

        // Get the input of the students school name
        fgets(tmp, MAX_INPUT_LENGTH, stdin);

        // Remove the new line and return character from the string
        tmp[strcspn(tmp, "\n")] = 0;

        // Store the string length ( + 1 - NULL terminator) to the validation.size
        tmpValidation.stringSize = strlen(tmp) + 1;

        // Check if a school name has been entered
        if(tmpValidation.stringSize == 1) {
            // Display error message
            printf("\n\tOops...  That's an invalid School Name.  Please try again.\n\n");
        }else{
            // Allocate the space for the students school name on the heap
            (*node)->schoolName = (char *)malloc(tmpValidation.stringSize * sizeof(char));

            // Check if memory cannot be allocate for the (*rootPtr)'s school name
            if((*node)->schoolName == NULL) {
                // Display an error message
                printf("Oops...  Memory cannot be allocated for adding a new student.  The application is closing as it cannot go any further.");

                // Free the current tmp student
                free((*node)->name);
                free((*node));

                // Exit the application in error
                // exitQueue(head, tail);
            }

            // Assign the student to it's school name
            memcpy((*node)->schoolName, tmp, tmpValidation.stringSize);
        }

        // Flush the Buffer
        FLUSH;
    } while(tmpValidation.stringSize == 1);

    // Perform the loop and get the Students Program Name
    do {
        // Display prompt message getting the students program name
        printf("\tPlease Enter the Students Program Name: ");

        // Get the input of the students program name
        fgets(tmp, MAX_INPUT_LENGTH, stdin);

        // Remove the new line and return character from the string
        tmp[strcspn(tmp, "\n")] = 0;

        // Store the length of the string ( + 1 - NULL terminator) into the validation.size
        tmpValidation.stringSize = strlen(tmp) + 1;

        // Check if a program name has been entered
        if(tmpValidation.stringSize == 1) {
            // Display error message
            printf("\n\tOops...  That's an invalid Program Name.  Please try again.\n\n");
        }else{
            // Allocate the space for the students program name on the heap
            (*node)->programName = (char *)malloc(tmpValidation.stringSize * sizeof(char));

            // Check if memory cannot be allocate for the (*rootPtr)'s program name
            if((*node)->programName == NULL) {
                // Display an error message
                printf("Oops...  Memory cannot be allocated for adding a new student.  The application is closing as it cannot go any further.");

                // Free the current tmp student
                free((*node)->name);
                free((*node)->schoolName);
                free((*node));

                // Exit the application in error
                // exitQueue(head, tail);
            }

            // Assign the student to it's program name
            memcpy((*node)->programName, tmp, tmpValidation.stringSize);
        }

        // Flush the Buffer
        FLUSH;
    } while(tmpValidation.stringSize == 1);

    // Perform a loop to get the Students graduating year
    do {
        // Display the prompt for the students graduating year
        printf("\tPlease Enter the Students Graduating Year: ");

        // Get the input from stdin and store it into the previousEntry array
        fgets(tmp, MAX_INPUT_LENGTH, stdin);

        // Store the entered year into the validation.int
        tmpValidation.enteredInt = atoi(tmp);

        // Check if the entered year is valid
        if(tmpValidation.enteredInt == 0 || tmpValidation.enteredInt < 2018) {
            // Display an error message
            printf("\n\tOops...  That's an invalid Graduating Year.  Please try again.\n\n");

            // Set the tmpGraduatingYear to 0 for error and loop continuation
            tmpValidation.enteredInt = 0;
        }else{
            // Assign the (*rootPtr) it's graduating year
            (*node)->graduatingYear = tmpValidation.enteredInt;
        }

        // Flush the buffer
        FLUSH;
    } while(tmpValidation.enteredInt == 0);

    // Perform a loop to get the Students GPA
    do {
        // Display the prompt for the students GPA
        printf("\tPlease Enter the Students GPA: ");

        // Get the input from the user
        fgets(tmp, MAX_INPUT_LENGTH, stdin);

        // Store the entered gpa into the validation.float
        tmpValidation.enteredFloat = atof(tmp);

        // Check if the entered GPA is valid
        if(tmpValidation.enteredFloat == 0 && *tmp != '0' || tmpValidation.enteredFloat < 0) {
            // Display an error message
            printf("\n\tOops...  That's an invalid GPA.  Please try again.\n\n");

            // Set the tmpGpa to -1 for error and loop continuation
            tmpValidation.enteredFloat = -1;
        }else{
            // Assign the (*rootPtr) it's GPA
            (*node)->gpa = tmpValidation.enteredFloat;
        }

        // Flush the buffer
        FLUSH;
    }while(tmpValidation.enteredFloat == -1);
}

/**
 *
 * This function is used to print the students information to the console
 *
 * @param student: is the student to be printed
 *
 */
void printStudent(StudentPtr student) {
    // Display the separator and student information
    printf("-----------------------------------------------------\n");
    printf("ID: %d\nName: %s\nGraduating Year: %d\nGPA: %.2lf\nProgram Name: %s\nSchool Name: %s\n", student->id, student->name, student->graduatingYear, student->gpa, student->programName, student->schoolName);
    printf("-----------------------------------------------------\n\n");
}

/**
 * 
 * This function is used to delete a student from the tree
 * 
 * @param student: is the student being removed
 *
 */
void deleteStudent(StudentPtr *student) {
    // Create the needed variables
    StudentPtr parentStudent = NULL, tmpStudent = NULL, replacementStudent;
    
    // Check to see if the passed student is nULL
    if(*student == NULL) {
        // Display an empty student tree message
        printf("\nLooks like the Student List is empty.  Please add items to the list to view them.\n\n");
        
        // Return to not continue any further processing
        return;
    }
    
    // Check if the student node being deleted has 2 children (left & right)
    if (tmpStudent->leftPtr != NULL && tmpStudent->rightPtr != NULL) {
        // Set the parentStudent to the tmpStudent
        parentStudent = tmpStudent;
        
        // Set the replacementStudent to the tmpStudent rightPtr
        replacementStudent = tmpStudent->rightPtr ;

        // Loop through while the replacementStudent leftPtr is not NULL
        while(replacementStudent->leftPtr != NULL) {
            // Set the parentStudent to the replacementStudent
            parentStudent = replacementStudent;
            
            // Set the replacementStudent to the replacementStudent's leftPtr
            replacementStudent = replacementStudent->leftPtr;
        }
        
        // Set the tmpStudent to the replacementStudent
        tmpStudent = replacementStudent;
    }

    // Check is the student node being deleted has no children
    if(tmpStudent->leftPtr == NULL && tmpStudent->rightPtr == NULL) {
        // Check if the parentStudens rightPtr is equal to tmpStudent
        if(parentStudent->rightPtr == tmpStudent) {
            // Set parentStudents rightPtr to NULL
            parentStudent->rightPtr = NULL;
        }else{
            // Set parentStudent leftPtr to NULL
            parentStudent->leftPtr = NULL;
        }

        // Free the tmpStudent
        free(tmpStudent->name);
        free(tmpStudent->schoolName);
        free(tmpStudent->programName);
        free(tmpStudent);
        
        // Return out of the method
        return;
    }

    // Check if the student node has only a rightPtr
   if(tmpStudent->leftPtr == NULL && tmpStudent->rightPtr != NULL) {
        // Check if the parentStudents leftPtr is equal to the tmpStudent
        if(parentStudent->leftPtr == tmpStudent) {
            // Set the parentStudents leftPtr to the tmpStudents rightPtr
            parentStudent->leftPtr = tmpStudent->rightPtr;
        }else{
            // Set the parentStuends rightPtr to the tmpStudents rightPtr
            parentStudent->rightPtr = tmpStudent->rightPtr;
        }

        // Free the tmpStudent
        free(tmpStudent->name);
        free(tmpStudent->schoolName);
        free(tmpStudent->programName);
        free(tmpStudent);
        
        // Return out of the method
        return;
    }

    // Check if the student node has only a rightPtr
    if(tmpStudent->leftPtr != NULL && tmpStudent->rightPtr == NULL ) {
        // Check if the parentStudents leftPtr is equal to the tmpStudents leftPtr
        if(parentStudent->leftPtr == tmpStudent) {
            // Set the parentStudents leftPtr to the tmpStudents leftPtr
            parentStudent->leftPtr = tmpStudent->leftPtr;
        }else{
            // Set the parentStudents rightPtr to the tmpStudents leftPtr
            parentStudent->rightPtr = tmpStudent->leftPtr;
        }

        // Free the tmpStudent
        free(tmpStudent->name);
        free(tmpStudent->schoolName);
        free(tmpStudent->programName);
        free(tmpStudent);
        
        // Return out of the method
        return;
    }
}

/**
 * 
 * This method is used for searching for a student
 * 
 * @param student: is the student being searched for
 * @param id: is the id being matched against
 * @param parent: is the parent node
 * @param tmp: is the tmp node
 * @param found: is the boolean value of true (1) false (0)
 */
void searchNode(StudentPtr *student, unsigned int id, StudentPtr *parent, StudentPtr *tmp, int *found) {
    // Set the needed variables
    StudentPtr tmpPtr = *student ;
    *found = 0;
    *parent = NULL;

    // Loop through the tmpPrt while it is not NULL
    while(tmpPtr != NULL) {
        // Check if the tmpPtr id is the same as the passed in id
        if(tmpPtr->id == id) {
            // Set found to true
            *found = 1;
            
            // Set the tmp to the tmpPtr
            *tmp = tmpPtr;
            
            // Return out of the function
            return;
        }

        // Set the parent to tmpPtr
        *parent = tmpPtr;
       
        // Check if the tmpPtr id is greater than the passed in id
        if (tmpPtr->id > id) {
            // Set the tmpPtr to the left child of tmpPtr
            tmpPtr = tmpPtr->leftPtr;
        }else{
            // Set the tmpPtr to the right child of tmpPtr
            tmpPtr = tmpPtr -> rightPtr;
        }
    }
}