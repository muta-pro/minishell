Minishell - A Robust Bash Implementation
Minishell is a fully functional shell implementation written in C, built to understand the intricacies of process creation, file descriptor manipulation, and signal handling in a UNIX environment.

This project goes beyond simple command execution, featuring a recursive Abstract Syntax Tree (AST) parser and a dedicated pre-processing phase for complex redirections like Heredocs.

>> Key Features
Pipeline Management: Handles infinite pipes (|) with correct fd duplication.

Robust Signal Handling: Mimics Bash behavior for Ctrl+C, Ctrl+D, and Ctrl+\ across interactive, blocking, and heredoc states.

Advanced Redirections: Supports input (<), output (>), append (>>), and Heredocs (<<).

AST Architecture: Uses a tree-based structure rather than a linear list, enabling complex logic handling.

Environment Management: Custom implementation of environment variable expansion and storage.

>> Architecture Deep Dive
The core strength of this shell lies in its Recursive AST Traversal and Multi-State Signal Handling.

1. The Heredoc "Pre-Processing" Phase
Unlike standard commands, Heredocs (<<) require user input before the execution phase. To solve this, Minishell implements a dedicated tree traversal pass:

Detection: The shell scans the AST for HEREDOC nodes.

Interaction: It pauses execution to capture user input, writing to unique temporary files (/tmp/.minishell_hd_X).

AST Transformation: The AST node type is dynamically swapped from HEREDOC to REDIR_IN. The delimiter is replaced with the path to the temp file.

Execution: The Executor runs blindly, treating the complex heredoc as a simple file input.

2. Signal Synchronization
Handling signals in C is tricky when combined with readline. Minishell manages three distinct signal states to prevent "zombie" inputs and visual glitches:

Interactive Mode: Uses sigaction to reprint the prompt on a new line (handling Ctrl+C).

Heredoc Mode: Implements a specialized handler using ioctl(TIOCSTI) to force readline to unblock immediately upon interrupt, preventing the shell from hanging.

Child Processes: Properly ignores signals in the parent while waiting for blocking commands (like cat or grep) to finish.

3. Abstract Syntax Tree (AST)
Commands are parsed into a binary tree structure, allowing for logical separation of execution steps.

Code snippet

graph TD;
    PIPE-->|Left| CMD_1[cat];
    CMD_1-->|Redir| HD[<< EOF];
    PIPE-->|Right| CMD_2[grep];
    CMD_2-->|Arg| ARG[pattern];
>> Technical Challenges & Studies
The "Zombie File" Problem
Challenge: If a user interrupts a heredoc (Ctrl+C), a temporary file remains on the disk. Solution: A "cleanup" routine traverses the AST post-execution. Additionally, an emergency unlink is triggered immediately inside the signal handler to prevent garbage accumulation during interrupted sessions.

Readline vs. Signals
Challenge: The readline library blocks the main thread. When a signal handler runs, it doesn't automatically unblock readline, causing the shell to ignore the first Ctrl+C or print double prompts. Solution: We utilized ioctl to simulate a newline injection, forcing readline to return control to the main loop immediately for a clean state reset.

💻 Installation & Usage
Build
Bash

git clone https://github.com/yourusername/minishell.git
cd minishell
make
Run
Bash

./minishell
Examples
Multi-Heredoc Piping:

Bash

minishell$ cat << A | grep << B
> hello
> A
> world
> B
Signal Test:

Bash

minishell$ cat
^C
minishell$ 
>> Resources & References
Bash Reference Manual: For behavior replication.

The Linux Programming Interface: For deep dives into fork(), execve(), and file descriptors.

GNU Readline Library: For input management.

Built by muta-pro & joko as part of the 42 Curriculum.

Rice-cooker team collab
