#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

// Functions prototypes
void readFromFile();
struct node *makeEmpty(struct node *list);
void insert(int valueIn, struct node *head);
void printLinkedList();
void printNumbers(struct node *list);
void printRes(struct node *list);
void addition();
struct node *additionMul(struct node *A, struct node *B);
struct node *subtraction(struct node *A, struct node *B);
void multiplication();
void division();
void operations(int pick);
bool sign(struct node *number);
bool compare(struct node *temp, struct node *temp2);

// Creating the struct for the linked list
struct node
{
    int value;         // Takes one digit
    struct node *next; // Pointer to the next node
    struct node *prev; // Pointer to the previous node
};

// Declaring global variables
struct node *head;        // Pointers to structs
struct node **arr, **res; // Arrays of pointers to structs
int size = 0;             // Number of numbers in the file
FILE *outputFile;         // Output file declaration

// Main
int main()
{
    // Opening the output text file
    outputFile = fopen("output.txt", "w");
    int input = 0;

    // Main Menu
    while (input != 8)
    {
        printf("\n1- Read the input file\n");
        printf("2- Print the saved numbers\n");
        printf("3- Addition\n");
        printf("4- Subtraction\n");
        printf("5- Multiplication\n");
        printf("6- Division\n");
        printf("7- Exit\n");
        printf(".......................\n");
        printf("Please choose an operation: ");
        scanf("%d", &input);
        if (input == 1)
        {
            readFromFile();
        }
        if (input == 7)
        {
            printf("\n*** Goodbye <3 ***\n\n");
            fclose(outputFile);
            break;
        }
        if (size)
        {
            if (input == 2)
            {
                printLinkedList();
            }
            if (input == 3)
            {
                operations(1);
            }
            if (input == 4)
            {
                operations(0);
            }
            if (input == 5)
            {
                multiplication();
            }
            if (input == 6)
            {
                division();
            }
        }

        else
        {
            printf("\nUnavailable! Zero numbers stored.\n");
        }
    }

    return 0;
}

// Function to read from a file
void readFromFile()
{
    // Declaring variables
    int i = 0, temp = 0;
    char chr;

    // Opening the file
    FILE *inputFile;
    inputFile = fopen("input.txt", "r");

    // Opening a file for output

    // Calculating how many numbers is in the file
    chr = getc(inputFile);
    while (chr != EOF)
    {
        // Count whenever new line is encountered
        if (chr == '\n')
        {
            size++;
        }
        // take next character from file.
        chr = getc(inputFile);
    }
    size++;

    // Allocating the memory required for the "size" numbered pointers
    arr = (struct node **)malloc(size * sizeof(struct node *));
    res = (struct node **)malloc(3 * sizeof(struct node *));

    // Clearing the linked list and allocating the memory required
    head = makeEmpty(head);

    // Rereading the file
    rewind(inputFile);

    // Reading the entire file
    while (temp != EOF)
    {
        // Creating the head node and initializing it
        temp = fgetc(inputFile);

        if (temp != 45 && temp != 10 && temp != EOF)
        {
            // Turning characters to integers
            insert(temp - '0', head);
        }

        // 10 = \n to check if we reached a new line
        else if (temp == 10)
        {
            arr[i] = head;
            i++;
            head = makeEmpty(head);
        }

        // checks for negative signs
        else if (temp == 45)
        {
            insert(temp, head);
        }
    }

    // Once it reaches the end of the file
    if (temp == EOF)
    {
        arr[i] = head;
        i++;
    }

    // Make sure the numbers have been read correctly
    if (i > 0)
    {
        printf("\nThe numbers have been read.\n");
    }
    else
    {
        printf("The operation was not successful.\n");
    }
    fclose(inputFile);
}

// Function to allocate the required space for the linked list and set the pointers to null
struct node *makeEmpty(struct node *list)
{
    list = (struct node *)malloc(sizeof(struct node));
    if (list == NULL)
        printf("Out of memory !\n");
    list->next = NULL;
    list->prev = NULL;
    return list;
}

