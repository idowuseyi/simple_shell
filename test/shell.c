#include "main.h"

/**
 * main - calls the necessary functions for the shell
 * @argc: argument counter
 * @argv: actual arguments
 * Return: 0 or 1
 */
int main(int argc, char **argv)
{
	char *usrIn;
	char **args;
	int status;/*controls the closing or opening of the shell*/

	(void) argc;
	(void) argv;

	do {
		printf("MnA$ ");/*print the shell dollar sign*/
		usrIn = read_line();/*calling function for user input*/
		args = split(usrIn);/*split input into arguments with strok*/
		status = exec_func(args);/*calling execve on child processes*/
		/*memory management*/
		free(usrIn);
		free(args);
	} while (status);

	return (0);
}
/**
 * read_line - gets the input from the shell
 * Return: line or -1
 */
char *read_line(void)
{
	size_t size = 0;/*Expected size of input*/
	char *string_ptr = NULL;/*Output*/

	if (getline(&string_ptr, &size, stdin) == -1)/*check errors in input*/
	{
		if (feof(stdin))/*check for EOF*/
		{
			printf("\n");
			exit(EXIT_SUCCESS);/*we got an EOF*/
		}
		else
		{
			perror("Command not found!");
			exit(EXIT_SUCCESS);
		}
	}
	while (string_ptr[0] == '\n')/*if empty line ask again*/
	{
		printf("$ ");
		getline(&string_ptr, &size, stdin);
	}

	return (string_ptr);/*return the input read from the terminal*/
}
/**
 * split - breaks the string into tokens for execution
 * @str: string pointer we'll receive
 * Return: void but should be 0 for sucess, -1 for failure
 */

char **split(char *str)
{
	int bufsize = TOK_BUFSIZE, pos = 0;
	char **pieces = malloc(bufsize * (sizeof(char *)));
	char *piece;

	if (!pieces)/*malloc error check*/
	{
		fprintf(stderr, "Malloc error\n");
		exit(EXIT_FAILURE);
	}

	piece = strtok(str, TOK_DELIM);/*point to string to split*/
	while (piece != NULL)
	{
		pieces[pos] = piece;/*add token to list of tokens*/
		pos++;

		/*check if pos>bufsize and reallocate mem*/
		if (pos >= bufsize)
		{
			bufsize += TOK_BUFSIZE;
			pieces = realloc(pieces, bufsize * sizeof(char *));
			if (!pieces)
			{
				fprintf(stderr, "Malloc error\n");
				exit(EXIT_FAILURE);
			}
		}
		piece = strtok(NULL, TOK_DELIM);/*keep pointing to same string*/
	}
	pieces[pos] = NULL;
	return (pieces);

}

/**
 * launch_sh - runs the fork and exec functions to run multiple
 * programs via the shell
 * @args: pointer for arguments to be executed
 * Return: exit or 1 for success
 */

int launch_sh(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)/*check for child process*/
	{
		/*run an exec to run a program on the child process*/
		if (execve(args[0], args, NULL) == -1)
		{
			perror("./shell");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("Fork failure");
	}
	else /*for parent process, wait for child to complete*/
	{
		do {
			waitpid(pid, &status, WUNTRACED);/*check for these*/
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return (1);
}
/**
 * exec_func - executes the shell
 * @args: the arguments received
 * Return: 1 or shell launch
 */

int exec_func(char **args)
{
	int i;
	char *builtin_str[] = {
		"cd",
		"help",
		"exit",
		"env"
	};
	int (*builtin_func[]) (char **) = {
		&cd_func,
		&help_func,
		&exit_func,
		&env_func
	};

	if (args[0] == NULL)
		return (1);

	for (i = 0; i < num_builtins(); i++)
	{
		if (strcmp(args[0], builtin_str[i]) == 0)
		{
			return ((*builtin_func[i])(args));
		}
	}
	return (launch_sh(args));
}
