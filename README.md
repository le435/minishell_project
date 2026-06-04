# minishell

> *As beautiful as a shell* — 42 Network Project

A simple shell written in C, replicating core behaviors of **bash**. This project is part of the 42 curriculum and aims to deepen understanding of processes, file descriptors, and UNIX system calls.

---

## Features

- Display a prompt while waiting for a new command
- Working command history
- Search and launch the right executable based on 'PATH', or using a relative/absolute path
- Handle ''' (single quotes) — prevent the shell from interpreting metacharacters
- Handle '"' (double quotes) — prevent the shell from interpreting metacharacters except for '$'
- Redirections:
  - '<' — redirect input
  - '>' — redirect output
  - '<<' — heredoc (read input until a delimiter is seen)
  - '>>' — redirect output in append mode
- Pipes '|' — the output of each command is connected to the input of the next
- Environment variables ('$VAR') expansion
- '$?' expansion — exit status of the most recently executed foreground pipeline
- Handle 'ctrl-C', 'ctrl-D', and 'ctrl-\' like bash:
  - 'ctrl-C' — display a new prompt on a new line
  - 'ctrl-D' — exit the shell
  - 'ctrl-\' — do nothing

### Built-in Commands

| Command | Description |
|---|---|
| 'echo' | Print arguments with option '-n' |
| 'cd' | Change directory (relative or absolute path) |
| 'pwd' | Print the current working directory |
| 'export' | Set environment variables |
| 'unset' | Unset environment variables |
| 'env' | Print the environment |
| 'exit' | Exit the shell |

---

## Getting Started

### Prerequisites

- GCC or Clang
- GNU Make
- 'readline' library

On macOS (via Homebrew):
'''bash
brew install readline
'''

On Linux (Debian/Ubuntu):
'''bash
sudo apt-get install libreadline-dev
'''

### Build

'''bash
git clone https://github.com/youruser/minishell.git
cd minishell
make
'''

### Run

'''bash
./minishell
'''

---

## Usage Examples

'''bash
# Basic command
minishell$ ls -la

# Pipes
minishell$ ls | grep ".c" | wc -l

# Redirections
minishell$ echo "hello" > output.txt
minishell$ cat < output.txt >> log.txt

# Heredoc
minishell$ cat << EOF
> line one
> line two
> EOF

# Environment variables
minishell$ export NAME=world
minishell$ echo "Hello $NAME"
Hello world

# Exit status
minishell$ ls nonexistent
minishell$ echo $?
2

# Built-ins
minishell$ cd ..
minishell$ pwd
minishell$ env | grep HOME
'''

## Implementation Notes

- The shell uses 'readline' for prompt display and history management
- Parsing is done in two passes: lexing (tokenization) then parsing (building the AST/command list)
- 'fork' + 'execve' are used to execute external commands
- Pipes are implemented with 'pipe()' and proper fd management
- Signals are handled differently in the parent (interactive) shell vs child processes
- All memory is freed before exiting — no leaks (except those from 'readline' itself)

---

## Resources

- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
- [42 minishell subject](https://cdn.intra.42.fr/pdf/pdf/104374/en.minishell.pdf)
- 'man 3 readline', 'man 2 fork', 'man 2 execve', 'man 2 pipe', 'man 2 dup2'

---

## Authors

Made by **[asmae]** — 42 Network


