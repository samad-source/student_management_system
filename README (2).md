# COS 201 Student Course Management System (Modular C Project)

This version separates the program into source files by responsibility. It does **not** put every single function in its own file; functions that work together are grouped together, which is a common C project structure.

## Files and responsibilities

- `main.c` — starts the program, reads the menu choice, and directs the user to the right operation.
- `course.c` — adds, displays, and searches for courses; calculates total credit units recursively; displays the menu.
- `input.c` — reusable input helpers and validation.
- `file_manager.c` — saves courses to and loads courses from `courses.txt`.
- `course.h` — defines `struct Course`, constants, and declarations for course functions.
- `input.h` — declarations for the input helper functions.
- `file_manager.h` — declarations for file-saving and loading functions.

A `.c` file contains function **definitions** (the actual instructions). A `.h` header contains shared declarations so other `.c` files know the function names and data structure.

## Compile with GCC

Open the terminal in this folder and compile all four `.c` source files together:

```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c course.c input.c file_manager.c -o student_course_management
```

Windows Command Prompt:

```cmd
student_course_management.exe
```

Linux/macOS:

```bash
./student_course_management
```

Do not compile only `main.c`; the other `.c` files contain functions that `main.c` uses.

## Data file

The program saves records in `courses.txt`, one course per line:

```text
COS201|Programming I|3
MTH201|Mathematics|2
```

The vertical bar `|` separates fields, so don't use it in course codes or titles. Loading replaces the current in-memory list with the records read from the file.

## Features

- Add a course (code, title, positive credit units)
- View all courses
- Search by exact course code
- Calculate total credit units using recursion
- Save and load course records
- Validate menu and unit input, reject duplicate codes, and check file errors
- Store up to 50 courses

## Testing checklist

1. View courses before adding any.
2. Add COS201 / Programming I / 3.
3. Add MTH201 / Mathematics / 2.
4. View all courses and search for COS201.
5. Calculate units; the expected result for those two courses is 5.
6. Save, exit, restart, load, and view courses.
7. Try an unknown course code, invalid units, duplicate code, and an invalid menu option.

## Assessment note

The brief mentions classes, objects, methods, and exceptions. C doesn't provide classes and exception handling in the same way as object-oriented languages. This implementation uses `struct`, functions, input checks, return values, and file-error checks. Confirm with the lecturer that this C interpretation is acceptable.
