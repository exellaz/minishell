
# Minishell

<p align="center">
	<img src="https://github.com/user-attachments/assets/f66b33b1-7de1-47ab-9d8a-0fc64063ed43"
</p>

Minishell is a custom implementation of a Unix shell written in C. It replicates basic essential features of Bash, handling command execution, redirections, pipes, and environment variables using low-level system calls. The project utilizes GNU Readline for terminal interaction such as input handling and command history. It provides a fundamental yet functional shell experience, serving as a stepping stone for understanding shell internals and process management.

Allowed functions:`rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history,
printf, malloc, free, write, access, open, read,
close, fork, wait, waitpid, wait3, wait4, signal,
sigaction, sigemptyset, sigaddset, kill, exit,
getcwd, chdir, stat, lstat, fstat, unlink, execve,
dup, dup2, pipe, opendir, readdir, closedir,
strerror, perror, isatty, ttyname, ttyslot, ioctl,
getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
tgetnum, tgetstr, tgoto, tputs`

## Status
Finished: 2024-9-25. Grade: 125/100.

## Supported Features

### Command Execution and Prompt
- Display a prompt when waiting for a new command.
- Have a working history.
- Search and launch the right executable (PATH, relative, or absolute path).

### Input Handling and Parsing
- `'` Single quotes - Prevent interpretation of meta-characters.
- `"` Double quotes - Prevent interpretation of meta-characters except `$` expansion.
- `$VAR` Environment variables expansion.
- `$?` Expands to the last exit status.
- `*` Wildcards expansion for current working directory.
- `|` Pipes - The output of each command in the pipeline is connected via a pipe to the input of the next command.
- `&&` and `||` operators - Used to control execution flow between commands or pipelines.
- `(` with `)` - Placing a list of commands between parentheses forces the shell to create a subshell.
- Handles unbalanced quotes by prompting until a closing quote is found.


### Builtins and Signals:
- `echo` with option `-n`
- `cd` with relative or absolute path and `-` for previous working directory
- `pwd` without options
- `export` without options
- `unset` without options
- `env` without options
- `exit` without options
- `ctrl-C`, `ctrl-D` and `ctrl-\` behaves like in Bash

## Process Overview
1. Envionment variables are initialised.
2. Terminal attributes are set.
3. Input is received via readline and saved to history.
4. Lexer tokenises input and stores them in a linked-list.
5. Parser uses operator precedence climbing to build an AST from the token list.
6. Here document interrups happens after the construction of AST.
7. Expansion of environment variables, quotes and wildcards occur before the execution of each respective node.
8. Redirections for each simple command are processed before the execution.
9. Execute the command within the node.
10. Repeat 7 to 9 until all simple command nodes have been executed.
11. Clean up and free unused memory before prompting for next input.

## Dependencies
- GCC/Clang Compiler
- GNU Make
- libncurses library

### Installation for libncurses
For Linux or WSL:
```sh
sudo apt install libncurses5-dev libncursesw5-dev
```

For macOS:
```sh
brew install ncurses
```

## How To Use
To clone and and run this application. From your command line:
```sh
# Clone this repository
$ git clone git@github.com:exellaz/minishell.git

# Go into repository
$ cd minishell

# Build program
$ make

# Run program
$ ./minishell
```

Example session:
```sh
$ ./minishell
minishell> echo Hello World
Hello World
minishell> exit
$
```