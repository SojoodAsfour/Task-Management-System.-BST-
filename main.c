// Name: Sojood Nazih Asfour, Id: 1230298, Section: 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxSize 100

// Definition of the Node structure used in the Binary Search Tree (BST)
struct Node
{
    int ID;// Task ID
    char* Name;// Task Name
    char* Date;// Task Date in string format
    float Duration;// Task Duration
    int perform;// Flag indicating if the task was performed (1 = performed, 0 = not performed)
    struct Node* Left;// Pointer to the left child in the BST
    struct Node* Right;// Pointer to the right child in the BST
};

// Define a new type 'Task' as a pointer to struct Node
typedef struct Node* Task;

int op = 4, counter;

// Function declarations
void displayMenu();
Task MakeEmpty(Task);
Task Insert(int, char*, char*, float, int, Task);
Task LoadTask();
void AddTask(Task);
Task Find(int, Task);
Task FindMin(Task);
Task Delete(Task);
Task DeleteById(int, Task, int*);
Task DeleteByName(char*, Task, int*);
Task DeleteByDate(char*, Task, int*);
Task DeleteByDuration(float, Task, int*);
void SearchTaskByName(Task, char*);
void PerformATask(Task);
void viewUnperformedTasks(Task, int*);
void viewPerformedTasks(Task, int*);
Task RestructTasksBST(Task);
Task InsertTaskByName(Task, Task);
Task RestructTasksByName(Task);
int dateToInt(char*, int, int);
int CompareDate(char *, char *);
Task InsertTaskByDate(Task, Task);
Task RestructTasksByDate(Task);
Task InsertTaskByDuration(Task, Task);
Task RestructTasksByDuration(Task);
Task RestructTasksByID(Task);
int getTreeHeight(Task);
int getTreeSize(Task);
int getNumOfLeaves(Task);
int getNumOfInternalNode(Task);
void viewTasksBSTInfo(Task);
void PrintTree(Task);

int main()
{
    int found1 = 0,found2 = 0;// Variables for task ID and found flag
    char name[MaxSize];
    Task T;

    printf("Welcome to the Task Management System....\n\n");

    int choice = 0;
    printf("Please enter an option from the menu:\n");
    displayMenu();// Show menu to the user
    scanf("%d", &choice);

    // Ensure tasks are loaded before performing operations
    if (choice != 1)
    {
        while (choice != 1 && choice != 10)
        {
            printf("\nYou can't do any operation before load the information from the file!!\n\n");
            printf("Please enter an option from the menu:\n\n");
            displayMenu();
            scanf("%d", &choice);

            if (choice == 10)  // If the user enters 10 at this point, exit immediately
            {
                printf("\nExit from the program...\nThank you for using this program...\nGood bye!\n");
                return 0;
            }
        }
    }

    // Main menu loop
    while (choice != 10)
    {
        switch (choice)
        {
        // Load tasks from file
        case 1:
            T = LoadTask();
            break;
        // Add a new task to the BST
        case 2:
            AddTask(T);
            break;
        // Delete tasks based on various criteria
        case 3:
            T = Delete(T);
            break;
        // Search task by name
        case 4:
            printf("\nPlease enter Task name: ");
            getchar();// To consume any newline character left in the input buffer
            scanf("%[^\n]", name);// Read the task name (including spaces)
            SearchTaskByName(T, name);
            break;
        // Mark a task as performed
        case 5:
            PerformATask(T);
            break;
        // View unperformed tasks
        case 6:
            counter = 1;
            viewUnperformedTasks(T, &found1);
            printf("\n");
            if (!found1)
                printf("There are no unperformed Tasks to display!\n\n");
            break;
        // View performed tasks
        case 7:
            counter = 1;
            viewPerformedTasks(T, &found2);
            printf("\n");
            if (!found2)
                printf("There are no performed Tasks to display!\n\n");
            break;
        // Restructure the task BST based on user choice(id,date,duration,name)
        case 8:
            T = RestructTasksBST(T);
            break;
        // Display information about the BST(hight,size,number of internal nodes, number of leaves)
        case 9:
            viewTasksBSTInfo(T);
            break;
        default:
            printf("\nInvalid choice! PLease try again!\n\n");
            break;
        }

        // Re-display the menu after operation
        printf("Please enter an option from the menu:\n");
        displayMenu();
        scanf("%d", &choice);
    }

    // Exit message
    printf("\nExit from the program...\nThank you for using this program...\nGood bye!\n");
    return 0;
}

