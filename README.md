# Pipex

**Pipex project school 42**

This program takes the infile, outfile to redirect the STDIN (<), STDOUT (>) and 2 commands to pipe. To execute the mandatory program, type the command listed below. The arguments will be processed as same as < infile cmd1 | cmd2 > outfile on the shell.

```
./pipex <infile> <cmd1> <cmd2> <outfile>
```

## Usage

### Mandatory part
```bash
./pipex infile "ls -l" "wc -l" outfile
```
Its behavior should be equivalent to: `< infile ls -l | wc -l > outfile`

```bash
./pipex infile "grep a1" "wc -w" outfile
```
Its behavior should be equivalent to: `< infile grep a1 | wc -w > outfile`

## Compilation

```bash
make
```

## Project Structure

```
pipex/
├── includes/
│   └── pipex.h
├── srcs/
│   ├── pipex.c
│   ├── pipex_exec.c
│   └── utils.c
├── libft/
│   ├── ft_strlen.c
│   ├── ft_strdup.c
│   ├── ft_strjoin.c
│   ├── ft_strncmp.c
│   ├── ft_strchr.c
│   ├── ft_split.c
│   ├── ft_putstr_fd.c
│   └── ft_putendl_fd.c
├── Makefile
└── README.md
```

## Features

- Handles file redirection (stdin from infile, stdout to outfile)
- Creates pipes between two commands
- Executes shell commands with their parameters
- Proper error handling and memory management
- Follows 42 school coding standards (Norm)

## External Functions Used

- `open`, `close`, `read`, `write`
- `malloc`, `free`, `perror`, `strerror`
- `access`, `dup`, `dup2`
- `execve`, `exit`, `fork`, `pipe`
- `unlink`, `wait`, `waitpid`

## About

Pipex project school 42 - Implementation of UNIX pipe mechanism in C.
