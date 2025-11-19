# minishell 2025

> > > > > > > > > > > > > > > >>>>>>>>>>> Rice-cooker team collab > Yo/Iv-an

$$$ 	ABOUT THE SHELL 	$$$ 

**SKIP GOTO USAGE**

>++ PARSING ++<

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

__GRAMMAR: syntax validation__

- read POSIX standard, specifically the section on "Shell Command Language." : details command structure, variable expansion rules, redirection syntax, and how operators like |, &, &&, and || are processed.

\> Example:
\+ redirection token (<, >, >>) must be followed by a STRING token (the file name).
\+ pipe token (|) :
	[lexical analysis] - recognise pipe token
	[syntatic analysis] - rule require that pipe tok must be followed by cmnd. if missing:
	[multiline state] - shell prompts for more input: pipe> (visual cue)
	[combining the cmnd] - two lines of input into single cmnd

- build a State machine : By moving between different states, your parser can correctly 		handle complex sequences of characters.
	Default State: The initial state where the parser is looking for commands, arguments, pipes, and redirections. Spaces and tabs act as delimiters.

	Single-Quote State: Entered when a single quote (') is encountered. In this state, all 	characters are treated literally until the matching closing quote is found. Variable 	expansion is disabled.
	
	Double-Quote State: Entered when a double quote (") is encountered. In this state, characters 	are also treated literally, but with key exceptions. Variable expansion ($) and command 	substitution (``` ` ``) are still enabled. The parser must look for and process these special 	characters even while inside double quotes.
	
	Escape State: Some shells, including Bash, have an escape state entered after a backslash (\)	. This tells the parser to treat the very next character as a literal character, even if it 	would normally have a special meaning (e.g., \$ prints a literal $ instead of expanding a 	variable).

- ID tokens & token linked list
- Syntax analysis : cmnd sequence logic
- Handle Error & Status Message: report outcome of executions
	ex: syntax error near unexpected token 'newline'
	ex: exit status SUCCESS 0 or ERROR != 0 : manage exit status variable 
	ex: empty files and output : but still exit status 0.