// Display the menu options to the user
void displayMenu()
{
    printf("1. Load Tasks File\n");
    printf("2. Add a New Task\n");
    printf("3. Delete a Task\n");
    printf("4. Search for a Task\n");
    printf("5. Perform a Task\n");
    printf("6. View Unperformed Tasks\n");
    printf("7. View Performed Tasks\n");
    printf("8. Restructure the Tasks BST\n");
    printf("9. View the tasks BST info\n");
    printf("10. Exit\n");
}

// Function to recursively free all nodes in the BST and return NULL
Task MakeEmpty(Task T)
{
    if(T != NULL)
    {
        MakeEmpty(T->Left);// Recursively free the left subtree
        MakeEmpty(T->Right);// Recursively free the right subtree
        free(T);// Free the current node
    }
    return NULL;// Return NULL to indicate the tree is now empty
}

// Function to insert a new task into the BST based on its ID
Task Insert(int id, char* name, char* date, float duration, int performed, Task T)
{
    if(T == NULL)
    {
        // Allocate memory for a new node if tree is empty
        T = (struct Node*)malloc(sizeof(struct Node));
        if(T == NULL)
            printf("Out of space!\n"); // Memory allocation failed
        else
        {
            // Initialize the new node with task data
            T->ID = id;
            T->Name = name;
            T->Date = date;
            T->Duration = duration;
            T->perform = performed;
            T->Left = T->Right = NULL;
        }
    }
    else if(id < T->ID) // Recursively insert into the left subtree
        T->Left = Insert(id, name, date, duration, performed, T->Left);
    else if(id > T->ID) // Recursively insert into the right subtree
        T->Right = Insert(id, name, date, duration, performed, T->Right);

    return T;// Return the root of the modified subtree
}

// Function to load tasks from "tasks.txt" file into the BST
Task LoadTask()
{
    Task T = MakeEmpty(NULL);// Ensure BST is empty before loading new tasks
    FILE *in = fopen("tasks.txt", "r");// Open the file for reading

    // Check if the file is successfully opened
    if(in == NULL)
        printf("Error, Can't open the file!\n");

    else
    {
        char FileData[MaxSize];// Buffer to hold each line of the file
        char *str = fgets(FileData, MaxSize, in); // Read the first line

        while(str != NULL)
        {
            // Split the line into fields using '#' as a delimiter
            char* id = strtok(str, "#"); // Extract Task ID
            char* name = strtok(NULL, "#");// Extract Task Name
            char* date = strtok(NULL, "#");// Extract Task Date
            char* dur = strtok(NULL, "#"); // Extract Task Duration

            // Insert the task into the BST with 'performed' flag set to 0
            T = Insert(atoi(id), strdup(name), strdup(date), atof(dur), 0, T);

            // Read the next line
            str = fgets(FileData, MaxSize, in);
        }
        printf("\nTasks loaded successfully!\n\n");
    }

    fclose(in); // Close the file after reading
    return T;  // Return the BST
}

// Function to add a new task to the BST
void AddTask(Task T)
{
    int id;
    char name[MaxSize], date[MaxSize];
    float dur;
    Task newTask;

    // Prompt the user to enter the task ID
    printf("\nPlease enter Task ID: ");
    scanf("%d", &id);

    // Check if a task with the same ID already exists
    if(Find(id, T) != NULL)
    {
        printf("\nTask with id %d already exists. Please try again!\n\n", id);
        return;
    }

    // Prompt the user to enter task details
    printf("\nPlease enter Task name: ");
    getchar();
    scanf("%[^\n]", name);// Read task name with spaces
    getchar();
    printf("\nPlease enter Task date: ");
    scanf("%[^\n]", date);// Read task date
    printf("\nPlease enter Task Duration(hours): ");
    scanf("%f", &dur);// Read task duration

    // Insert based on current organization (op global variable)
    // Organize by ID
    if (op == 4)
    {
        T = Insert(id, strdup(name), strdup(date), dur, 0, T);
    }
    // Organize by Name
    else if(op == 1)
    {
        newTask = MakeEmpty(NULL);  // Create empty task node
        newTask = Insert(id, strdup(name), strdup(date), dur, 0, newTask);
        T = InsertTaskByName(T, newTask);
    }
    // Organize by Date
    else if(op == 2)
    {
        newTask = MakeEmpty(NULL);
        newTask = Insert(id, strdup(name), strdup(date), dur, 0, newTask);
        T = InsertTaskByDate(T, newTask);
    }
    // Organize by Duration
    else if(op == 3)
    {
        newTask = MakeEmpty(NULL);
        newTask = Insert(id, strdup(name), strdup(date), dur, 0, newTask);
        T = InsertTaskByDuration(T, newTask);
    }

    printf("\nTask added successfully!\n\n");
}