// Function for inserting a new value to a designated place in the doubly linked list
void insert(int valueIn, struct node *head)
{
    // Creating the new node and allocating the memory size needed
    struct node *newNode;
    newNode = (struct node *)malloc(sizeof(struct node));

    // Assigning the wanted value to the new node
    newNode->value = valueIn;

    // Fixing the pointers of the new and previous nodes' pointers
    newNode->next = head->next;
    head->next = newNode;
    newNode->prev = NULL;

    // If the new node has a next, we need to fix it's PREVIOUS pointer
    if (newNode->next != NULL)
    {
        newNode->next->prev = newNode;
    }
}

// Function for inserting a new value at the end of a double linked list
void insertLast(int valueIn, struct node *head)
{
    // Creating the new node and allocating the memory size needed
    struct node *newNode;
    newNode = (struct node *)malloc(sizeof(struct node));

    // Assigning the wanted value to the new node
    newNode->value = valueIn;

    // Fixing the pointers of the new and previous nodes' pointers
    newNode->next = NULL;

    while (head->next != NULL)
    {
        head = head->next;
    }
    head->next = newNode;
    newNode->prev = head;
}

// Function to print the values of the array of linked lists
void printLinkedList()
{
    printf("\nThe list of numbers:\n");
    for (int i = 0; i < size; i++)
    {
        printf("#%d - ", (i + 1));
        while (arr[i]->next != NULL)
        {
            arr[i] = arr[i]->next;
        }
        while (arr[i]->prev != NULL)
        {
            if (arr[i]->value == 45)
            {
                printf("-");
            }
            else
            {
                printf("%d", arr[i]->value);
            }
            arr[i] = arr[i]->prev;
        }
        printf("%d\n", arr[i]->value);
    }

    printf("................\n");
}

// Function to print the values of a single linked list
void printNumbers(struct node *list)
{
    while (list->next != NULL)
    {
        list = list->next;
    }
    while (list->prev != NULL)
    {
        if (list->value == 45)
        {
            fprintf(outputFile, "-");
        }
        else
        {
            fprintf(outputFile, "%d", list->value);
        }
        list = list->prev;
    }
    fprintf(outputFile, "%d", list->value);
}

// Function to print the answers. They have integers in them
void printRes(struct node *list)
{
    while (list->next != NULL)
    {
        list = list->next;
        if (list->value == 45)
        {
            fprintf(outputFile, "-");
        }
        else
        {
            fprintf(outputFile, "%d", list->value);
        }
    }
    printf("\n");
}

// Function to add any two lists
void addition()
{
    int flag = 0;
    while (res[0] != NULL && res[1] != NULL)
    {
        if (res[0]->value == 45)
        {
            res[2]->value = res[1]->value;
            break;
        }
        if (res[1]->value == 45)
        {
            res[2]->value = res[0]->value;
            break;
        }
        insert((res[0]->value) + (res[1]->value) + flag, res[2]);

        if (res[2]->next->value >= 10)
        {
            res[2]->next->value = res[2]->next->value - 10;
            flag = 1;
        }
        else
        {
            flag = 0;
        }
        res[0] = res[0]->next;
        res[1] = res[1]->next;
    }
    while (res[0] != NULL)
    {
        if (res[0]->value != 45)
        {
            insert(res[0]->value + flag, res[2]);
            flag = 0;
        }
        if (res[2]->next->value >= 10)
        {
            res[2]->next->value = res[2]->next->value - 10;
            flag = 1;
        }
        else
        {
            flag = 0;
        }

        res[0] = res[0]->next;
    }
    while (res[1] != NULL)
    {
        if (res[1]->value != 45)
        {
            insert(res[1]->value + flag, res[2]);
            flag = 0;
        }
        if (res[2]->next->value >= 10)
        {
            res[2]->next->value = res[2]->next->value - 10;
            flag = 1;
        }
        else
        {
            flag = 0;
        }
        res[1] = res[1]->next;
    }
    if (flag)
    {
        insert(flag, res[2]);
    }
    while (res[2]->next->value == 0 && res[2]->next->next != NULL)
    {
        res[2] = res[2]->next;
    }
    printRes(res[2]);
    printf("Done.\n");
}

