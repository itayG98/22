```markdown
# MAMAN 22 – 2025B  
**Course 20465 – Systems Programming in C (ANSI C90)**  
**Open University of Israel**  
**Project Directory: `mycomp/`**

## 📌 Overview  
This project implements a command-line based program that handles operations on complex numbers. It is part of MAMAN 22 for semester 2025B in the Systems Programming course (20465). The program is written in ANSI C90 and intended to run on a Linux system (Ubuntu 16).

## 🧠 Purpose  
The goal is to practice:
- Structuring code using `.c` and `.h` files
- Parsing string input manually
- Performing arithmetic on complex numbers
- Handling user commands and input validation
- Writing portable, standard-compliant ANSI C90 code

## 🧱 File Structure



mycomp/
├── Makefile               # Build script for Ubuntu
├── Ubunto\_Makefile        # Duplicate makefile (legacy)
├── common\_types.h         # Shared type definitions and constants
├── complex.c              # Complex number operations
├── complex.h              # Header for complex.c
├── instructions.pdf       # Official instructions for MAMAN 22
├── mycomp.c               # Main program and command dispatcher
├── mycomp.h               # Header for dispatcher functions
├── string\_utils.c         # Utility functions for parsing and string handling
├── string\_utils.h         # Header for string\_utils.c

```
## 🛠️ Compilation

To compile the program on Ubuntu:
```bash
cd mycomp
make
````

Manual compilation (if needed):

```bash
gcc -ansi -pedantic -Wall -Wextra -o mycomp mycomp.c complex.c string_utils.c
```

## ▶️ Usage

After compiling:

```bash
./mycomp
```

You can enter one command per line. For example:

```
read_comp A, 3.0, -2.5
print_comp A
add_comp A, B
stop
```

## 🧮 Supported Commands

| Command          | Description                                      |
| ---------------- | ------------------------------------------------ |
| `read_comp`      | Assign values to a complex variable              |
| `print_comp`     | Print a complex number                           |
| `add_comp`       | Add two complex numbers                          |
| `sub_comp`       | Subtract one complex number from another         |
| `mult_comp_real` | Multiply a complex number by a real number       |
| `mult_comp_img`  | Multiply a complex number by an imaginary number |
| `mult_comp_comp` | Multiply two complex numbers                     |
| `abs_comp`       | Calculate the absolute value of a complex number |
| `stop`           | Exit the program                                 |

## ❗ Input Rules & Error Handling

The program handles:

* Missing or extra parameters
* Invalid command names
* Misplaced or missing commas
* Input with extra whitespace
* Invalid variable names or number formats

## ✅ Submission Checklist

* [x] All source files (`.c` and `.h`)
* [x] Working Makefile
* [x] README file
* [x] Follows ANSI C90 standard
* [x] Works on Ubuntu 16
* [x] Handles all input validation as described in `instructions.pdf`

## 🧪 Testing Suggestions

Try testing:

* Each valid command
* Invalid commands (e.g., `add_com`, `printcomp`)
* Missing arguments (e.g., `add_comp A`)
* Extra text after commands (e.g., `stop now`)
* Whitespace variations
