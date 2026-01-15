## String Toolkit (C)

This program implements a reusable set of string-processing utilities in C using
manual pointer traversal and dynamic memory allocation. Unlike earlier programs
that performed string operations directly within a single control flow, this
implementation emphasizes modular function design and explicit memory ownership.

The toolkit is structured so that each operation is implemented as a standalone
function, allowing the logic to be reused by other programs rather than being tied
to a specific user interaction sequence.

### Features
- Convert strings to uppercase and lowercase
- Count character occurrences
- Count vowels (including Y/y)
- Substring search
- Substring deletion
- Delimiter-based string extraction
- Flow detection across words

### Concepts Used
- Pointer arithmetic with C strings
- Dynamic memory allocation (malloc / free)
- Manual string traversal and comparison
- Modular design across multiple source files
- Custom helper functions

### Notes
- Functions that return strings allocate memory dynamically and must be freed
  by the caller.
- A custom string length function is implemented in helpers.c and reused
  across the program.
