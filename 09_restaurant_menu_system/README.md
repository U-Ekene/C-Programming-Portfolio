# Restaurant Menu System

This program models a simple restaurant menu system in C using modular design.
It demonstrates how structured data, dynamic memory allocation, and controlled
interfaces can be used to manage related entities such as restaurants and their
menu items.

A single main file serves as a test harness to showcase the system’s behavior
under different scenarios.

✨ Features
- Creation and management of multiple restaurants
- Dynamic creation and removal of menu items
- Tag-based classification of menu items (e.g., chicken, salad, fries)
- Festival-based filtering of menu items by tag
- Conditional discount application per restaurant
- Safe memory management with explicit ownership and cleanup

🧠 Concepts Used
- Struct-based data modeling in C
- Header and source file separation
- Dynamic memory allocation (malloc, strdup, free)
- Pointer ownership and lifecycle management
- Fixed-size arrays with bounds checking
- Modular API design for reusable components

📁 File Overview
- main.c – Demonstrates usage of the restaurant and menu modules
- menu.h / menu.c – Defines and manages individual menu items
- restaurant.h / restaurant.c – Defines restaurants and operations on menus
- Makefile – Builds the program from multiple source files

📝 Notes
- Restaurants own their menu items and are responsible for freeing them.
- Menu items enforce a maximum number of tags to maintain internal consistency.
- This program is designed as a demonstration, not an interactive application.

