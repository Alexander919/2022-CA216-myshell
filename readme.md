# myshell user manual

## Start and exit

A shell is a program that reads your commands and either carries them out
itself or starts another program to do the work. To start myshell, open a
terminal in the directory that contains the `myshell` executable and type:

    ./myshell

The prompt shows your current working directory, which is the directory
myshell uses to resolve relative paths. For example, `notes.txt` refers to
a file in the current directory, and `/tmp/notes.txt` refers to a file at
that absolute path. In a relative path, `.` means the current directory
and `..` means its parent directory.

Type one command per line and press Enter. The first word is the command
name, and the words after it are arguments. Use spaces or tabs between
words and on both sides of redirection operators. Type `quit` to exit.

## Built-in commands

| Command | What it does |
| --- | --- |
| `cd` | Prints the current working directory. |
| `cd /tmp` | Changes the working directory to `/tmp`. Use `cd ..` to go up one level. If the requested directory does not exist, myshell reports an error. |
| `clr` | Clears the terminal screen. |
| `dir .` | Shows a detailed listing of the current directory, including hidden entries. Replace `.` with another directory path to list its contents. |
| `environ` | Displays the environment variables and their values. |
| `echo Hello there` | Prints the given words followed by a newline. Multiple spaces or tabs may appear as a single space in the output. |
| `help` | Opens this manual in the `more` pager. When prompted, press Space for the next screen, Enter for the next line, or `q` to return to myshell [1]. |
| `pause` | Waits for you to press Enter before continuing. |
| `quit` | Exits myshell. |

For other commands, myshell starts an external program. For example,
`uname -s` asks the `uname` program to print the operating system name.
You can also give a path to an executable, such as `./myprogram` for a
program in the current directory.

## Redirect input and output

Programs have three standard streams. Standard input is where a program
reads data. Standard output carries its regular results. Standard error
carries diagnostic messages. In a typical interactive session these streams
use the terminal. Redirection changes where a command reads or writes [2].

| Operator | Effect |
| --- | --- |
| `< file` | Reads standard input from an existing file. |
| `> file` | Writes standard output to a file. Creates the file if needed and erases any existing contents before the command writes. |
| `>> file` | Adds standard output to the end of a file. Creates the file if needed. |

Try these commands in a directory where you can write files. Choose unused
filenames if you already have files called `practice.txt` or `count.txt`.

    echo One line > practice.txt
    echo Another line >> practice.txt
    wc -l < practice.txt > count.txt
    cat count.txt

The first two commands create a two-line text file. The third reads it
through standard input, counts newline characters with `wc -l`, and
saves the result. The last command displays the saved count of 2 [3].

You can combine input and output redirection for an external program, as
in the `wc` example. Use different files for input and output so that
`>` does not erase your input. The built-ins `dir`, `environ`, `echo`,
and `help` also support output redirection. The operators `>` and `>>`
redirect standard output only, so error messages may still appear on the
terminal.

## View the program environment

The environment is a collection of settings passed to a program when it
starts. Each entry has the form `NAME=value`. Type `environ` to view
these settings. Environment variable names are case-sensitive [4].

- `PATH` contains the directories searched when you run an external
  command by name, such as `wc`.
- `HOME` usually contains the path to your home directory.
- `PWD` contains the current working directory. Myshell updates it when
  you change directories with `cd`.
- `shell` contains the full path to the running myshell executable.
- `parent` is set in the environment of programs launched by myshell.
  Its value is the full path to myshell. Run the external command `env`
  to see the environment passed to it.

## Run a program in the background

A process is a running instance of a program. When you launch an external
program, myshell starts a separate process for it. In the foreground,
myshell waits for that process to finish. For a background run, put `&`
at the end of the line with a space before it. Myshell returns to the
prompt while the process continues [5].

    sleep 5 &

You can type another command immediately while `sleep` waits for five
seconds [6]. Use `&` with external programs. If a background program
prints to the terminal, its output can appear while you are typing the
next command. Use `> file` before the final `&` to send its standard
output to a file.

## Run commands from a file

Save one command per line in a plain-text file. For example, a file called
`commands.txt` could contain:

    echo Current directory
    cd
    dir .

From the terminal, in the directory containing the executable and the file,
run:

    ./myshell commands.txt

Myshell reads the commands in order from the file and exits when it
reaches the end. Relative paths in those commands are resolved from the
current working directory, which can change during the batch if it runs
`cd`.

## References

[1] util-linux project, “more(1),” *Linux Manual Pages*.
https://man7.org/linux/man-pages/man1/more.1.html

[2] GNU Project, “Redirections,” *Bash Reference Manual*, sec. 3.6.
https://www.gnu.org/software/bash/manual/html_node/Redirections.html

[3] GNU Project, “wc: Print newline, word, and byte counts,” *GNU Coreutils Manual*.
https://www.gnu.org/software/coreutils/manual/html_node/wc-invocation.html

[4] Linux man-pages project, “environ(7),” *Linux Manual Pages*.
https://man7.org/linux/man-pages/man7/environ.7.html

[5] Zsh development team, “Simple Commands & Pipelines,” *Zsh Manual*, sec. 6.1.
https://zsh.sourceforge.io/Doc/Release/Shell-Grammar.html

[6] GNU Project, “sleep: Delay for a specified time,” *GNU Coreutils Manual*.
https://www.gnu.org/software/coreutils/manual/html_node/sleep-invocation.html
