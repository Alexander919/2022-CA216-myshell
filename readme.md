
## Acknowledgements

Many thanks to Donal Fitzpatrick who provided the basis for this assignment. He developed the initial version of this assignment from Operating Systems: Internals and Design Principles by William Stallings. The assignment and description has been modified by Dr. Healy accordingly. The code examples and supporting exercises have all necessary attributions contained therein. All errors and omissions introduced are mine. No unauthorised distribution / reproduction is permitted.

## Academic Integrity

Before reading this specification, you are requested to familiarise yourself with the DCU academic Integrity Policy.

There is a ***0-tolerance*** approach to plagiarism in this module. If you are found to have breached the DCU Academic Integrity Policy you will simply be given 0. It does not matter how small or minor the breach, you will simply be given 0 for this assessment.

It is not acceptable to take other people's work and attempt to pass it off as your own.

## Introduction

Up to this week in CA216 you have been learning about processes by doing small-scale exercises. You have used *Python* and *C*. This project is designed to meet the following objectives:

1. To introduce you to working, in a larger setting, with processes.
2. To introduce you to building a larger program than you might have written before.
3. To strengthen your knowledge of organising and structuring your programs to ensure they are extensible and modular.

## Specification

The Shell or Command Line Interpreter is the fundamental User interface to an Operating System. For this assignment you will write a simple shell - myshell - that has the following functionality:

#### Supported Commands (Internal Commands)

The shell must support the following internal commands:

- **cd** \- change the current default directory . If the argument is not present, report the current directory. If the directory does not exist an appropriate error should be reported. This command should also change the PWD environment variable.
- **clr** - clear the screen.
- **dir** \- list the contents of directory e.g. ls -al \<directory\>
- **environ** - list all the environment strings
- **echo** \- echo on the display followed by a new line (multiple spaces/tabs may be reduced to a single space)
- **help** - display the user manual using the more filter.
- **pause** - pause operation of the shell until 'Enter' is pressed
- **quit** - quit the shell
The shell environment should contain shell= /myshell where /myshell is the full path for the shell executable (not a hardwired path back to your directory, but the one from which it was executed)

### Other Commands

All other command line input is interpreted as program invocation which should be done by the shell ***forking** and **execing*** the programs as its own child processes. The programs should be executed with an environment that contains the entry: parent= /myshell where /myshell is as described in the last bullet point above.

### Batch Mode

The shell must be able to take its command line input from a file. i.e. if the shell is invoked with a command line argument:

```
./myshell batchfile
```

then `batchfile` is assumed to contain a set of command lines for the shell to process. When the end-of -file is reached, the shell should exit. Obviously, if the shell is invoked without a command line argument it solicits input from the user via a prompt on the display.

### I/O Redirection

The shell must support i/o-redirection on either or both `stdin` and/or `stdout`. i.e. the command line:

```
programname arg1 arg2 < inputfile > outputfile
```

will execute the program *programname* with arguments arg1 and arg2, the stdin FILE stream replaced by inputfile and the stdout FILE stream replaced by outputfile.

`stdout` redirection should also be possible for the internal commands: `dir`, `environ`, `echo`, and `help`.

With output redirection, if the redirection character is `>` then the outputfile is created if it does not exist and truncated if it does. If the redirection token is `>>` then outputfile is created if it does not exist and appended to if it does.

### Background Execution

The shell must support background execution of programs. **This does not need to be implemented for internal commands but it should be implemented for "Other Commands".** An ampersand, or `&` character, at the end of the command line indicates that the shell should return to the command line prompt immediately after launching that program whilst it continues to run in the background.

### Miscellaneous

The command line prompt must contain the pathname of the current directory. Note: you can assume that all command line arguments including the redirection symbols, `<`, `>` and `>>` and the background execution symbol, `&` will be delimited from other command line arguments by white space - one or more spaces and/or tabs (see the command line above). We should just have to type `make` to build your shell.

## Project Requirements

### System Design