// Function to find a task by ID (recursively traverses entire BST)
Task Find(int id, Task T)
{
    if (T == NULL) // Base case: not found
        return NULL;

    if (T->ID == id) // Match found
        return T;

    // Search in the left subtree
    Task found = Find(id, T->Left);
    if (found != NULL) // If found in left, return it
        return found;

    // Otherwise, search in the right subtree
    return Find(id, T->Right);
}

// Find the node with the minimum value in the BST
Task FindMin(Task T)
{
    if (T == NULL)
        return NULL;
    else if (T->Left == NULL)
        return T;
    else
        return FindMin(T->Left);
}

// Delete a task based on the current BST organization (op)
Task Delete(Task T)
{
    int found = 0; // Flag to indicate if a task was successfully found and deleted

    // Delete by ID
    if(op == 4)
    {
        int id;
        printf("\nPlease enter the id of the task that you want to delete: ");
        scanf("%d", &id);
        T = DeleteById(id, T, &found);
        if (!found)
            printf("\nTask with id %d does not exist. Please try again!\n\n", id);
        else
            printf("\nTask with id '%d' deleted successfully!\n\n", id);
    }
    // Delete by Name
    else if(op == 1)
    {
        char name[MaxSize];
        printf("\nPlease enter name of the task that you want to delete: ");
        getchar();
        scanf("%[^\n]", name);
        T = DeleteByName(strdup(name), T, &found);
        if (!found)
            printf("\nTask with name '%s' does not exist. Please try again!\n\n", name);
        else
            printf("\nTask with name '%s' deleted successfully!\n\n", name);
    }
    // Delete by Date
    else if(op == 2)
    {
        char date[MaxSize];
        printf("\nPlease enter date of the task that you want to delete: ");
        getchar();
        scanf("%[^\n]", date);
        T = DeleteByDate(strdup(date), T, &found);
        if (!found)
            printf("\nTask with date '%s' does not exist. Please try again!\n\n", date);
        else
            printf("\nTask with date '%s' deleted successfully!\n\n", date);
    }
    // Delete by Duration
    else if(op == 3)
    {
        float dur;
        printf("\nPlease enter the duration of the task that you want to delete: ");
        scanf("%f", &dur);
        T = DeleteByDuration(dur, T, &found);
        if (!found)
            printf("\nTask with duration %.4f does not exist. Please try again!\n\n", dur);
        else
            printf("\nTask with duration '%.4f' deleted successfully!\n\n", dur);
    }

    return T;
}

// Delete a task by its ID from a BST organized by ID
Task DeleteById(int id, Task T, int *found)
{
    Task temp;
    if (T == NULL)
        return NULL;

    else if(id < T->ID)
        T->Left = DeleteById(id, T->Left, found);
    else if(id > T->ID)
        T->Right = DeleteById(id, T->Right, found);
    else  // Node found
    {
        *found = 1;
        // If node has two children
        if (T->Left && T->Right)
        {
            temp = FindMin(T->Right);
            T->ID = temp->ID;
            T->Name = temp->Name;
            T->Date = temp->Date;
            T->Duration = temp->Duration;
            T->perform = temp->perform;
            T->Right = DeleteById(T->ID, T->Right, found);
        }
        // One or no child
        else
        {
            temp = T;
            T = (T->Left == NULL) ? T->Right : T->Left;
            free(temp);
        }
    }
    return T;
}

