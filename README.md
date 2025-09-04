# Pipex

## Table of Contents
- [Introduction](#introduction)
- [Installation](#installation)
- [Usage](#usage)
- [Features](#features)
- [Skills Learned](#skills-learned)
- [Requirements](#requirements)
- [Project Structure](#project-structure)
- [How It Works](#how-it-works)
- [Examples](#examples)
- [Error Handling](#error-handling)

## Introduction

Pipex is a 42 School project that replicates the behavior of Unix pipelines (`|`) and input/output redirections using C. The program executes two commands sequentially, passing the output of the first command as input to the second command, while managing file input and output redirection.

This project demonstrates understanding of:
- Process creation and management
- Inter-process communication using pipes
- File descriptor manipulation
- System calls for process control

## Installation

To install and compile the Pipex project:

1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd pipex
   ```

2. Compile the project:
   ```bash
   make
   ```

3. Clean object files (optional):
   ```bash
   make clean
   ```

4. Clean everything and recompile:
   ```bash
   make re
   ```

## Usage

The program must be executed with exactly 4 arguments:

```bash
./pipex file1 cmd1 cmd2 file2
```

**Arguments:**
- `file1`: Input file name
- `cmd1`: First shell command with its parameters
- `cmd2`: Second shell command with its parameters  
- `file2`: Output file name

**Behavior:**
The program behaves exactly like the shell command:
```bash
< file1 cmd1 | cmd2 > file2
```

## Features

- **Process Management**: Creates and manages child processes using `fork()`
- **Inter-Process Communication**: Uses `pipe()` to enable communication between processes
- **File Descriptor Manipulation**: Redirects input and output using `dup2()`
- **Command Execution**: Executes shell commands with `execve()`
- **Path Resolution**: Automatically finds command paths in the system PATH
- **Error Handling**: Comprehensive error handling with proper cleanup
- **Memory Management**: Proper allocation and deallocation of memory

## Skills Learned

- **Process Management**: Creating and managing processes using `fork()`
- **Inter-Process Communication**: Using `pipe()` to enable communication between processes
- **File Descriptor Manipulation**: Redirecting input and output using `dup2()`
- **System Calls**: Executing commands with `execve()`
- **Memory Management**: Proper memory allocation and cleanup
- **Error Handling**: Robust error handling and resource cleanup
- **Path Resolution**: Finding executable paths in the system environment

## Requirements

- A Unix-like operating system (macOS or Linux)
- GCC or Clang compiler
- Make utility
- 42 School Norminette compliance

## Project Structure

```
pipex/
├── Makefile          # Build configuration
├── pipex.h           # Header file with declarations
├── pipex.c           # Main program file
├── utils.c           # Utility functions
├── process.c         # Process management functions
├── path.c            # Path resolution functions
├── libft.c           # Custom string functions
└── README.md         # This file
```

## How It Works

1. **Argument Validation**: Checks that exactly 4 arguments are provided
2. **File Operations**: Opens input and output files
3. **Command Parsing**: Splits commands and arguments into arrays
4. **Pipe Creation**: Creates a pipe for inter-process communication
5. **First Child Process**: 
   - Redirects stdin to input file
   - Redirects stdout to pipe write end
   - Executes first command
6. **Second Child Process**:
   - Redirects stdin to pipe read end
   - Redirects stdout to output file
   - Executes second command
7. **Parent Process**: Waits for both child processes to complete
8. **Cleanup**: Closes file descriptors and frees allocated memory

## Examples

### Basic Usage
```bash
# Count lines in a file
./pipex input.txt "cat" "wc -l" output.txt
# Equivalent to: < input.txt cat | wc -l > output.txt

# Search and count
./pipex input.txt "grep 'pattern'" "wc -w" output.txt
# Equivalent to: < input.txt grep 'pattern' | wc -w > output.txt

# List files and count
./pipex . "ls -la" "wc -l" file_count.txt
# Equivalent to: < . ls -la | wc -l > file_count.txt
```

### Advanced Examples
```bash
# Process text file
./pipex data.txt "sort" "uniq -c" sorted_unique.txt

# Filter and format
./pipex log.txt "grep ERROR" "awk '{print $2}'" errors.txt

# Compress and count
./pipex large_file.txt "gzip -c" "wc -c" compressed_size.txt
```

## Error Handling

The program handles various error conditions:

- **Invalid Arguments**: Wrong number of arguments
- **File Errors**: Cannot open input/output files
- **Command Not Found**: Commands not found in PATH
- **System Call Failures**: Pipe, fork, or execve failures
- **Memory Allocation**: Malloc failures
- **Process Management**: Child process failures

All errors are handled gracefully with appropriate error messages and proper cleanup of resources.

## Technical Details

### System Calls Used
- `pipe()`: Creates a pipe for inter-process communication
- `fork()`: Creates child processes
- `dup2()`: Duplicates file descriptors for redirection
- `execve()`: Executes commands
- `open()`/`close()`: File operations
- `waitpid()`: Waits for child processes
- `access()`: Checks file permissions

### Memory Management
- All dynamically allocated memory is properly freed
- No memory leaks
- Proper cleanup on error conditions

### Norminette Compliance
- Functions under 25 lines
- Lines under 80 characters
- Proper indentation (4 spaces)
- Standard header format
- No forbidden functions

## Testing

To test the program:

1. Create test files:
   ```bash
   echo "line1\nline2\nline3" > test_input.txt
   ```

2. Run pipex:
   ```bash
   ./pipex test_input.txt "cat" "wc -l" test_output.txt
   ```

3. Verify output:
   ```bash
   cat test_output.txt
   # Should show: 3
   ```

4. Compare with shell command:
   ```bash
   < test_input.txt cat | wc -l > shell_output.txt
   diff test_output.txt shell_output.txt
   # Should show no differences
   ```

## Contributing

This is a 42 School project. Please follow the school's guidelines and norms when contributing.

## License

This project is part of the 42 School curriculum.
