# Doubly Linked List in C

A menu-driven C program implementing a doubly linked list with full CRUD operations. Each node stores a person's name, a unique student ID (AM), and a wallet balance.

---

## Data Structure

```c
typedef struct Node {
    char  name[50];
    i32   am;       // unique student ID
    f32   wallet;   // balance / cost
    struct Node *left;
    struct Node *right;
} Node;
```

Each node holds a pointer to both its predecessor (`left`) and successor (`right`), allowing traversal in both directions.

---

## Features

- **Build a list** interactively at startup — enter nodes one by one, stop with `-1`
- **Display** the full list with name, AM, and cost per node
- **Debt summary** — total sum and average wallet across all nodes
- **Search** by name (case-insensitive)
- **Insert** a new node at a flexible position
- **Delete** a node at a flexible position
- **Duplicate AM guard** — rejects any AM already present in the list

---

## Insert Positions

| Value | Behaviour |
|-------|-----------|
| `0` | Insert before the head |
| `N > 0` | Insert after position N (falls back to tail if N exceeds length) |
| `-1` | Append to the tail |
| `< -1` | Search by AM and insert after the matching node |

## Delete Positions

| Value | Behaviour |
|-------|-----------|
| `0` | Delete the head |
| `N > 0` | Delete node at position N |
| `-1` | Delete the tail |
| `< -1` | Search by AM and delete the matching node |

---

## Functions

| Function | Description |
|----------|-------------|
| `createNode` | Allocates and populates a new node from user input |
| `insert` | Inserts a pre-created node at the specified position |
| `deleteNode` | Removes and frees a node at the specified position |
| `search` | Returns a pointer to the first node matching a given name |
| `display` | Prints all nodes left-to-right |
| `debt` | Prints the total and average wallet balance |
| `listLength` | Returns the number of nodes in the list |
| `isAmTaken` | Returns `1` if the given AM already exists in the list |
| `freeMemory` | Traverses and frees the entire list |
| `cleanInput` | Safe `fgets` wrapper that strips the trailing newline |
| `readInt` | Validated integer input using `strtol` |
| `readFloat` | Validated float input using `strtof` |
| `toLowerString` | Converts a string to lowercase in-place |

---

## Type Aliases

Standard fixed-width types are aliased for brevity:

```c
typedef int32_t  i32;
typedef int16_t  i16;
typedef uint16_t u16;
typedef float    f32;
// etc.
```

---

## Build & Run

```bash
gcc -o linked_list main.c
./linked_list
```

No external dependencies — pure C99 standard library.

---

## Example Session

```
Enter AM: (-1 to stop): 101
Enter Name: Alice
Enter cost: 42.50

Enter AM: (-1 to stop): 102
Enter Name: Bob
Enter cost: 18.00

Enter AM: (-1 to stop): -1

Your double linked list
Name: alice AM: 101 cost: 42.50
Name: bob   AM: 102 cost: 18.00

The sum is: 60.50
Average: 30.25
```