// Delete a task by Name in a BST organized by Name
Task DeleteByName(char *name, Task T, int *found)
{
    if (T == NULL)
        return NULL;

    int cmp = strcasecmp(name, T->Name);  // Case-insensitive string comparison

    if (cmp < 0)
        T->Left = DeleteByName(name, T->Left, found);
    else if (cmp > 0)
        T->Right = DeleteByName(name, T->Right, found);
    else  // Node found
    {
        Task temp;
        *found = 1;
        if (T->Left && T->Right)
        {
            temp = FindMin(T->Right);
            T->ID = temp->ID;
            T->Name = temp->Name;
            T->Date = temp->Date;
            T->Duration = temp->Duration;
            T->perform = temp->perform;
            T->Right = DeleteByName(temp->Name, T->Right, found);
        }
        else
        {
            temp = T;
            T = (T->Left == NULL) ? T->Right : T->Left;
            free(temp);
        }
    }

    return T;
}

// Delete a task by Date in a BST organized by Date
Task DeleteByDate(char *date, Task T, int *found)
{
    if (T == NULL)
        return NULL;

    int cmp = strcasecmp(date, T->Date);

    if (cmp < 0)
        T->Left = DeleteByDate(date, T->Left, found);
    else if (cmp > 0)
        T->Right = DeleteByDate(date, T->Right, found);
    else  // Node found
    {
        Task temp;
        *found = 1;
        if (T->Left && T->Right)
        {
            temp = FindMin(T->Right);
            T->ID = temp->ID;
            T->Name = temp->Name;
            T->Date = temp->Date;
            T->Duration = temp->Duration;
            T->perform = temp->perform;
            T->Right = DeleteByDate(temp->Date, T->Right, found);
        }
        else
        {
            temp = T;
            T = (T->Left == NULL) ? T->Right : T->Left;
            free(temp);
        }
    }

    return T;
}

// Delete a task by Duration in a BST organized by Duration
Task DeleteByDuration(float dur, Task T, int *found)
{
    Task temp;
    if (T == NULL)
        return NULL;

    else if(dur < T->Duration)
        T->Left = DeleteByDuration(dur, T->Left, found);
    else if(dur > T->Duration)
        T->Right = DeleteByDuration(dur, T->Right, found);
    else  // Node found
    {
        *found = 1;
        if (T->Left && T->Right)
        {
            temp = FindMin(T->Right);
            T->ID = temp->ID;
            T->Name = temp->Name;
            T->Date = temp->Date;
            T->Duration = temp->Duration;
            T->perform = temp->perform;
            T->Right = DeleteByDuration(T->Duration, T->Right, found);
        }
        else
        {
            temp = T;
            T = (T->Left == NULL) ? T->Right : T->Left;
            free(temp);
        }
    }

    return T;
}

// Search for a task by its name and print all matches
void SearchTaskByName(Task T, char *name)
{
    if (T == NULL)
    {
        printf("\nNo tasks available!\n\n");
        return;
    }

    // If the BST is not organized by name, restructure it temporarily
    Task WorkingTree = T;
    // Tree is sorted by Date, Duration, or ID
    if (op == 2 || op == 3 || op == 4)
    {
        WorkingTree = RestructTasksByName(T); // Rebuild BST by Name
    }

    int count = 1;
    int found = 0;

    // Internal recursive function to search the tree
    void Search(Task node)
    {
        if (node == NULL)
            return;

        Search(node->Left);  // Traverse left subtree

        // If name matches (case-insensitive), print task info
        if (strcasecmp(node->Name, name) == 0)
        {
            printf("Task %d: ID: %d, Name: %s, Date: %s, Duration: %.2f hours\n",
                   count++, node->ID, node->Name, node->Date, node->Duration);
            found = 1;
        }

        Search(node->Right); // Traverse right subtree
    }

    Search(WorkingTree);// Start recursive search
    printf("\n");

    if (!found)
        printf("\nTask with name '%s' is not found, please try again!\n\n", name);

    // Free the rebuilt tree
    if (op == 2 || op == 3 || op == 4)
        free(WorkingTree);
}

