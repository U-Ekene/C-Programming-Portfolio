## 🗺️ Map / Grid Utilities (C)

This program implements a collection of utility functions for working with
tile-based 2D maps represented as dynamically allocated char** arrays.
It focuses on grid traversal, boundary checking, and memory-safe manipulation
of two-dimensional data.

The program is structured as reusable map operations with a separate main
file that serves as a test harness for demonstrating functionality.

### ✨ Features
- Dynamic creation of 2D character grids
- Clearcutting regions of a map and predicting affected tiles
- Counting specific tile types across the map and per row
- Flood-risk detection based on adjacency rules
- Detection of single-tile islands
- Submap extraction with bounds checking
- Tessellation (tiling) of a map to larger dimensions

### 🧠 Concepts Used
- Dynamic memory allocation for 2D arrays (malloc / free)
- Pointer-to-pointer (char **) data structures
- Nested loop grid traversal
- Boundary and input validation
- Modular design with reusable utility functions

### 📝 Notes
- Functions that return new maps allocate memory dynamically; the caller is
  responsible for freeing all allocated rows and the map itself.
- The islands function returns pointers to elements in the original map,
  not copies of tiles.
