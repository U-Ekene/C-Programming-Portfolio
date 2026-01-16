# Census CSV Query Filter

The program is structured as a batch-style data processing tool that applies reusable filtering logic to census data, driven by a separate query file. Each query is processed independently and produces its own filtered output file.

✨ Features
- Batch processing of multiple queries from a single CSV file
- Region-based filtering with support for compound region names
- Age group and characteristic-based filtering
- Optional numeric conditions using relational operators (<, >, =)
- Automatic generation of output CSV files per query
- Graceful handling of “N/A” filters to bypass specific criteria

🧠 Concepts Used
- File I/O with CSV-style data 
- Dynamic memory allocation and cleanup 
- Tokenization and string parsing
- Conditional filtering logic
- NULL-terminated dynamic string arrays
- Defensive programming and error handling

⚙️ How It Works
Each row in Queries.csv defines:
- An output filename
- Region filters
- Age filters
- Characteristic filters
- An optional numeric condition applied to census values

For each query, the program scans Census.csv, applies all specified filters, and writes matching rows to the corresponding output file.

