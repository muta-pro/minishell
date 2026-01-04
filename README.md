Minishell — my tiny UNIX time machine

This project is my attempt to recreate the feeling of early UNIX development: no GUI, no shortcuts, just a prompt and the rules of the operating system. Minishell isn’t “just parsing strings”. It’s a pipeline of small, strict systems: terminal input, tokenization, syntax building, file descriptors, processes, signals, environment state. It forced me to stop thinking like an app developer and start thinking like the OS.

I built this project incrementally: first getting something that reads commands and runs them, then making it correct and maintainable layer by layer (memory, errors, signals, redirections, pipelines). The final result is a minimal interactive shell that behaves like bash for the features required by the subject.

What minishell does

Shows an interactive prompt using readline

Maintains history (add_history)

Parses commands into an AST

Runs executables using PATH lookup (execve)

Handles builtins: echo -n, cd, pwd, export, unset, env, exit

Redirections: <, >, >>, << (heredoc)

Pipes: |

Environment variables: $VAR and $?

Signals in interactive mode: ctrl-C, ctrl-D, ctrl-\ like bash

Proper exit status rules ($?)

Bonus support can be added on top (&&, ||, parentheses, wildcard *) but the core architecture was built to stay clean even if bonus is added later.

How the shell works (the real structure)

A shell is not one big function. It’s a loop that repeatedly transforms input into behavior:

Input layer
readline() prints the prompt, returns a heap-allocated line without the trailing newline, or NULL on ctrl-D (EOF).
ctrl-C does not “return a special string”: it triggers SIGINT and we must decide how to make readline() stop and redraw cleanly.

Lexing / Tokenizing layer
The line becomes a linked list of tokens: words, quotes, operators (|, >, >>, <, <<), variables ($HOME, $?).
This stage is about reading characters and producing structured pieces.

Parsing layer
Tokens become an AST (Abstract Syntax Tree). This is where “syntax meaning” happens:

a command node has args and a redirection list

a pipeline node connects commands

Parsing is also where syntax errors should be decided (like cat << missing delimiter). Bash-like shells use exit status 258 for syntax errors. In my project I keep that decision inside parsing so execution doesn’t guess.

Expansion layer
Expansion is where $VAR and $? turn into strings.
$? expands from the shell’s exit_status (the status of the most recent foreground pipeline).

Execution layer
This is the most “UNIX” part:

redirections call open() + dup2() to replace stdin/stdout

pipelines use pipe() and fork a process per stage

external commands use execve()

builtins may run in the parent (to modify shell state like cd, export)

Cleanup layer
Tokens, AST, heredoc temp files, and temporary arrays must be freed deterministically.
Shell programs are long-running, so leaks and dangling FDs accumulate fast.

Everything above happens for each command line. Then the loop repeats.

Why signals were harder than they look

Signals are where “it runs” is not enough. It must behave like bash:

ctrl-C at prompt: show a fresh prompt, set $? = 130, do not exit

ctrl-D: exit minishell

ctrl-\ at prompt: do nothing

ctrl-C during a running child: stop the child, return to prompt, $? = 130

ctrl-\ during a running child: quit child, $? = 131

The strict requirement is: only one global variable to communicate signal reception, and it must store only the signal number.
So my handler sets a volatile sig_atomic_t g_got_sigint = SIGINT and the main loop / executor reacts to it.

A key design decision I adopted:

In the child process: restore default signals (so programs behave normally)

In the parent while waiting: ignore signals (so the shell doesn’t fight readline/UI)

In the parent at prompt: custom handler that resets the line and redraws properly

Redirections and why “parent wrappers” exist

Redirections are not “string operations”. They are file descriptor operations:

> open file → dup2(fd, STDOUT_FILENO)

< open file → dup2(fd, STDIN_FILENO)

>> open append

<< heredoc: read lines until delimiter, write to temp file, then treat as < temp

Important practical rule:

In a child process, redirections can permanently replace stdin/out (child will exec/exit).

In the parent process, redirections must be temporary, otherwise the shell prompt itself gets redirected forever.

That’s why parent-level builtins (like cd, export, unset, exit) are wrapped:

save stdin/stdout

apply redirections

run builtin

restore stdin/stdout

This was one of the biggest “shell thinking” moments for me.

Exit status rules I implemented

Normal exit: WEXITSTATUS(status)

Signaled: 128 + signal (SIGINT → 130, SIGQUIT → 131)

Syntax error: 258

Command not found: 127

Exec permission problems: usually 126

$? is always the last foreground pipeline’s exit status.

How to test quickly (the core checks)

Prompt behavior:

ctrl-C on empty prompt → new prompt, echo $? prints 130

ctrl-D → prints exit and quits

ctrl-\ on prompt does nothing

External commands:

ls, pwd, env, echo hello

not_a_cmd → “command not found”, $? = 127

Redirections:

echo hi > out then cat out

cat < out

echo hi >> out (append)

Pipes:

cat file | grep something

cat | cat then ctrl-C → $? = 130

Heredoc:

cat << EOF then type lines then EOF

ctrl-C during heredoc → returns to prompt, $? = 130

Builtins affecting shell:

cd /tmp then pwd

export A=1 then echo $A

unset A then echo $A

exit 42

Code organization (how I kept it maintainable)

I tried to keep the project readable as “a pipeline of systems”:

input/ prompt loop + readline behavior

lexer/ token scanning, quote logic, operators

parser/ AST construction, syntax validation

expand/ $VAR and $?

exec/ pipes, redirections, builtins, execve

env/ env list utilities, export/unset helpers

signals/ interactive vs exec vs child signal modes

free/ centralized cleanup

The rule I followed: each layer owns its responsibilities and returns a clear result to the next layer. When things were messy, I fixed structure first, then behavior.

What I learned (the “why” of this project)

Minishell taught me that a shell is basically a controlled conversation between:

the terminal driver

the process scheduler

file descriptors

signals

memory ownership

It also taught me how much of “bash behavior” is actually a set of small conventions:

exit codes

exactly when expansion happens

exactly who gets signals (parent vs child)

exactly how parsing errors are reported

I didn’t just code features; I had to make them consistent with UNIX rules.

Build & run
make
./minishell

>> Resources & References
AI: for deep-level reasearch and shell understatnig.

Bash Reference Manual: For behavior replication.

The Linux Programming Interface: For deep dives into fork(), execve(), and file descriptors.

GNU Readline Library: For input management.

Built by muta-pro & jokoN3 as part of the 42 Curriculum.

Rice-cooker team collab