// Function to add lists for multiplication
struct node *additionMul(struct node *A, struct node *B)
{
    int flag = 0, result = 0;
    struct node *temp;
    temp = makeEmpty(temp);
    while (A->next != NULL)
    {
        A = A->next;
    }
    while (B->next != NULL)
    {
        B = B->next;
    }

    while (B != NULL && A != NULL)
    {

        result = A->value + B->value + flag;
        if (result >= 10)
        {
            insert(result - 10, temp);
            flag = 1;
        }
        else
        {
            insert(result, temp);
            flag = 0;
        }

        B = B->prev;
        A = A->prev;
    }
    while (A != NULL)
    {
        insert(A->value + flag, temp);
        flag = 0;

        A = A->prev;
    }
    if (flag)
    {
        insert(flag, temp);
    }

    return temp;
}

// Function to subtract two lists
struct node *subtraction(struct node *A, struct node *B)
{
    int flag = 0, result = 0, counter;

    res[2] = makeEmpty(res[2]);

    while (A != NULL && B != NULL)
    {
        counter++;
        if (A->value == 45)
        {

            break;
        }
        if (B->value == 45)
        {

            break;
        }

        result = (A->value) - (B->value) - flag;
        flag = 0;

        if (result < 0)
        {
            result = result + 10;
            flag = 1;
        }

        insert(result, res[2]);
        A = A->next;
        B = B->next;
    }

    while (A != NULL)
    {
        counter++;
        if (A->value == 0 && flag == 1)
        {
            insert((A->value) + 9, res[2]);
            A = A->next;
            flag = 1;
        }
        else
        {
            if (A->value != 45)
            {
                insert(A->value - flag, res[2]);
                flag = 0;
            }
            A = A->next;
        }
    }

    while (res[2]->next->value == 0 && res[2]->next->next != NULL)
    {
        res[2] = res[2]->next;
        counter--;
    }

    printRes(res[2]);
    printf("Done.\n");
    return (res[2]);
}

// Function to multiply two lists[]
void multiplication()
{
    int result = 0, carry = 0, zeros = 0, negative = 0;
    int choiceOne = 0, choiceTwo = 0;

    printLinkedList();
    printf("Choose two numbers: ");
    scanf("%d %d", &choiceOne, &choiceTwo);

    choiceOne--, choiceTwo--;
    struct node *A = arr[choiceOne];
    struct node *B = arr[choiceTwo];

    fprintf(outputFile, "Your equation is ");
    printNumbers(A);
    fprintf(outputFile, " * ");
    printNumbers(B);
    fprintf(outputFile, " = ");

    res[0] = makeEmpty(res[0]);
    res[1] = makeEmpty(res[1]);
    insert(0, res[1]);

    while (A != NULL && A->value != '-')
    {
        B = arr[choiceTwo];
        for (int i = 0; i < zeros; i++)
        {
            insert(0, res[0]);
        }
        while (B != NULL && B->value != '-')
        {
            result = (((A->value) * (B->value)) + carry);
            insert(result % 10, res[0]);
            carry = result / 10;
            B = B->next;
        }

        if (carry > 0)
        {
            insert(carry, res[0]);
        }

        res[1] = additionMul(res[0], res[1]);
        res[0] = makeEmpty(res[0]);

        carry = 0;
        zeros++;
        A = A->next;
    }

    while (res[1]->next->value == 0 && res[1]->next->next != NULL)
    {
        res[1] = res[1]->next;
    }
    if ((!(A != NULL) && B != NULL) || ((A != NULL) && !(B != NULL)))
    {
        negative = 1;
        if (res[1]->next->value == 0 && res[1]->next->next == NULL)
        {
            negative = 0;
        }
    }
    if (negative)
    {
        fprintf(outputFile, "-");
    }
    printRes(res[1]);
}

