#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include "shell.h"

/**
 * executeCmd -will create a child process to execute a cmd
 *
 * @program: command that is   executed
 * @command: argument of command
 * @env: current environ
 * @shpack: struct with shell info
 *
 * Return: pointer to the value in the enviro,
 * or NULL if there is no match
 *
 */
int executeCmd(char *program, char *command[], char **env, hshpack *shpack)
{
	pid_t process, status;
	int execveSts = 0, waitSts = 0;

	process = fork();
	signal(SIGINT, signal_handler2);
	if (process == -1)
	{
		write(2, "Fork Error", 10);
		exit(-1);
	}
	if (process == 0)
	{

		execveSts = execve(program, command, env);
		if (execveSts == -1)
		{
			_exit(-1);
		}
	}
	else
	{
		waitSts = wait(&status);
		signal(SIGINT, signal_handler);
		if (waitSts == -1)
			exit(-1);
		if (WEXITSTATUS(status) == 0)
			shpack->exitnum[0] = 0;
		else
			shpack->exitnum[0] = 2;
	}

	shpack->errnum[0] += 1;
	return (0);
}
