.TH SIMPLE_SHELL 1 "November 2019" "Holberton School" "Linux Programmers Manual"
.SH NAME
simple_shell - command language interpreter that reads from standard input
.SH SYNOPSIS

simple_shell is a program that reads commands provided by a user and attempts to execute them through low level system procedures.

It can be compiled with most warnings and errors flags. In the case of GCC, them being:

.B gcc -Wall -Werror -Wextra -pedantic *.c -o hsh

In order to run the shell, the user must have executable permissions and use the command.

.B ./hsh

(or the name of the executable in case it is changed)

.SH DESCRIPTION

The simple shell program obtains commands provided by a user through Standard Input stream and attempts to execute them by
searching for corresponding built in functions in the shell, or executables present in the operating system and defined in the
environmental variable PATH.

When an error occurs, such as when a command is not found, or it is called with invalid options, a message is produced on the
Standard Error stream, and an exit error number is set accordingly.

.TP
\fB Return (Exit Value) \fR

Upon termination of the simple shell program, an exit value will be set according to the status of the last command
executed. If the command ran succesfuly, the exit value will be zero (0).


If an error was encounter, the values that can be set are:

1 - Catchall for general errors

2 - Misuse of shell builtins

126 - Command invoked cannot execute

127 - command not found

130 - Script terminated by Control-C


.TP
\fBFORMAT OF COMMAND INPUT\fR

The simple shell can work in two different modes, \fIinteractive\fR and \fInon-interactive\fR. In both modes, commands
can be written with their absolute path or simply their executable name if they exist in one of the folders defined by
PATH.

Example:

\fB/bin/ls\fR is the same as \fBls\fR (ls exists in one of the PATH folders)


.IP \fB-Interactive Mode:\fR

In this condition, the shell will display a prompt ($) that will indicate that the user can provide commands by writing them
with a keyboard. In order to execute the commands the user will need to press the enter key (new line).

Each time a command is executed, the prompt will reappear and wait for a new user input.

Example:

\fBvagrant@vagrant-ubuntu-trusty-64:~/simple_shell$\fR ./hsh

$ ls

file1 file2 dira dirb

$

In order to exit the simple shell, the user must press the combination CTRL + D, as the CTRL + C signal is reserved only for internal script termination and it does not exit the shell.

.IP \fB-Non-interactive Mode:\fR

In this condition, the shell will run commands provided through a pipe at the moment of execution, and will not display a prompt
($) or wait for new user input:

Example:

\fBvagrant@vagrant-ubuntu-trusty-64:~/simple_shell$\fR echo "ls" | ./hsh

file1 file2 dira dirb

\fBvagrant@vagrant-ubuntu-trusty-64:~/simple_shell$\fR


.TP
\fBArguments\fR

Most commands have several options or arguments that can be used when executing the program. In order for the Shell to recognize
those parameters, the user must separate everything with spaces.

Example:


\fBvagrant@vagrant-ubuntu-trusty-64:~/simple_shell$\fR ./hsh

$ ls -l /tmp

total 0

$

or

\fBvagrant@vagrant-ubuntu-trusty-64:~/simple_shell$\fR echo "ls -l /tmp" | ./hsh

total 0

\fBvagrant@vagrant-ubuntu-trusty-64:~/simple_shell$\fR

.TP
\fBComments\fR

Commands can be run with an extra parameter called a comment. This parameter is used for writing a descriptory text when executing. In order to use this option
the user will have to add the character '#' after a command or its arguments with a trailing space:

Example:

\fBtest@ubuntu:~/simple_shell$\fR ./hsh

$ ls -l /tmp \fB#This is a Comment\fR

total 0

$

Everything written after the character '#' will be ignored in the execution.


.TP
\fBBuiltins\fR

.RS
simple shell has some commands that run internally when executed and don't depend on external programs.

.IP \fBexit\fR

This command is used for exiting the shell and can be used in two formats:

$ exit

or

$ exit status (Where status is an integer number)

If no status is provided, the shell will exit with the value of the last
encountered error or zero (0) if no error was ever encountered.


.IP \fBenv\fR

(Environment) This command is used for displaying the system's current environment in the format variable=value.

Its use is fairly simple:

$ env

with no options.

.IP \fBsetenv\fR

This command will overwrite the value of an environmental variable if it already exists, or create a new one in case
it does not. Its syntax is as follows:

$ setenv VARIABLE VALUE

