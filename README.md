# readline-c

*This project has been created as part of the 42 curriculum*

## Description

**readline-c or get_next_line** is the second project in the 42 curriculum that focuses on file manipulation and static variables in C. The goal is to write a function that reads a line from a file descriptor, allowing you to read text files line by line efficiently.

This project teaches you about:
- File descriptors and file I/O operations
- Static variables and their persistence between function calls
- Buffer management and memory allocation
- Reading from both files and standard input

The function must handle multiple file descriptors simultaneously and work with various buffer sizes, making it a versatile tool for future projects.

---

## Project Structure

```
get_next_line/
├── get_next_line.h              # Mandatory: Header file
├── get_next_line.c              # Mandatory: Main function
├── get_next_line_utils.c        # Mandatory: Helper functions
├── get_next_line_bonus.h        # Bonus: Header file
├── get_next_line_bonus.c        # Bonus: Main function (multiple FDs)
├── get_next_line_utils_bonus.c  # Bonus: Helper functions
├── main.c                       # Test program
├── Makefile                     # Compilation automation
└── README.md                    # This file
```

---

## Function Prototype

```c
char *get_next_line(int fd);
```

### Parameters
- `fd` - The file descriptor to read from

### Return Value
- **Success**: The line that was read (including the terminating `\n` if present)
- **End of file**: The last line without `\n` (if the file doesn't end with a newline)
- **Error or nothing to read**: `NULL`

---

## Instructions

### Quick Start

To compile and test the mandatory part:

```bash
make
```

To compile and test the bonus part:

```bash
make bonus
```

To run tests:

```bash
make run        # Run mandatory tests
make run_bonus  # Run bonus tests
```

### Available Make Rules

- `make` or `make all` - Compiles mandatory version with tests
- `make bonus` - Compiles bonus version with tests
- `make run` - Compiles and runs mandatory tests
- `make run_bonus` - Compiles and runs bonus tests
- `make clean` - Removes object files
- `make fclean` - Removes object files and executables
- `make re` - Rebuilds everything from scratch

### Manual Compilation

#### Mandatory Part
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c -o gnl_test
./gnl_test
```

#### Bonus Part
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line_bonus.c get_next_line_utils_bonus.c -o gnl_bonus
./gnl_bonus
```

You can change `BUFFER_SIZE` to any value (1, 42, 9999, 10000000, etc.)

### Usage Example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

---

## Mandatory vs Bonus

### Mandatory Part
The mandatory implementation handles:
- Reading one line at a time from a single file descriptor
- Managing static variables for a single FD
- All basic requirements

### Bonus Part ⭐
The bonus implementation adds:
- **Multiple file descriptor management** - Read from multiple files simultaneously
- Uses only **one static variable** for all file descriptors
- More efficient memory management
- Advanced static variable techniques

**Example of bonus usage:**
```c
int fd1 = open("file1.txt", O_RDONLY);
int fd2 = open("file2.txt", O_RDONLY);

char *line1 = get_next_line(fd1);  // Read from file1
char *line2 = get_next_line(fd2);  // Read from file2
char *line3 = get_next_line(fd1);  // Continue reading file1
```

---

## Key Features

### ✅ Required Functionality
- Read one line at a time from a file descriptor
- Handle multiple consecutive calls to read entire files
- Include the terminating `\n` character (when present)
- Work with both files and standard input (stdin)
- **Bonus**: Handle multiple file descriptors simultaneously with one static variable
- Support variable buffer sizes (compile-time definition)

### ⚙️ Technical Requirements
- Must use `read()`, `malloc()`, and `free()`
- Must handle edge cases (empty files, no newline at EOF, etc.)
- No memory leaks

---

## Implementation Details

### Buffer Size
The buffer size is defined at compilation time using the `-D BUFFER_SIZE=n` flag. Your implementation should work correctly with any buffer size, including extreme values like:
- `BUFFER_SIZE=1` (read one byte at a time)
- `BUFFER_SIZE=42` (standard size)
- `BUFFER_SIZE=9999` (large buffer)
- `BUFFER_SIZE=10000000` (very large buffer)

### Static Variables

#### Mandatory Version
Uses static variables to store leftover data between function calls for a single file descriptor.

#### Bonus Version
Uses **only ONE static variable** to manage multiple file descriptors simultaneously. This requires:
- Dynamic allocation for tracking multiple FDs
- Efficient data structure management
- Proper cleanup when FDs are closed

### Memory Management
- Each returned line must be dynamically allocated
- The caller is responsible for freeing the returned line
- Internal buffers must be properly managed to prevent leaks
- All allocated memory must be freed when reaching EOF or on error

---

## Testing Scenarios

Your implementation should handle:

1. **Normal files** - Files with regular lines ending in `\n`
2. **No trailing newline** - Last line without `\n`
3. **Empty lines** - Lines containing only `\n`
4. **Empty files** - Files with no content
5. **Large lines** - Lines longer than `BUFFER_SIZE`
6. **Small buffer** - `BUFFER_SIZE=1` with large files
7. **Standard input** - Reading from stdin (fd=0)
8. **Multiple FDs** (Bonus) - Reading from multiple files simultaneously
9. **Invalid FD** - Handling negative or invalid file descriptors

---

## Testing with Different Buffer Sizes

The Makefile allows easy testing with different buffer sizes:

```bash
# Test with BUFFER_SIZE=1
make BUFFER_SIZE=1 run

# Test with BUFFER_SIZE=9999
make BUFFER_SIZE=9999 run_bonus

# Test with custom size
make BUFFER_SIZE=10000000 bonus
```

---

## Resources

### Official Documentation
- [read() man page](https://man7.org/linux/man-pages/man2/read.2.html)
- [open() man page](https://man7.org/linux/man-pages/man2/open.2.html)
- [File descriptors explained](https://en.wikipedia.org/wiki/File_descriptor)

### Understanding Static Variables
- [Static Variables in C](https://www.geeksforgeeks.org/static-variables-in-c/)
- [Storage Classes in C](https://www.tutorialspoint.com/cprogramming/c_storage_classes.htm)

### Articles & Tutorials
- [File I/O in C](https://www.cs.utah.edu/~germain/PPS/Topics/C_Language/file_IO.html)
- [Buffer Management](https://www.codingunit.com/c-tutorial-file-io-using-text-files)
- [Working with File Descriptors](https://www.bottomupcs.com/file_descriptors.xhtml)

### Video Tutorials
- [Oceano - get_next_line explained](https://www.youtube.com/watch?v=8E9siq7apUU)
- [CodeVault - File I/O](https://www.youtube.com/watch?v=R_FQUGHhNJ8)

---

## Compilation Flags

All code is compiled with:
- `-Wall` - Enable all warnings
- `-Wextra` - Enable extra warnings
- `-Werror` - Treat warnings as errors
- `-D BUFFER_SIZE=n` - Define buffer size at compile time

---