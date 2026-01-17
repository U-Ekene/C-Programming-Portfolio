# Infection Spread Simulation

This program simulates the spread of an infection across a 2D grid based on
population density, proximity to an outbreak source, and seasonal factors.
The simulation computes a single update step that projects new infections and
produces an updated infection map.

✨ Features
- Dynamic creation and management of 2D integer grids
- Recursive flood-style traversal to compute proximity risk
- Seasonal infection multiplier affecting spread intensity
- Calculation of new infections based on remaining susceptible population
- Merging of new infections while respecting population limits
- CSV-style input and output for grid-based data

🧠 Concepts Used
- Dynamic memory allocation for 2D arrays (malloc, calloc, free)
- Recursive grid traversal (up, down, left, right)
- File I/O and CSV parsing
- Pointer-to-pointer (int **) data structures
- Boundary and validity checking
- Modular design with focused helper functions

