Doubly Linked List — Student Registry in C
A command-line program written in C that implements a fully functional doubly linked list to manage a registry of people or students. The project demonstrates core data structure concepts including dynamic memory allocation, pointer manipulation, and bidirectional list traversal, making it a solid example of low-level systems programming in C.

What It Does
The program allows a user to interactively build and manage a list of records through the terminal. Each record represents a person and stores three pieces of information: an AM (a unique integer ID), a name, and a cost/wallet value (a floating-point number representing a monetary amount). The user fills in these records one by one, and the program organizes them into a doubly linked list in memory.
Once the list is built, the program offers several operations: displaying all records, computing statistics, searching by name, and inserting new nodes at custom positions within the list.

Features
Building the List
The program starts with an input loop where the user enters records one at a time. Each entry requires an AM, a name, and a cost value. Entering a negative AM signals the end of input and breaks the loop, finalizing the list. Names are automatically converted to lowercase to ensure consistency.
Display
Prints every record in the list sequentially, showing the name, AM, and cost formatted to two decimal places.
Debt & Statistics
After displaying the list, the program computes and prints:

The total sum of all wallet/cost values across every record
The average cost per person

This gives a quick financial overview of all entries in the registry.
Search
The user can search for a record by entering a name. The search is case-insensitive — input is lowercased before comparison, so it matches regardless of how the name was originally entered. If found, the full record is displayed; otherwise, a not-found message is shown.
Insert
The program supports inserting a new node into the list at three different positions, chosen by entering a number