// Function to multiply a single number with a list
struct node *multiplicationNum(int A, struct node *B)
{

    int result = 0, carry = 0, zeros = 0, negative = 0;

    struct node *C;
    C = makeEmpty(C);
    while (B->next != NULL)
    {
        B = B->next;
    }

    while (B != NULL)
    {
        result = ((A * (B->value)) + carry);
        insert(result % 10, C);
        carry = result / 10;
        B = B->prev;
    }

    if (carry > 0)
    {
        insert(carry, C);
        carry = 0;
    }

    return C;
}

// Function to divide two lists
void division()
{
    int choiceOne = 0, choiceTwo = 0, div = 0, counter = 0;

    printLinkedList();
    printf("Choose two numbers: ");
    scanf("%d %d", &choiceOne, &choiceTwo);

    choiceOne--, choiceTwo--;
    struct node *A = arr[choiceOne];
    struct node *B = arr[choiceTwo];
    struct node *C;
    struct node *D;
    struct node *F;
    struct node *G;
    C = makeEmpty(C);
    D = makeEmpty(D);
    F = makeEmpty(F);
    G = makeEmpty(G);

    fprintf(outputFile, "\nYour equation is ");
    printNumbers(A);
    fprintf(outputFile, " / ");
    printNumbers(B);
    fprintf(outputFile, " = \n");

    if (compare(A, B))
    {
        while (A->next)
        {
            A = A->next;
        }
        while (A != NULL)
        {
            insert(A->value, C);
            if (compare(C, B))
            {
                while (compare(C, B))
                {
                    G = C;
                    printf("\n");
                    C = subtraction(C, B);
                    counter++;
                    if (C->value == 0)
                    {
                        C = C->next->next;
                    }
                }
                insert(counter, F);
                printf("\nG = ");
                printRes(G);
                printf("\nB = ");
                printf("%d", B->value);
                B = multiplicationNum(counter, B);
                D = subtraction(G, B);
                while (D->next != NULL)
                {
                    D = D->next;
                    insert(D->value, A);
                }
                printf(" counter = %d", counter);

                counter = 0;
                C = makeEmpty(C);
                D = makeEmpty(D);
                G = makeEmpty(G);
            }

            if (compare(B, A))
            {
                break;
            }
            A = A->prev;
        }
    }
    else
    {
        printf("0\n");
    }
    printf("F = %d", F->value);
}

