// Name: Sojood Nazih Asfour, Id: 1230298, Section: 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxSize 100

struct Node
{
    int ID;
    char* Name;
    char* Date;
    float Duration;
    int perform;
    struct Node* Left;
    struct Node* Right;
};

//Create Task
typedef struct Node* Task;
int op = 4, counter;

void displayMenu();
Task MakeEmpty(Task);
Task Insert(int, char*, char*, float,int, Task);
Task LoadTask();
void AddTask(Task);
Task Find(int, Task);
Task FindName(char*, Task);
Task FindDate(char*, Task);
Task FindDuration(float, Task);
Task FindMin(Task);
Task Delete(Task);
Task DeleteById(int, Task, int*);
Task DeleteByName(char*, Task, int*);
Task DeleteByDate(char*, Task, int*);
Task DeleteByDuration(float, Task, int*);
void SearchTaskByName(Task, char*);
void PerformATask(Task);
void viewUnperformedTasks(Task, int*);
void viewPerformedTasks(Task,int*);
Task RestructTasksBST(Task);
Task InsertTaskByName(Task,Task);
Task RestructTasksByName(Task);
Task InsertTaskByDate(Task,Task);
Task RestructTasksByDate(Task);
Task InsertTaskByDuration(Task,Task);
Task RestructTasksByDuration(Task);
Task RestructTasksByID(Task);
void PrintTree(Task);

