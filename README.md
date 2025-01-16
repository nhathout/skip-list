# skip-list

This repository builds on my linked-list project to implement a Skip List. The Skip List uses a doubly-linked list structure with multiple levels for improved search efficiency.

Features:
- Constructor: Creates an empty Skip List with a top-level list only and accepts Linked List sentinel values.
- Destructor: Deletes the Skip List and frees memory.
- Search: Finds a value’s location in the bottom-most list or its predecessor if it doesn’t exist.
- Insert: Adds a value to the bottom-most list and promotes it to higher levels based on probability. Returns NULL if the value already exists.
- printData: Outputs the Skip List’s data values (one value per line per level).
- print: Outputs the Skip List’s structure, including node addresses and pointers, for debugging.
- topList: Returns a pointer to the top-most list.
- setRand: Sets a random number generator seed for consistent grading.

Example Output:<br>
Skip List data:<br>
-2147483648 2147483647<br>
-2147483648 2 2147483647<br>
-2147483648 2 5 9 2147483647<br>
-2147483648 2 3 5 6 7 9 2147483647<br>