// Function to decide which operation
void operations(int pick)
{
    int choiceOne = 0, choiceTwo = 0;

    printLinkedList();
    printf("Choose two numbers: ");
    scanf("%d %d", &choiceOne, &choiceTwo);

    choiceOne--, choiceTwo--;

    res[0] = arr[choiceOne];
    res[1] = arr[choiceTwo];
    res[2] = makeEmpty(res[2]);

    // A + B
    if (pick && sign(res[0]) && sign(res[1]))
    {
        fprintf(outputFile, "Your equation is ");
        printNumbers(res[0]);
        fprintf(outputFile, " + ");
        printNumbers(res[1]);
        fprintf(outputFile, " = ");
        addition();
        fprintf(outputFile, "\n");
        return;
    }
    // -A + - B = - (A + B)
    else if (pick && !sign(res[0]) && !sign(res[1]))
    {
        fprintf(outputFile, "Your equation is ");
        printNumbers(res[0]);
        fprintf(outputFile, " + ");
        printNumbers(res[1]);
        fprintf(outputFile, " = ");
        fprintf(outputFile, "-");
        addition();
        fprintf(outputFile, "\n");
        return;
    }
    // A + -B = A - B
    else if (pick && sign(res[0]) && !sign(res[1]))
    {
        fprintf(outputFile, "Your equation is ");
        printNumbers(res[0]);
        fprintf(outputFile, " + ");
        printNumbers(res[1]);
        fprintf(outputFile, " = ");
        if (compare(res[0], res[1]))
        {
            subtraction(res[0], res[1]);
        }
        else
        {
            fprintf(outputFile, "-");
            subtraction(res[1], res[0]);
        }
        fprintf(outputFile, "\n");
        return;
    }
    // -A + B = B - A = - (A - B)
    else if (pick && !sign(res[0]) && sign(res[1]))
    {
        fprintf(outputFile, "Your equation is ");
        printNumbers(res[0]);
        fprintf(outputFile, " + ");
        printNumbers(res[1]);
        fprintf(outputFile, " = ");
        if (compare(res[0], res[1]))
        {
            fprintf(outputFile, "-");
            subtraction(res[0], res[1]);
        }
        else
        {
            subtraction(res[1], res[0]);
        }
        fprintf(outputFile, "\n");
        return;
    }
    // A - B
    else if (!pick && sign(res[0]) && sign(res[1]))
    {
        fprintf(outputFile, "Your equation is ");
        printNumbers(res[0]);
        fprintf(outputFile, " - ");
        printNumbers(res[1]);
        fprintf(outputFile, " = ");
        if (compare(res[0], res[1]))
        {
            subtraction(res[0], res[1]);
        }
        else
        {
            fprintf(outputFile, "-");
            subtraction(res[1], res[0]);
        }
        fprintf(outputFile, "\n");
        return;
    }
    // A - - B = A + B
    else if (!pick && sign(res[0]) && !sign(res[1]))
    {
        fprintf(outputFile, "Your equation is ");
        printNumbers(res[0]);
        fprintf(outputFile, " - ");
        printNumbers(res[1]);
        fprintf(outputFile, " = ");
        addition();
        fprintf(outputFile, "\n");
        return;
    }
    // -A - B = - (A + B)
    else if (!pick && !sign(res[0]) && sign(res[1]))
    {
        fprintf(outputFile, "Your equation is ");
        printNumbers(res[0]);
        fprintf(outputFile, " - ");
        printNumbers(res[1]);
        fprintf(outputFile, " = ");
        fprintf(outputFile, "-");
        addition();
        fprintf(outputFile, "\n");
        return;
    }
    // -A - - B = -A + B
    else if (!pick && !sign(res[0]) && !sign(res[1]))
    {
        fprintf(outputFile, "Your equation is ");
        printNumbers(res[0]);
        fprintf(outputFile, " - ");
        printNumbers(res[1]);
        fprintf(outputFile, " = ");
        if (compare(res[0], res[1]))
        {
            fprintf(outputFile, "-");
            subtraction(res[0], res[1]);
        }
        else
        {
            subtraction(res[1], res[0]);
        }
        fprintf(outputFile, "\n");
        return;
    }
}

// Function to check the sign of a number
// True if positive and false if negative
bool sign(struct node *number)
{
    while (number->next != NULL)
    {
        number = number->next;
    }
    if (number->value == 45)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Function to compare two numbers
// True if the first is larger
bool compare(struct node *temp, struct node *temp2)
{
    struct node *A = temp;
    struct node *B = temp2;

    while (A->next != NULL)
    {
        temp = temp->next;
        A = A->next;
    }
    while (B->next != NULL)
    {
        temp2 = temp2->next;
        B = B->next;
    }

    int sizeA = 0, sizeB = 0;
    while (A != NULL)
    {
        if (A->value != 45)
        {
            sizeA++;
        }
        A = A->prev;
    }
    while (B != NULL)
    {

        if (B->value != 45)
        {
            sizeB++;
        }
        B = B->prev;
    }

    if (sizeA > sizeB)
    {
        return true;
    }
    else if (sizeA < sizeB)
    {
        return false;
    }

    if (temp->value == 45)
    {
        temp = temp->next;
    }
    if (temp2->value == 45)
    {
        temp2 = temp2->next;
    }
    while (sizeA-- > 0)
    {

        if (temp->value > temp2->value)
        {
            return true;
        }
        else if (temp2->value > temp->value)
        {
            return false;
        }
        temp = temp->prev;
        temp2 = temp2->prev;
    }
    return false;
}