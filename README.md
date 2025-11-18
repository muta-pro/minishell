# minishell

> > > > > > > > > > Rice-cooker team collab > Yo/Iv-an

$$$ ABOUT THE SHELL $$$

# ======Redirection Operators
> (Great): Redirects standard output (stdout) to a file. If the file doesn't exist, it's created. If it does exist, its contents are overwritten.

\> Example: echo "hello" > file.txt writes "hello" into file.txt, overwriting any previous content.

< (Less): Redirects standard input (stdin) from a file. The command reads its input from the file instead of the keyboard.

\> Example: grep "pattern" < input.txt searches for "pattern" within input.txt.

>> (Dgreat): Appends standard output to a file. It adds new content to the end of an existing file without overwriting it.

\> Example: echo "world" >> file.txt adds "world" to the end of file.txt.

<< (Dless): This is a heredoc (short for "here document"). It redirects input from the shell itself, using a specified delimiter to mark the end of the input stream. The shell reads all the text between the command and the delimiter as the input for the command.

\> Example: grep hello << EOF will read all subsequent lines as input until it encounters a line containing only EOF.

# ======Variables and Exit Status
Variables ($): In a shell, a variable is a named value. The $ symbol is used for variable expansion, meaning the shell replaces the variable name with its stored value during parsing.

Example: If you set NAME="Alice", the command echo $NAME is parsed as echo "Alice". The parser recognizes VARIABLE tokens and expands them before executing the command.

Exit Status ($?): This special variable holds the exit status of the most recently executed foreground command. By convention, a value of 0 indicates success, while any non-zero value indicates an error.

# ======Double Quotes
("): These quotes allow for partial expansion. The shell expands variables ($VAR) and command substitutions ( ) within double quotes, but it treats most other special characters as literal strings.

\> Example: echo "$USER" will print your username because $USER is expanded. echo "echo "hello"" will execute the inner echo and print "hello".

Single Quotes ('): These quotes are for literal strings. The shell treats everything inside single quotes, including variables and special characters, as a literal string. No expansion occurs.

\> Example: echo '$USER' will print the literal string $USER and not your username.

__GRAMMAR:
- read POSIX standard, specifically the section on "Shell Command Language." : details command structure, variable expansion rules, redirection syntax, and how operators like |, &, &&, and || are processed.

- build a State machine.


