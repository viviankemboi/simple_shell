#include <unistd.h>
#include "shell.h"

/**
 * _getenv - gets an envirnt var
 *
 * @name: name of environmental var
 * @env: current environmt
 *
 * Return: pointer to the value in the environmt,
 * or NULL if there is no match
 *
 */
char *_getenv(const char *name, char **env)
{
	int i, j, check, l = 0;

	if (!env)
		return (NULL);

	while (name[l] != 0)
		l++;

	for (i = 0; env[i] != 0; i++)
	{
		for (check = 0, j = 0; j < l && env[i][j] != 0; j++)
			if (env[i][j] == name[j])
				check++;
		if (check == l && env[i][check] == '=')
			return (env[i]);
	}

	return (NULL);
}
