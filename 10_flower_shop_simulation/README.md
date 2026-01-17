# Flower Shop Linked List Simulator

This program simulates the operation of a flower shop using a doubly linked list
to manage plants at different stages of growth. The system processes commands from
an input file and updates the internal data structure accordingly.

A single main.c file acts as the driver, while supporting files implement the
linked list and flower logic.

✨ Features
- Dynamic creation and management of flower records
- Doubly linked list sorted by months until maturity
- Planting new flowers with automatic ID assignment
- Issuing growth delays to existing flowers
- Transplanting flowers between matching flowerbeds
- Completing growth cycles and reinserting flowers
- File-driven command processing (Requests.txt)

🧠 Concepts Used
- Dynamic memory allocation (malloc, free)
- Doubly linked list implementation
- Pointer ownership and safe memory cleanup
- String parsing and tokenization
- Modular design using '.h' and '.c' files
- File I/O with structured command handling

📝 Notes
- The linked list maintains flowers in ascending order of months until maturity.
- Flower nodes are detached and reinserted to preserve list ordering after updates.
