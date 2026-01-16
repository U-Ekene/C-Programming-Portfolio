## 📊 CSV Data Queries (C)

This program implements a set of C functions that read a CSV file and extract
specific statistics using file I/O and manual parsing with strtok.

### ✨ Features
- Tokenize CSV rows into fields using a delimiter
- Look up a region’s population based on field filters
- Find the region with the highest value under specific conditions
- Extract a sequence of values into a dynamically allocated float array
- Return a dynamically allocated list of regions matching a threshold
- Compute totals across multiple matching CSV categories

### 🧠 Concepts Used
- File I/O (fopen, fgets, fclose)
- CSV parsing with strtok and strcmp
- Dynamic memory (malloc, free)
- Returning arrays/pointers from functions
- Numeric filtering with atoi / atof

### 📝 Notes
- delimit() uses strtok, which modifies the input line buffer.
- Some functions return dynamically allocated memory; the caller must free it.
