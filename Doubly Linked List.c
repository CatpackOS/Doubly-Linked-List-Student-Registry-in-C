#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;
typedef double f64;

typedef struct Node{
    char name[50];
    i32 am;
    f32 wallet;
    struct Node *left;
    struct Node *right;
}Node;


Node *createNode();
void toLowerString(char *str);
void readInt(i32 *value);
void readFloat(f32 *value);
void cleanInput(char *str, int size);
void display(Node *head);
void debt(Node const *head);
Node *search(Node *head, char lName[50]);
Node *insert(Node *head, i32 index, Node *selectedNode);
void freeMemory(Node *head);


Node *createNode() {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed \n");
        return NULL;
    }
    newNode->left = NULL;
    newNode->right = NULL;

    printf("Enter AM: ");
    readInt(&newNode->am);

    printf("Enter Name: ");
    cleanInput(newNode->name,50);

    printf("Enter cost: ");
    readFloat(&newNode->wallet);

    return newNode;
}


void toLower(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = (char)tolower((unsigned char)str[i]);
    }
}


void readInt(i32 *value) {
    char buf[32];
    char *endptr;

    while (1) {
        fgets(buf, sizeof(buf), stdin);
        *value = (i32)strtol(buf, &endptr, 10);
        if (endptr != buf) {
            break;
        }
        printf("Invalid input! Please enter a number: ");
    }
}


void readFloat(f32 *value) {
    char buf[32];
    char *endptr;

    while (1) {
        fgets(buf, sizeof(buf), stdin);
        *value = strtof(buf, &endptr);

        if (endptr != buf) {
            break;
        }
        printf("Invalid input! Please enter a number: ");
    }
}


void cleanInput(char *str, int const size ) {
    fgets(str, size, stdin);
    str[strcspn(str, "\n")] = 0;
}


void display(Node *head) {
    while (head != NULL) {
        printf("Name: %s AM: %d cost: %.2f \n", head->name, head->am, head->wallet);
        head = head->right;
    }
}


void debt(Node const *head) {
    f32 Sum = 0;
    u16 people = 0;
    while (head != NULL) {
        Sum += head->wallet;
        people++;
        head = head->right;
    }

    if (people > 0) {
        f32 average = 0;
        average = Sum / (f32)people;
        printf("The sum is: %.2f \n",Sum);
        printf("Average: %.2f \n", average);
    }
    else {
        printf("Can't divide with 0 people \n");
    }


}

Node *search(Node *head, char lName[50]) {
    while (head != NULL) {
        if (strcmp(head->name, lName) == 0) {
            return head;
        }
        head = head->right;
    }
    return NULL;
}

Node *insert(Node *head, i32 const index, Node *selectedNode) {
    if (head == NULL) {
        printf("No list is appearing \n");
        return NULL;
    }


    if (index == 0) {
        head->left = selectedNode;
        selectedNode->left = NULL;
        selectedNode->right = head;
        return selectedNode;
    }
    else if (index > 0) {
        i16 i = 0;
        while (i < index && head->right != NULL) {
            head = head->right;
            i++;
        }
        selectedNode->right = head->right;
        selectedNode->left = head;
        if (head->right != NULL) {
            head->right->left = selectedNode;
        }
        head->right = selectedNode;
        while (head->left != NULL) {
            head = head->left;
        }
        return head;

    }

    else {
        i32 targetAm;
        printf("Enter AM to search to insert into list \n");
        readInt(&targetAm);
        while (head != NULL) {
            if (head->am == targetAm) {
                selectedNode->right = head->right;
                selectedNode->left = head;

                if (head->right != NULL) {
                    head->right->left = selectedNode;
                }
                head->right = selectedNode;
                while (head->left != NULL) {
                    head = head->left;
                }
                return head;
            }
            head = head->right;
        }
        printf("Didn't find any same AM in the list \n");
        free(selectedNode);
        return NULL;
    }
}


void freeMemory(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->right;
        free(temp);
    }
}


int main(){
    Node *head = NULL;
    Node *currNode = NULL;
    char searchName[50];
    char operation[2];
    i32 operationNum;

    while(1) {
        Node *newNode = malloc(sizeof(Node));
        newNode->left = NULL;
        newNode->right = NULL;

        printf("Enter AM: ");
        readInt(&newNode->am);
        if (newNode->am < 0) {
            free(newNode);
            break;
        }

        printf("Enter Name: ");
        cleanInput(newNode->name,50);
        toLower(newNode->name);

        printf("Enter cost:");
        readFloat(&newNode->wallet);

        if (head == NULL) {
            head = newNode;
            currNode = head;
        }
        else if (currNode != NULL) {
            currNode->right = newNode;
            newNode->left = currNode;
            currNode = newNode;
        }


    }

    display(head);
    printf("\n");
    debt(head);

    printf("Enter a name to search: ");
    cleanInput(searchName,50);
    toLower(searchName);

    Node *result = search(head, searchName);

    if (result != NULL) {
        printf("Found \n");
        printf("Name: %s AM: %d cost: %.2f \n", result->name, result->am, result->wallet);
    }
    else {
        printf("Not found \n");
    }


    printf("Do you want to insert a new node (Y:N)");
    cleanInput(operation,2);

    if (tolower(operation[0]) == 'y') {
        printf("Behind Head -> 0 | after head -> 0 > | after AM 0 <");
        readInt(&operationNum);
        Node *toInsert = createNode();

        if (toInsert != NULL) {
            head = insert(head, operationNum, toInsert);
        }
        else {
            printf("Can't insert node \n");
            printf("Memory allocation failed \n");
        }
    }
    else {
        printf("Goodbye \n");
    }


    printf("after \n");

    if (head != NULL) {
        display(head);
    }
    else {
        printf("Not found \n");
    }

    freeMemory(head);
    return 0;
}