int main()
{
    int id,found = 0;
    char name[MaxSize];
    Task T,NewTask;
    printf("Welcome to the Task Management System....\n\n");
    int choice = 0;
    printf("Please enter an option from the menu:\n");
    displayMenu();
    scanf("%d", &choice);

    // Ensure tasks are loaded before performing operations
    if(choice!=1 )
    {
        while(choice!=1 && choice != 10)
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
    while(choice != 10)
    {
        switch(choice)
        {
        case 1:
            T = LoadTask();
            PrintTree(T);
            printf("\n");
            break;
        case 2:
            AddTask(T);
            PrintTree(T);
            break;
        case 3:
            T = Delete(T);
            PrintTree(T);
            break;
        case 4:
            printf("\nPlease enter Task name: ");
            getchar();  // To consume any newline character left in the input buffer
            scanf("%[^\n]", name);  // Read the task name with spaces
            SearchTaskByName(T,name);
            break;
        case 5:
            PerformATask(T);
            break;
        case 6:
            counter = 1;
            viewUnperformedTasks(T, &found);
            printf("\n");
            if (!found)
                printf("There are no unperformed Tasks to display!\n\n");
            break;
        case 7:
            counter = 1;
            viewPerformedTasks(T, &found);
            printf("\n");
            if (!found)
                printf("There are no performed Tasks to display!\n\n");
            break;
        case 8:
            T = RestructTasksBST(T);
            break;
        default:
            printf("\nInvalid choice! PLease try again!\n\n");
            break;
        }
        printf("Please enter an option from the menu:\n");
        displayMenu();
        scanf("%d", &choice);

    }
    printf("\nExit from the program...\nThank you for using this program...\nGood bye!\n");
    return 0;
}

//display menu for the user
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

Task MakeEmpty(Task T)
{
    if(T != NULL)
    {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return NULL;
}


Task Insert(int id, char* name, char* date, float duration,int performed, Task T)
{
    if(T == NULL)
    {
        T = (struct Node*)malloc(sizeof(struct Node));
        if(T == NULL)
            printf("Out of space!\n");
        else
        {
            T->ID = id;
            T->Name = name;
            T->Date = date;
            T->Duration = duration;
            T->perform = performed;
            T->Left = T->Right = NULL;
        }
    }

    else if(id < T->ID)
        T->Left = Insert(id,name,date,duration,performed,T->Left);
    else if(id > T->ID)
        T->Right = Insert(id,name,date,duration,performed,T->Right);

    return T;
}

Task LoadTask()
{
    Task T = MakeEmpty(NULL);
    FILE *in = fopen("tasks.txt", "r");
    // Check if the file is successfully opened
    if(in == NULL)
        printf("Error, Can't open the file!\n");

    else
    {
        // Declare a buffer to store each line from the file
        char FileData[MaxSize];

        // Read the first line from the file
        char *str = fgets(FileData, MaxSize, in);

        // Continue reading lines from the file until the end of file
        while(str != NULL)
        {
            // Tokenize the line by '#' delimiter to extract task attributes
            char* id = strtok(str, "#");         // Extract Task ID
            char* name = strtok(NULL, "#");      // Extract Task Name
            char* date = strtok(NULL, "#");      // Extract Task Date
            char* dur = strtok(NULL, "#");       // Extract Task Duration

            // Insert the parsed task into the task list (T)
            T = Insert(atoi(id), strdup(name), strdup(date), atof(dur),0, T);
            // Read the next line from the file
            str = fgets(FileData, MaxSize, in);
        }
        printf("\nTasks loaded successfully!\n\n");
    }
    fclose(in);
    return T;
}

void AddTask(Task T)
{
    int id;
    char name[MaxSize], date[MaxSize];
    float dur;
    Task newTask;

    // Prompt the user to enter the task ID
    printf("\nPlease enter Task ID: ");
    scanf("%d", &id);
    if(Find(id, T) != NULL)
    {
        printf("\nTask with id %d already exists. Please try again!\n\n", id);
        return;
    }
    // Prompt the user to enter the task information
    printf("\nPlease enter Task name: ");
    getchar();
    scanf("%[^\n]", name);
    getchar();
    printf("\nPlease enter Task date: ");
    scanf("%[^\n]", date);
    printf("\nPlease enter Task Duration(hours): ");
    scanf("%f", &dur);
    if (op == 4)
    {
        T = Insert(id, strdup(name), strdup(date), dur,0, T);
    }
    else if(op == 1)
    {
        newTask = MakeEmpty(NULL);
        newTask = Insert(id, strdup(name), strdup(date), dur,0, newTask);
        T = InsertTaskByName(T,newTask);
    }
    else if(op == 2)
    {
        newTask = MakeEmpty(NULL);
        newTask = Insert(id, strdup(name), strdup(date), dur,0, newTask);
        T = InsertTaskByDate(T,newTask);
    }
    else if(op == 3)
    {
        newTask = MakeEmpty(NULL);
        newTask = Insert(id, strdup(name), strdup(date), dur,0, newTask);
        T = InsertTaskByDuration(T,newTask);
    }
    printf("\nTask added successfully!\n\n");
}

Task Find(int id, Task T)
{
    if (T == NULL)
        return NULL;

    if (T->ID == id)
        return T;

    Task found = Find(id, T->Left);
    if (found != NULL)
        return found;

    return Find(id, T->Right);
}

Task FindName(char* name, Task T)
{
    if(T == NULL)
        return NULL;
    else if(strcasecmp(name, T->Name) < 0)
        return FindName(name, T->Left);
    else if(strcasecmp(name, T->Name) > 0)
        return FindName(name, T->Right);
    else
        return T;
}

Task FindDate(char* date, Task T)
{
    if(T == NULL)
        return NULL;
    else if(strcasecmp(date, T->Date) < 0)
        return FindDate(date, T->Left);
    else if(strcasecmp(date, T->Date) > 0)
        return FindDate(date, T->Right);
    else
        return T;
}
Task FindDuration(float dur, Task T)
{
    if(T == NULL)
        return NULL;
    else if(dur < T->Duration)
        return FindDuration(dur, T->Left);
    else if(dur > T->Duration)
        return FindDuration(dur, T->Right);
    else
        return T;
}

Task FindMin(Task T)
{
    if(T == NULL)
        return NULL;
    else if(T->Left == NULL)
        return T;
    else return FindMin(T->Left);
}
Task Delete(Task T)
{
    int found = 0;  // Flag to indicate whether the task was found
    if(op == 4)
    {
        int id;
        printf("\nPlease enter the id of the task that you want to delete: ");
        scanf("%d", &id);
        T = DeleteById(id,T,&found);
        if(!found)
            printf("\nTask with id %d does not exist. Please try again!\n\n", id);
        else
            printf("\nTask with id '%d' deleted successfully!\n\n", id);
    }
    else if(op == 1)
    {
        char name[MaxSize];
        printf("\nPlease enter name of the task that you want to delete: ");
        getchar();
        scanf("%[^\n]", name);
        T = DeleteByName(strdup(name),T, &found);
        // If no task was found, print an error message
        if (!found)
        {
            printf("\nTask with name '%s' does not exist. Please try again!\n\n", name);
        }
        else
            printf("\nTask with name '%s' deleted successfully!\n\n", name);
    }
    else if(op == 2)
    {
        char date[MaxSize];
        printf("\nPlease enter date of the task that you want to delete: ");
        getchar();
        scanf("%[^\n]", date);
        T = DeleteByDate(strdup(date),T, &found);
        // If no task was found, print an error message
        if (!found)
        {
            printf("\nTask with date '%s' does not exist. Please try again!\n\n", date);
        }
        else
            printf("\nTask with date '%s' deleted successfully!\n\n", date);
    }
    else if(op == 3)
    {
        float dur;
        printf("\nPlease enter the duration of the task that you want to delete: ");
        scanf("%f", &dur);
        T = DeleteByDuration(dur,T,&found);
        if(!found)
            printf("\nTask with duration %.4f does not exist. Please try again!\n\n", dur);
        else
            printf("\nTask with duration '%.4f' deleted successfully!\n\n", dur);
    }
    return T;
}

Task DeleteById(int id, Task T,int *found)
{
    Task temp;
    if (T == NULL)
        return NULL;

    else if(id < T->ID)
        T->Left = DeleteById(id, T->Left,found);
    else if(id > T->ID)
        T->Right = DeleteById(id,T->Right,found);
    else
    {
        *found = 1;
        if(T->Left && T->Right)
        {
            temp = FindMin(T->Right);
            T->ID = temp->ID;
            T->Name = temp->Name;
            T->Date = temp->Date;
            T->Duration = temp->Duration;
            T->perform = temp->perform;
            T->Right = DeleteById(T->ID, T->Right,found);
        }
        else
        {
            temp = T;
            if(T->Left == NULL)
                T = T->Right;
            else if(T->Right == NULL)
                T = T->Left;
            free(temp);
        }
    }
    return T;
}

Task DeleteByName(char *name, Task T, int* found)
{
    // Base case: if the tree is empty, no task with the given name exists.
    if (T == NULL)
    {
        return NULL;  // Simply return NULL if no task is found
    }

    int cmp = strcasecmp(name, T->Name);  // Case-insensitive comparison to search for the task

    if (cmp < 0)
    {
        T->Left = DeleteByName(name, T->Left, found);  // Traverse left subtree
    }
    else if (cmp > 0)
    {
        T->Right = DeleteByName(name, T->Right, found); // Traverse right subtree
    }
    else
    {
        // We found a task with the matching name, now delete it
        Task temp;

        // Mark that we found the task
        *found = 1;

        // Case 1: Node has both left and right children
        if (T->Left && T->Right)
        {
            // Find the minimum value in the right subtree
            temp = FindMin(T->Right);
            T->ID = temp->ID;
            T->Name = temp->Name;
            T->Date = temp->Date;
            T->Duration = temp->Duration;
            T->perform = temp->perform;

            // Delete the node that was copied to the current node
            T->Right = DeleteByName(temp->Name, T->Right, found);
        }
        else
        {
            // Case 2: Node has no left child or no right child
            temp = T;
            if (T->Left == NULL)
                T = T->Right; // Take the right child
            else if (T->Right == NULL)
                T = T->Left; // Take the left child

            free(temp);
        }

    }

    return T; // Return the updated tree
}

Task DeleteByDate(char* date, Task T, int* found)
{
    // Base case: if the tree is empty, no task with the given name exists.
    if (T == NULL)
    {
        return NULL;  // Simply return NULL if no task is found
    }

    int cmp = strcasecmp(date, T->Date);  // Case-insensitive comparison to search for the task

    if (cmp < 0)
    {
        T->Left = DeleteByDate(date, T->Left, found);  // Traverse left subtree
    }
    else if (cmp > 0)
    {
        T->Right = DeleteByDate(date, T->Right, found); // Traverse right subtree
    }
    else
    {
        // We found a task with the matching name, now delete it
        Task temp;

        // Mark that we found the task
        *found = 1;

        // Case 1: Node has both left and right children
        if (T->Left && T->Right)
        {
            // Find the minimum value in the right subtree
            temp = FindMin(T->Right);
            T->ID = temp->ID;
            T->Name = temp->Name;
            T->Date = temp->Date;
            T->Duration = temp->Duration;
            T->perform = temp->perform;

            // Delete the node that was copied to the current node
            T->Right = DeleteByDate(temp->Date, T->Right, found);
        }
        else
        {
            // Case 2: Node has no left child or no right child
            temp = T;
            if (T->Left == NULL)
                T = T->Right; // Take the right child
            else if (T->Right == NULL)
                T = T->Left; // Take the left child

            free(temp);
        }

    }

    return T; // Return the updated tree
}

Task DeleteByDuration(float dur, Task T, int*found)
{
    Task temp;
    if (T == NULL)
        return NULL;

    else if(dur < T->Duration)
        T->Left = DeleteByDuration(dur, T->Left,found);
    else if(dur > T->Duration)
        T->Right = DeleteByDuration(dur,T->Right,found);
    else
    {
        *found = 1;
        if(T->Left && T->Right)
        {
            temp = FindMin(T->Right);
            T->ID = temp->ID;
            T->Name = temp->Name;
            T->Date = temp->Date;
            T->Duration = temp->Duration;
            T->perform = temp->perform;
            T->Right = DeleteByDuration(T->Duration, T->Right,found);
        }
        else
        {
            temp = T;
            if(T->Left == NULL)
                T = T->Right;
            else if(T->Right == NULL)
                T = T->Left;
            free(temp);
        }
    }
    return T;
}


void SearchTaskByName(Task T, char *name)
{
    if (T == NULL)
    {
        printf("\nNo tasks available!\n\n");
        return;
    }

    // Check if tree is based on name or not
    Task WorkingTree = T;
    if (op == 2 || op == 3 || op == 4) // if op=2 or op=3 or op=4 , tree is based on Date or duration or ID, we need to rebuild
    {
        WorkingTree = RestructTasksByName(T);
    }

    int count = 1;
    int found = 0;

    void Search(Task node)
    {
        if (node == NULL)
            return;

        Search(node->Left);

        if (strcasecmp(node->Name, name) == 0)
        {
            printf("Task %d: ID: %d, Name: %s, Date: %s, Duration: %.2f hours\n",
                   count++, node->ID, node->Name, node->Date, node->Duration);
            found = 1;
        }

        Search(node->Right);
    }

    Search(WorkingTree);
    printf("\n");

    if (!found)
        printf("\nTask with name '%s' is not found, please try again!\n\n", name);

    // Free the temporary tree if we rebuilt
    if (op == 2 || op == 3 || op == 4)
        free(WorkingTree);
}


void PerformATask(Task T)
{
    if (T == NULL)
    {
        printf("\nNo tasks available!\n\n");
        return;
    }

    Task found = NULL;

    if (op == 1)    // Based on Name
    {
        char name[MaxSize];
        printf("\nEnter Task Name to perform: ");
        getchar();
        scanf("%[^\n]", name);

        void Search(Task n)
        {
            if (n == NULL || found != NULL)
                return;
            Search(n->Left);
            if (strcasecmp(name, n->Name) == 0 && !n->perform)
                found = n;
            Search(n->Right);
        }

        Search(T);
        if (found != NULL)
        {
            found->perform = 1;
            printf("\nTask with name '%s' performed successfully!\n\n", found->Name);
        }
        else
        {
            printf("\nNo unperformed task with name '%s' found.\n\n", name);
        }

    }
    else if (op == 2)      // Based on Date
    {
        char date[MaxSize];
        printf("\nEnter Task Date to perform: ");
        getchar();
        scanf("%[^\n]", date);

        void Search(Task n)
        {
            if (n == NULL || found != NULL)
                return;
            Search(n->Left);
            if (strcasecmp(date, n->Date) == 0 && !n->perform)
                found = n;
            Search(n->Right);
        }

        Search(T);
        if (found != NULL)
        {
            found->perform = 1;
            printf("\nTask with date '%s' performed successfully!\n\n", found->Date);
        }
        else
        {
            printf("\nNo unperformed task with date '%s' found.\n\n", date);
        }

    }
    else if (op == 3)      // Based on Duration
    {
        float dur;
        printf("\nEnter Task Duration to perform: ");
        scanf("%f", &dur);

        void Search(Task n)
        {
            if (n == NULL || found != NULL)
                return;
            Search(n->Left);
            if (n->Duration  == dur && !n->perform)
                found = n;
            Search(n->Right);
        }

        Search(T);
        if (found != NULL)
        {
            found->perform = 1;
            printf("\nTask with duration %.2f performed successfully!\n\n", found->Duration);
        }
        else
        {
            printf("\nNo unperformed task with duration %.2f found.\n\n", dur);
        }

    }
    else if (op == 4)      // Based on ID
    {
        int id;
        printf("\nEnter Task ID to perform: ");
        scanf("%d", &id);
        Task task = Find(id, T);
        if (task != NULL)
        {
            if (!task->perform)
            {
                task->perform = 1;
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
        return;  // Base case for recursion

    // If op == 1, just traverse the tree and check for unperformed tasks
    if (op == 1)
    {
        viewUnperformedTasks(T->Left,flag);  // Recur on left subtree
        if (T->perform == 0)  // Check if task is unperformed
        {
            printf("ID: %d, Name: %s, Date: %s, Duration: %.3f\n",
                   T->ID, T->Name, T->Date, T->Duration);
            *flag = 1;
        }
        viewUnperformedTasks(T->Right,flag);  // Recur on right subtree
    }
    else if (op == 2 || op == 3 || op == 4)
    {
        // Restructure tasks by name if needed (only if op is 2, 3, or 4)
        Task task = RestructTasksByName(T);
        if (task != NULL)
        {
            viewUnperformedTasks(task->Left,flag);  // Recur on left subtree
            if (task->perform == 0)  // Check if task is unperformed
            {
                printf("Task%d: ID: %d, Name: %s, Date: %s, Duration: %.3f\n",
                       counter++, task->ID, task->Name, task->Date, task->Duration);
                *flag = 1;
            }
            viewUnperformedTasks(task->Right, flag);  // Recur on right subtree
        }
    }
}


void viewPerformedTasks(Task T, int *flag)
{
    if (T == NULL)
        return;

    if (op == 4)
    {
        viewPerformedTasks(T->Left, flag);

        if (T->perform == 1)
        {
            printf("Task %d: ID: %d, Name: %s, Date: %s, Duration: %.2f hours\n",
                   counter++, T->ID, T->Name, T->Date, T->Duration);
            *flag = 1;
        }

        viewPerformedTasks(T->Right, flag);
    }
    else if (op == 1 || op == 2 || op == 3)
    {
        Task task = RestructTasksByID(T);  // Assuming this restructures by ID
        if (task != NULL)
        {
            viewPerformedTasks(task->Left, flag);

            if (task->perform == 1)
            {
                printf("Task %d: ID: %d, Name: %s, Date: %s, Duration: %.2f hours\n",
                       counter++, task->ID, task->Name, task->Date, task->Duration);
                *flag = 1;
            }

            viewPerformedTasks(task->Right, flag);
        }
    }
}


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

    if (choice == op)
    {
        printf("\nThe tree is already structured based on your choice!\n\n");
        return T;
    }

    switch (choice)
    {
    case 1:
        T = RestructTasksByName(T);
        op = 1;
        printf("\nBST Restructured based on Task Name successfully!\n\n");
        break;
    case 2:
        T = RestructTasksByDate(T);
        op = 2;
        printf("\nBST Restructured based on Task Date successfully!\n\n");
        break;
    case 3:
        T = RestructTasksByDuration(T);
        op = 3;
        printf("\nBST Restructured based on Task Duration successfully!\n\n");
        break;
    case 4:
        T = RestructTasksByID(T);
        op = 4;
        printf("\nBST Restructured based on Task ID successfully!\n\n");
        break;
    default:
        printf("\nInvalid choice! Please try again!\n\n");
        return T;
    }

    printf("Task Information:\n");
    counter = 1;
    PrintTree(T);

    return T;
}


Task InsertTaskByName(Task T, Task NewTask)
{
    if (T == NULL)
        return NewTask; // If T is NULL, place NewTask here

    if (strcasecmp(NewTask->Name, T->Name) < 0)
        T->Left = InsertTaskByName(T->Left, NewTask);
    else
        T->Right = InsertTaskByName(T->Right, NewTask);

    return T; // return root always
}


Task RestructTasksByName(Task T)
{
    Task NewTask = NULL;
    void Builder(Task task)
    {
        if(task == NULL)
            return;
        Builder(task->Left);
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

        NewTask = InsertTaskByName(NewTask, Copy);

        Builder(task->Right);
    }
    Builder(T);
    return NewTask;
}

Task InsertTaskByDate(Task T, Task NewTask)
{
    if (T == NULL)
        return NewTask; // If T is NULL, place NewTask here

    if (strcasecmp(NewTask->Date, T->Date) < 0)
        T->Left = InsertTaskByDate(T->Left, NewTask);
    else
        T->Right = InsertTaskByDate(T->Right, NewTask);

    return T; // return root always
}

Task RestructTasksByDate(Task T)
{
    Task NewTask = NULL;
    void Builder(Task task)
    {
        if(task == NULL)
            return;
        Builder(task->Left);
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

        NewTask = InsertTaskByDate(NewTask, Copy);

        Builder(task->Right);
    }
    Builder(T);
    return NewTask;
}

Task InsertTaskByDuration(Task T, Task NewTask)
{
    if (T == NULL)
        return NewTask; // If T is NULL, place NewTask here

    if (NewTask->Duration < T->Duration)
        T->Left = InsertTaskByDuration(T->Left, NewTask);
    else
        T->Right = InsertTaskByDuration(T->Right, NewTask);

    return T; // return root always
}

Task RestructTasksByDuration(Task T)
{
    Task NewTask = NULL;
    void Builder(Task task)
    {
        if(task == NULL)
            return;
        Builder(task->Left);
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

        NewTask = InsertTaskByDuration(NewTask, Copy);

        Builder(task->Right);
    }
    Builder(T);
    return NewTask;
}

Task RestructTasksByID(Task T)
{
    Task NewTask = NULL;
    void Builder(Task task)
    {
        if(task == NULL)
            return;
        Builder(task->Left);
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

        NewTask = Insert(Copy->ID,Copy->Name,Copy->Date,Copy->Duration,Copy->perform,NewTask);

        Builder(task->Right);
    }
    Builder(T);
    return NewTask;
}

void PrintTree(Task T)
{
    if (T != NULL)
    {
        PrintTree(T->Left);
        printf("Task%d: ID: %d, Name: %s, Date: %s, Duration: %.3f\n", counter++, T->ID, T->Name, T->Date,T->Duration);
        PrintTree(T->Right);
    }
}