void PerformATask(Task T)
{
    // Check if the task tree is empty
    if (T == NULL)
    {
        printf("\nNo tasks available!\n\n");
        return;
    }

    Task found = NULL;

    // If the tree is based on name (op == 1), perform search by name
    if (op == 1)
    {
        char name[MaxSize];
        printf("\nEnter Task Name to perform: ");
        getchar();
        scanf("%[^\n]", name);  // Get the task name from the user

        // Recursive function to search for a task by name
        void Search(Task n)
        {
            if (n == NULL || found != NULL)
                return; // If task is found or tree is empty, return

            Search(n->Left); // Recur on the left subtree
            if (strcasecmp(name, n->Name) == 0 && !n->perform) // If name matches and task isn't performed
                found = n; // Mark the task as found
            Search(n->Right); // Recur on the right subtree
        }

        Search(T); // Start the search from the root

        // Check if a task was found and perform it
        if (found != NULL)
        {
            found->perform = 1; // Mark the task as performed
            printf("\nTask with name '%s' performed successfully!\n\n", found->Name);
        }
        else
        {
            printf("\nNo unperformed task with name '%s' found.\n\n", name);
        }
    }
     // Tree is based on Date
    else if (op == 2)
    {
        char date[MaxSize];
        printf("\nEnter Task Date to perform: ");
        getchar();
        scanf("%[^\n]", date); // Get the task date from the user

        // Recursive function to search for a task by date
        void Search(Task n)
        {
            if (n == NULL || found != NULL)
                return; // If task is found or tree is empty, return

            Search(n->Left); // Recur on the left subtree
            if (strcasecmp(date, n->Date) == 0 && !n->perform) // If date matches and task isn't performed
                found = n; // Mark the task as found
            Search(n->Right); // Recur on the right subtree
        }

        Search(T); // Start the search from the root

        // Check if a task was found and perform it
        if (found != NULL)
        {
            found->perform = 1; // Mark the task as performed
            printf("\nTask with date '%s' performed successfully!\n\n", found->Date);
        }
        else
        {
            printf("\nNo unperformed task with date '%s' found.\n\n", date);
        }
    }
    // Tree is based on Duration
    else if (op == 3)
    {
        float dur;
        printf("\nEnter Task Duration to perform: ");
        scanf("%f", &dur); // Get the task duration from the user

        // Recursive function to search for a task by duration
        void Search(Task n)
        {
            if (n == NULL || found != NULL)
                return; // If task is found or tree is empty, return

            Search(n->Left); // Recur on the left subtree
            if (n->Duration == dur && !n->perform) // If duration matches and task isn't performed
                found = n; // Mark the task as found
            Search(n->Right); // Recur on the right subtree
        }

        Search(T); // Start the search from the root

        // Check if a task was found and perform it
        if (found != NULL)
        {
            found->perform = 1; // Mark the task as performed
            printf("\nTask with duration %.2f performed successfully!\n\n", found->Duration);
        }
        else
        {
            printf("\nNo unperformed task with duration %.2f found.\n\n", dur);
        }
    }
    // Tree is based on ID
    else if (op == 4)
    {
        int id;
        printf("\nEnter Task ID to perform: ");
        scanf("%d", &id);  // Get the task ID from the user

        // Find the task by ID using the Find function
        Task task = Find(id, T);
        if (task != NULL)
        {
            if (!task->perform) // If the task is not already performed
            {
                task->perform = 1; // Mark the task as performed
                printf("\nTask with ID %d performed successfully!\n\n", id);
            }
            else
            {
                printf("\nTask with ID %d is already performed!\n\n", id);
            }
        }
        else
        {
            printf("\nTask with ID %d is not found, please try again!\n\n", id);
        }
    }
}

void viewUnperformedTasks(Task T, int* flag)
{
    if (T == NULL)
        return; // If the tree is empty, return

    // Tree is based on Name
    if (op == 1)
    {
        viewUnperformedTasks(T->Left, flag); // Recur on the left subtree

        // If the task is unperformed, print it
        if (T->perform == 0)
        {
            printf("ID: %d, Name: %s, Date: %s, Duration: %.3f\n",
                   T->ID, T->Name, T->Date, T->Duration);
            *flag = 1; // Set the flag to indicate at least one unperformed task was found
        }

        viewUnperformedTasks(T->Right, flag); // Recur on the right subtree
    }
     // Rebuild by Name for other cases
    else if (op == 2 || op == 3 || op == 4)
    {
        // Rebuild tasks based on Name
        Task task = RestructTasksByName(T);
        if (task != NULL)
        {
            viewUnperformedTasks(task->Left, flag); // Recur on the left subtree

            // If the task is unperformed, print it
            if (task->perform == 0)
            {
                printf("Task%d: ID: %d, Name: %s, Date: %s, Duration: %.3f\n",
                       counter++, task->ID, task->Name, task->Date, task->Duration);
                *flag = 1; // Set the flag to indicate at least one unperformed task was found
            }

            viewUnperformedTasks(task->Right, flag); // Recur on the right subtree
        }
    }
}