The VARIABLE argument must not contain the character '=' otherwise an error will be displayed.

If the command is used without arguments in the form:

$ setenv

The current environment will be printed as if \fBenv\fR had been used.

.IP \fBunsetenv\fR

This command will remove an environmental variable from the system if it exists, or leave the environment untouched
if it does not exist. Its syntax is as follows.

$ unsetenv VARIABLE

The VARIABLE argument must not contain the character '=' otherwise an error will be displayed.

If used without arguments unsetenv will simply leave the environment untouched.

.IP \fBcd\fR

(Change Directory) This command is used for changing the current working directory with the syntax:

$ cd DIRECTORY

If cd is used without directory in the form

$ cd

The command will change directory to the value indicated in the environmental variable HOME.

If used without directory but with the option '-'

$ cd -

The command will change to the previous working directory. By default, the previous dir is initially HOME.

Note: Each time cd is used, the environmental variable PWD is updated to reflect the working directory.

.IP \fBhelp\fR

This command will show a text explaning the usage of a built in. Its syntax is as follows:

$ help BUILTIN


If no argument is given, a list of available built in commands will be shown with their usage syntax. If a built in
that doesn't exist is given, then an error will be displayed.

Note: The help command can also be used on itself

$ help help


.RE
.TP
\fBSearch and Execution\fR

The simple shell will always have the same order of search an execution.

When a command is written and given to the Shell, the Shell will initially check if the command is a built in. If the
condition is met, then the command will be executed internally, and the prompt will be displayed again.


If a builtin command is not found, one of two things happen:

\fB1.\fR Command names containing a slash are simply executed without performing any searches.

\fB2.\fR The shell searches each entry in the environmental variable PATH for the command.  The value of the
PATH variable should be a series of entries separated by colons.  Each entry consists of a directory name.
The current directory may be indicated implicitly by an empty directory name, or explicitly by a single period.

If the command is found in the PATH, then its executable is run in a sub-process, also called child process, so that
after its termination, the Shell does not exit.

If the command is not found, then the Shell will display an error indicating the issue. The Shell will also
keep track of the command count and display it when the error appears.



.SH GENERAL USE EXAMPLES

.RE


.IP \fBInteractive Mode\fR


\fBvagrant@vagrant-ubuntu-trusty-64:~/simple_shell$\fR ./hsh

$ ls

file1 file2 dira dirb

$ ls -l

-rw-rw-r-- 1 vagrant vagrant  1293 Nov 25 02:01 file1

-rw-rw-r-- 1 vagrant vagrant  4768 Nov 23 23:01 file2

drwxrwxr-x 2 vagrant vagrant  4096 Nov 21 14:48 dira

drwxrwxr-x 2 vagrant vagrant  4126 Nov 21 11:21 dirb

$ echo Hello

Hello

$ qwerty

\ ./hsh: 4: qwerty: not found

$ env

USER=vagrant

LANGUAGE=en_US

SESSION=ubuntu

COMPIZ_CONFIG_PROFILE=ubuntu

SHLVL=1

HOME=/home/vagrant

DESKTOP_SESSION=ubuntu

LOGNAME=vagrant

TERM=xterm-256color

PATH=/home/vagrant/bin:/home/vagrant/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin

DISPLAY=:0

$ exit

\fBvagrant@vagrant-ubuntu-trusty-64:~/simple_shell$\fR

.IP \fBNon-interactive Mode\fR

\fBvagrant@vagrant-ubuntu-trusty-64:~/simple_shell$\fR echo "ls" | ./hsh

file1 file2 dira dirb

\fBvagrant@vagrant-ubuntu-trusty-64:~/simple_shell$\fR echo "ls -l" | ./hsh

-rw-rw-r-- 1 vagrant vagrant  1293 Nov 25 02:01 file1

-rw-rw-r-- 1 vagrant vagrant  4768 Nov 23 23:01 file2

drwxrwxr-x 2 vagrant vagrant  4096 Nov 21 14:48 dira

drwxrwxr-x 2 vagrant vagrant  4126 Nov 21 11:21 dirb


\fBvagrant@vagrant-ubuntu-trusty-64:~/simple_shell$\fR echo "qwerty" | ./hsh

\ ./hsh: 1: qwerty: not found

\fBvagrant@vagrant-ubuntu-trusty-64:~/simple_shell$\fR

.SH BUGS

--

.SH AUTHORS
FarrenK and Viviankemboi