Design a simple command line shell that satisfies the above criteria and implement it such **t** **hat it runs on Linux on the lab computers.** **I am aware that some of you program in Windows, *however* your programs will, under no circumstances, be compiled on Windows.** If you only have *Windows* at your convenient disposal, then the *WSL* or *Cygwin* might be the way to go. Alternatively you could set up a Linux Virtual machine, or develop using the [School of Computing Termcast](https://termcast.computing.dcu.ie/). Mileage may vary with these alternative options, so it is important you test your program successfully compiles and runs on the lab computers (under Linux).

The source code **MUST** be extensively commented and appropriately structured i.e. to an extend that would allow your peers to understand and easily maintain the code. Properly commented and laid out code is much easier to interpret and it is in your interests to ensure that the person marking your project is able to understand your code without having to perform mental gymnastics. You should also use multiple files to manage your code. **Submissions which only contain one *C program file* will lose marks.  

### A user Manual

You must write a simple manual describing how to use the shell. The manual should contain enough detail for a beginner to UNIX to use it. For example, you should explain the concepts of i/o redirection, the program environment, and background program execution. The manual MUST be named readme.md and must be a simple text document capable of being read by a standard Text Editor. Your manual must also contain four (at a minimum; more is better) references to *peer-reviewed sources*. These might include things like books, articles, or *official documentation*. Do not include links to random sources which you just happen to find as part of a Google search. Do some proper background research to verify the accuracy of the information you provide in your user manual. You may use either the Harvard or IEEE styles of citation. If you are not sure what these are, you should again do some background research to find out.

For an example of the sort of depth and type of description required, you should have a look at the on-line manuals for *bash* and *ZSH*

```
man bash
```
```
man zsh
```

These shells obviously have much more functionality than yours and thus, your manuals don’t have to be quite so large. However the manner in which things are described will give you an idea of the language and/or layout to use.

In this manual, you should NOT include building instructions, included file lists or source code - we can find that out from the other files you submit. Indeed, we should just have to type `make` to build your shell. This should be an Operator’s manual not a Developer’s manual.

## Submission

***~~This assignment has a submission due date of Sunday 6th March 2022 by 23:59.~~***

******This assignment has a submission due date of Friday 11th March 2022 by 17:00.***  
***

**This assignment must be completed individually.**

You will be using the [School of Computing Gitlab instance](https://gitlab.computing.dcu.ie/) to manage your code. A starter repository is available at:  
[https://gitlab.computing.dcu.ie/healygr/2022-ca216-myshell](https://gitlab.computing.dcu.ie/healygr/2022-ca216-myshell)

**Please read the instructions in this starter repository (readme.md)**

Importantly, fork (do not clone) this repository. Once you have forked it, make your own repository private and add both me (Graham Healy - [@healygr](https://loop.dcu.ie/healygr)) and Wandri Jooste ([@joostew2](https://loop.dcu.ie/joostew2)) as "maintainer". Do not modify any of the files in the forked repository after the deadline has passed.

The submission should contain only source code file(s), include file(s), a makefile (all lower case please), and the readme file (all lower case please). No executable program should be included. We will be automatically rebuilding your shell program from the source code provided. If the submitted code does not compile it will only receive the marks awarded for style and code quality. **Note that given the large class-size, we *will not* be in a position to chase people, or grade submissions which do not follow the requirements.**

The `makefile` (all lower case please) MUST generate the binary file `myshell` (all lower case please). A sample makefile would be:

```
# Joe Citizen, s1234567 - Operating Systems Project 1
# ca216/myshell

myshell: myshell.c utility.c myshell.h
    gcc -Wall myshell.c utility.c -o myshell
```

The program myshell is then generated by just typing make at the command line prompt. It is just a sample and essentially means that to generate the `myshell` binary, the other files should be compiled. **Note: the fourth line in the above makefile MUST begin with a tab**

In the example shown above, the files in the submitted directory would be:

1. makefile
2. myshell.c
3. utility.c
4. myshell.h
5. readme

### Required Documentation

Firstly, your source code will be assessed and marked as well as the readme manual. **Commenting is definitely required in your source code.** The user manual can be presented in a format of your choice (within the limitations of being displayable by a simple Text Editor). Again, the manual should contain enough detail for a beginner to UNIX to use the shell. For example, you should explain the concepts of i/o redirection, the program environment and background execution. The manual MUST be named readme (all lower case please, NO.txt extension).

Note: Your name, student number, and acknowledgement of the DCU Academic Integrity Policy must appear in each one of your submitted files. In the case of the *readme* place this content *at the end* of the file. that is: include the student number, name and declaration *after* the content.

## Marking Criteria

### The code (150 marks )

- Performance of internal commands and aliases (30 marks)
- External command functionality (10 marks)
- I/o redirection (10 marks)
- Background execution (10 marks)
- Readability, suitability & maintainability of source code and makefile (90 marks) (note: where reduced functionality is implemented, the potential marks here will also be reduced.)

### User manual (50 marks)

- Description of operation and commands (10 marks)
- Description of environment concepts (10 marks)
- Description of i/o redirection (10 marks)
- Description of the *process concept*, and the differences between *background* and *foreground* execution (5 marks)
- Overall layout and display of understanding (10 marks)
- Inclusion of four references from peer-reviewed sources such as books, articles etc. (5 marks). Note that the inclusion of Wikipedia, or a random website which just happened to come up in a Google search will result in a grade of 0 for this aspect.

## Wrap-up

Ensure that you address all the points specified in this project documentation. Looking at this specification, it probably seems daunting. However there will be some additional exercises to get you on track. Take this one small step at a time. And look at the Lab04/5 exercises!