void viewPerformedTasks(Task T, int *flag)
{
    if (T == NULL)
        return; // If the tree is empty, return

    // Tree is based on ID
    if (op == 4)
    {
        viewPerformedTasks(T->Left, flag); // Recur on the left subtree

        // If the task is performed, print it
        if (T->perform == 1)
        {
            printf("Task %d: ID: %d, Name: %s, Date: %s, Duration: %.2f hours\n",
                   counter++, T->ID, T->Name, T->Date, T->Duration);
            *flag = 1; // Set the flag to indicate at least one performed task was found
        }

        viewPerformedTasks(T->Right, flag); // Recur on the right subtree
    }
    // Rebuild by ID for other cases
    else if (op == 1 || op == 2 || op == 3)
    {
        // Rebuild tasks based on ID
        Task task = RestructTasksByID(T);
        if (task != NULL)
        {
            viewPerformedTasks(task->Left, flag); // Recur on the left subtree

            // If the task is performed, print it
            if (task->perform == 1)
            {
                printf("Task %d: ID: %d, Name: %s, Date: %s, Duration: %.2f hours\n",
                       counter++, task->ID, task->Name, task->Date, task->Duration);
                *flag = 1; // Set the flag to indicate at least one performed task was found
            }

            viewPerformedTasks(task->Right, flag); // Recur on the right subtree
        }
    }
}

// Function to restructure the BST based on user choice of attribute
Task RestructTasksBST(Task T)
{
    printf("\nRestructure BST based on:\n");
    printf("1. Task Name\n");
    printf("2. Task Date\n");
    printf("3. Task Duration\n");
    printf("4. Task ID\n");
    printf("Choose an option: ");

    int choice;
    scanf("%d", &choice);

    // If the tree is already structured based on the current choice, inform the user
    if (choice == op)
    {
        printf("\nThe tree is already structured based on your choice!\n\n");
        return T;
    }

    // Restructure the tree based on the selected choice
    switch (choice)
    {
    case 1:
        T = RestructTasksByName(T); // Rebuild tree based on Task Name
        op = 1;
        printf("\nBST Restructured based on Task Name successfully!\n\n");
        break;
    case 2:
        T = RestructTasksByDate(T); // Rebuild tree based on Task Date
        op = 2;
        printf("\nBST Restructured based on Task Date successfully!\n\n");
        break;
    case 3:
        T = RestructTasksByDuration(T); // Rebuild tree based on Task Duration
        op = 3;
        printf("\nBST Restructured based on Task Duration successfully!\n\n");
        break;
    case 4:
        T = RestructTasksByID(T); // Rebuild tree based on Task ID
        op = 4;
        printf("\nBST Restructured based on Task ID successfully!\n\n");
        break;
    default:
        printf("\nInvalid choice! Please try again!\n\n");
        return T;
    }

    // Print the restructured tree after successful restructuring
    printf("Task Information:\n");
    counter = 1;
    PrintTree(T); // Function that prints the BST
    printf("\n");
    return T;
}

// Insert task into the tree based on Task Name in lexicographical order
Task InsertTaskByName(Task T, Task NewTask)
{
    if (T == NULL)
        return NewTask; // If T is NULL, place NewTask here

    // Compare the task name to decide the direction of insertion (Left or Right)
    if (strcasecmp(NewTask->Name, T->Name) < 0)
        T->Left = InsertTaskByName(T->Left, NewTask);
    else
        T->Right = InsertTaskByName(T->Right, NewTask);

    return T; // return root always
}

