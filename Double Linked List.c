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


Node *createNode(Node const *head);
void toLowerString(char *str);
void readInt(i32 *value);
void readFloat(f32 *value);
void cleanInput(char *str, int size);
i32 listLength(const Node *head);
void display(Node *head);
void debt(Node const *head);
Node *search(Node *head, char lName[50]);
Node *insert(Node *head, i32 index, Node *selectedNode);
Node *deleteNode(Node *head,i32 index);
i32 isAmTaken(const Node *head, i32 am);
void freeMemory(Node *head);


Node *createNode(Node const *head) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed \n");
        return NULL;
    }
    newNode->left = NULL;
    newNode->right = NULL;

    printf("Enter AM: ");
    readInt(&newNode->am);

    while (isAmTaken(head, newNode->am)) {
        printf("This AM is already in use please enter a different one: ");
        readInt(&newNode->am);

        if (newNode->am < 0) {
            free(newNode);
            return NULL;
        }
    }

    do {
        printf("Enter Name: ");
        cleanInput(newNode->name,50);
        if (newNode->name[0] == '\0') printf("Name can't be empty. \n");

    }while (newNode->name [0] == '\0');


    do {
        printf("Enter cost: ");
        readFloat(&newNode->wallet);
        if (newNode->wallet < 0.0) printf("Wallet can't be negative. \n");

    }while (newNode->wallet < 0);

    return newNode;
}


void toLowerString(char *str) {
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

i32 listLength(const Node *head) {
    i32 count = 0;
    while (head != NULL) {
        count++;
        head = head->right;
    }
    return count;
}



void display(Node *head) {

    if (head == NULL) {
        printf("list is empty \n");
        return;
    }

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

    if (index > 0) {
        const i32 len = listLength(head);
        if (index > len) {
            printf("Warning: position %d exceeds list length %d. inserting at end. \n", index, len);
        }
    }

    if (index == 0) {
        head->left = selectedNode;
        selectedNode->left = NULL;
        selectedNode->right = head;
        return selectedNode;
    }

    if (index == -1) {
        Node *current = head;
        while (current->right != NULL) {
            current = current->right;
        }
        current->right = selectedNode;
        selectedNode->left = current;
        selectedNode->right = NULL;
        return head;
    }

    if (index > 0) {
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

Node *deleteNode(Node *head, const i32 index) {
    Node *current = head;
    Node *temp = NULL;
    i32 num;

    if (head == NULL) {
        return NULL;
    }

    if (index > 0) {
        const i32 len = listLength(head);
        if (index > len) {
            printf("Position %d exceeds list length %d. no node deleted. \n", index, len);
            return head;
        }
    }

    if (index == 0) {
        temp = current;
        head = current->right;
        if (head != NULL) {
            head->left = NULL;
        }
        free(temp);
        return head;
    }

    if (index == -1) {
        while (current->right != NULL) {
            current = current->right;
        }
        if (current->left != NULL) {
            current->left->right = NULL;
        } else {
            head = NULL;
        }
        free(current);
    }
    else if (index > 0) {

        if (index == 1) {
            temp = head;
            head = current->right;
            if (head != NULL) {
                head->left = NULL;
            }
            free(temp);
            return head;
        }

        u16 count = 1;
        while (current->right != NULL && count < index - 1) {
            current = current->right;
            count++;
        }
        temp = current->right;
        current->right = temp->right;
        if (temp->right != NULL) {
            temp->right->left = current;
        }
        free(temp);

        return head;

    }
    else {
        printf("Enter AM of the node you want to delete: ");
        readInt(&num);

        while (current->am != num && current->right != NULL) {
            current = current->right;
        }
        if (current->am != num) {
            printf("Node with am = %d not found \n", num);
            return head;
        }
        if (current->left == NULL) {
            head = current->right;
        } else {
            current->left->right = current->right;
        }
        if (current->right != NULL) {
            current->right->left = current->left;
        }
        free(current);
    }

    return head;
}

i32 isAmTaken(const Node *head, const i32 am) {
    while (head != NULL) {
        if (head->am == am) {
            return 1;
        }
        head = head->right;
    }
    return 0;
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

        if (newNode == NULL) {
            printf("Memory allocation failed \n");
            break;
        }

        newNode->left = NULL;
        newNode->right = NULL;

        printf("Enter AM: (-1 to stop): ");
        readInt(&newNode->am);


        if (newNode->am < 0) {
            free(newNode);
            break;
        }

        while (isAmTaken(head, newNode->am)) {

            printf("This AM is already in use please enter a different one: ");
            readInt(&newNode->am);

            if (newNode->am < 0) {
                free(newNode);
                goto done_building;
            }
        }


        do {
            printf("Enter Name: ");
            cleanInput(newNode->name,50);
            if (newNode->name[0] == '\0') printf("Name can't be empty. \n");

        }while (newNode->name[0] == '\0');

        toLowerString(newNode->name);

        do {
            printf("Enter cost:");
            readFloat(&newNode->wallet);
            if (newNode->wallet < 0.0) printf("Wallet can't be negative. \n");

        }while (newNode->wallet < 0);


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

    done_building: //goto

    if (head == NULL) {
        free(head);
        printf("your list is empty \n");
        goto done;
    }

    printf("Your double linked list \n");
    display(head);
    printf("\n");
    debt(head);


    printf("Enter a name to search: ");
    cleanInput(searchName,50);
    toLowerString(searchName);

    Node *result = search(head, searchName);

    if (result != NULL) {
        printf("Found \n");
        printf("Name: %s AM: %d cost: %.2f \n", result->name, result->am, result->wallet);
    }
    else {
        printf("Not found \n");
    }


    while (1) {

        printf("Do you want to insert a new node (Y:N)");
        cleanInput(operation,2);

        if (tolower(operation[0]) != 'y') {
            printf("Goodbye \n");
            break;
        }

        printf("Insert at position (0 = before head, N = after position, -1 = end, < -1 = by AM): <");
        readInt(&operationNum);
        Node *toInsert = createNode(head);

        if (toInsert != NULL) {
            head = insert(head, operationNum, toInsert);
        }
        else {
            printf("Can't insert node \n");
            printf("Memory allocation failed \n");
        }

    }

    printf("After \n");

    if (head != NULL) {
        display(head);
    }
    else {
        printf("Error finding list! \n");
    }

    while (1) {

        printf("Do you want to delete a node (Y:N): ");
        cleanInput(operation,2);

        if (tolower(operation[0]) != 'y') {
            break;
        }

        if (head == NULL) {
            printf("List is empty \n");
            break;
        }

        printf("Delete at position (0 = head, -1 = tail, < 0 = by AM): ");
        readInt(&operationNum);
        head = deleteNode(head, operationNum);
    }


    printf("After deletion \n");
    display(head);

    done: //goto
    freeMemory(head);

    return 0;
}