// Function to restructure the BST based on Task Name by creating a new tree
Task RestructTasksByName(Task T)
{
    Task NewTask = NULL; // New tree that will store tasks in the required order

    // Recursive function to traverse the original tree and rebuild it
    void Builder(Task task)
    {
        if (task == NULL)
            return;

        Builder(task->Left); // Traverse left subtree

        // Create a copy of the current task
        Task Copy = (struct Node*)malloc(sizeof(struct Node));
        if (Copy == NULL)
        {
            printf("Out of space!\n");
            return;
        }
        Copy->ID = task->ID;
        Copy->Name = task->Name;
        Copy->Date = task->Date;
        Copy->Duration = task->Duration;
        Copy->perform = task->perform;
        Copy->Left = Copy->Right = NULL;

        // Insert the copied task into the new tree based on name
        NewTask = InsertTaskByName(NewTask, Copy);

        Builder(task->Right); // Traverse right subtree
    }

    Builder(T); // Start the building process from the root
    return NewTask;
}

// Helper function to convert a date string (e.g., "dd/mm/yyyy") to integer values
int dateToInt(char *str, int start, int length) {
    int result = 0;
    for (int i = start; i < start + length; ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        }
    }
    return result;
}

// Function to compare two dates in the "dd/mm/yyyy" format
int CompareDate(char *date1, char *date2) {
    int d1 = dateToInt(date1, 0, 2);
    int m1 = dateToInt(date1, 3, 2);
    int y1 = dateToInt(date1, 6, 4);

    int d2 = dateToInt(date2, 0, 2);
    int m2 = dateToInt(date2, 3, 2);
    int y2 = dateToInt(date2, 6, 4);

    if (y1 != y2) return y1 - y2; // Compare years
    if (m1 != m2) return m1 - m2; // Compare months
    return d1 - d2; // Compare days
}

// Insert task into the tree based on Task Date
Task InsertTaskByDate(Task T, Task NewTask)
{
    if (T == NULL)
        return NewTask; // If T is NULL, place NewTask here

    // Compare the task date to decide the direction of insertion (Left or Right)
    if (CompareDate(NewTask->Date, T->Date) < 0)
        T->Left = InsertTaskByDate(T->Left, NewTask);
    else
        T->Right = InsertTaskByDate(T->Right, NewTask);

    return T; // return root always
}

// Function to restructure the BST based on Task Date
Task RestructTasksByDate(Task T)
{
    Task NewTask = NULL;

    // Recursive function to traverse the original tree and rebuild it
    void Builder(Task task)
    {
        if (task == NULL)
            return;

        Builder(task->Left); // Traverse left subtree

        // Create a copy of the current task
        Task Copy = (struct Node*)malloc(sizeof(struct Node));
        if (Copy == NULL)
        {
            printf("Out of space!\n");
            return;
        }
        Copy->ID = task->ID;
        Copy->Name = task->Name;
        Copy->Date = task->Date;
        Copy->Duration = task->Duration;
        Copy->perform = task->perform;
        Copy->Left = Copy->Right = NULL;

        // Insert the copied task into the new tree based on date
        NewTask = InsertTaskByDate(NewTask, Copy);

        Builder(task->Right); // Traverse right subtree
    }

    Builder(T); // Start the building process from the root
    return NewTask;
}

// Insert task into the tree based on Task Duration
Task InsertTaskByDuration(Task T, Task NewTask)
{
    if (T == NULL)
        return NewTask; // If T is NULL, place NewTask here

    // Compare the task duration to decide the direction of insertion (Left or Right)
    if (NewTask->Duration < T->Duration)
        T->Left = InsertTaskByDuration(T->Left, NewTask);
    else
        T->Right = InsertTaskByDuration(T->Right, NewTask);

    return T; // return root always
}

// Function to restructure the BST based on Task Duration
Task RestructTasksByDuration(Task T)
{
    Task NewTask = NULL;

    // Recursive function to traverse the original tree and rebuild it
    void Builder(Task task)
    {
        if (task == NULL)
            return;

        Builder(task->Left); // Traverse left subtree

        // Create a copy of the current task
        Task Copy = (struct Node*)malloc(sizeof(struct Node));
        if (Copy == NULL)
        {
            printf("Out of space!\n");
            return;
        }
        Copy->ID = task->ID;
        Copy->Name = task->Name;
        Copy->Date = task->Date;
        Copy->Duration = task->Duration;
        Copy->perform = task->perform;
        Copy->Left = Copy->Right = NULL;

        // Insert the copied task into the new tree based on duration
        NewTask = InsertTaskByDuration(NewTask, Copy);

        Builder(task->Right); // Traverse right subtree
    }

    Builder(T); // Start the building process from the root
    return NewTask;
}

// Function to restructure the BST based on Task ID
Task RestructTasksByID(Task T)
{
    Task NewTask = NULL;

    // Recursive function to traverse the original tree and rebuild it
    void Builder(Task task)
    {
        if (task == NULL)
            return;

        Builder(task->Left); // Traverse left subtree

        // Create a copy of the current task
        Task Copy = (struct Node*)malloc(sizeof(struct Node));
        if (Copy == NULL)
        {
            printf("Out of space!\n");
            return;
        }
        Copy->ID = task->ID;
        Copy->Name = strdup(task->Name); // Allocate space for Name and Date
        Copy->Date = strdup(task->Date);
        Copy->Duration = task->Duration;
        Copy->perform = task->perform;
        Copy->Left = Copy->Right = NULL;

        // Insert the copied task into the new tree based on ID
        NewTask = Insert(Copy->ID, Copy->Name, Copy->Date, Copy->Duration, Copy->perform, NewTask);

        Builder(task->Right); // Traverse right subtree
    }

    Builder(T); // Start the building process from the root
    return NewTask;
}

// Function to calculate the height of the tree (the longest path from the root to a leaf)
int getTreeHeight(Task T)
{
    if (T == NULL)
        return -1;  // An empty tree has a height of -1

    // Calculate the height of the left and right subtrees
    int leftHeight = getTreeHeight(T->Left);
    int rightHeight = getTreeHeight(T->Right);

    // Return the larger height plus 1 (for the current node)
    if (leftHeight > rightHeight)
        return leftHeight + 1;
    else
        return rightHeight + 1;
}

// Function to calculate the size of the tree (the total number of nodes (including leaf and internal nodes))
int getTreeSize(Task T) {
    if (T == NULL)
        return 0;  // If the tree is empty, size is 0

    // Recursively calculate the size of left and right subtrees
    int left = getTreeSize(T->Left);
    int right = getTreeSize(T->Right);

    // Return the size of the current subtree (left + right + 1 for the current node)
    return left + right + 1;
}

// Function to count the number of leaf nodes in the tree
// Leaf nodes are the nodes that do not have any children
int getNumOfLeaves(Task T) {

    // If T is NULL, return 0 (no leaves)
    if (T == NULL)
        return 0;

    // If the node has no left or right child, it is a leaf
    if (T->Left == NULL && T->Right == NULL)
        return 1;

    // Recursively count the leaves in the left and right subtrees
    return getNumOfLeaves(T->Left) + getNumOfLeaves(T->Right);
}

// Function to count the number of internal nodes in the tree
// Internal nodes are the nodes that have at least one child
int getNumOfInternalNode(Task T)
{
    // If T is NULL or if T has no children (leaf node), return 0
    if (T == NULL || (T->Left == NULL && T->Right == NULL))
        return 0;

    // Return 1 (current node is an internal node) plus the count of internal nodes in the left and right subtrees
    return 1 + getNumOfInternalNode(T->Left) + getNumOfInternalNode(T->Right);
}

// Function to print the information of the task BST
void viewTasksBSTInfo(Task T)
{
    printf("\nTasks BST Information:");
    printf("\nTree Height: %d", getTreeHeight(T)); // Print the tree height
    printf("\nTree Size: %d", getTreeSize(T)); // Print the tree size (number of nodes)
    printf("\nNumber of leaves (External nodes) : %d", getNumOfLeaves(T)); // Print the number of leaf nodes
    printf("\nNumber of internal nodes: %d\n\n", getNumOfInternalNode(T)); // Print the number of internal nodes
}

// Function to print the entire tree in an in-order traversal
// In-order traversal means it visits the left subtree first, then the current node, and then the right subtree.
void PrintTree(Task T)
{
    // If the current node is not NULL, continue the in-order traversal
    if (T != NULL)
    {
        // Recursively print the left subtree
        PrintTree(T->Left);

        // Print the current task information in the specified format
        printf("Task%d: ID: %d, Name: %s, Date: %s, Duration: %.3f\n", counter++, T->ID, T->Name, T->Date, T->Duration);

        // Recursively print the right subtree
        PrintTree(T->Right);
    }
}

