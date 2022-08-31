#include "main.h"

int cd_func(char **args);
int help_func(char **args);
int exit_func(char **args);
int exec_func(char **args);
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

/**
 * num_builtins - returns the number of characters from a
 * built-in string
 * Return: as stated above
 */
int num_builtins(void)
{
	return (sizeof(builtin_str) / sizeof(char *));
}
/**
 * cd_func - changes directory to the one provided in the next
 * argument
 * @args: the string token it receives as arguments
 * Return: an int
 */

int cd_func(char **args)
{
	if (args[1] == NULL)
		fprintf(stderr, "Provide arguments");
	else
	{
		if (chdir(args[1]) != 0)
			perror("Shell");
	}
	return (1);
}
/**
 * help_func - changes directory to the one provided in the next
 * argument
 * @args: string token
 * Return: an int
 */
int help_func(char **args)
{
	int i;

	printf("Simple shell by Amos and Miheret\n");
	printf("Usage: <command> <arguments>\n");
	printf("Here's a list of builtin commands:\n");

	for (i = 0; i < num_builtins(); i++)
	{
		printf(" %s\n", builtin_str[i]);
	}

	printf("run ./man_1_simple_shell for more info.\n");

	return (1);
}
/**
 * exit_func - exits the shell
 * @args: string token
 * Return: 0
 */
int exit_func(char **args)
{
	return (0);
}
/**
 * env_func - should print the environment variables
 * @args: pointer to the string
 *Return: 1
 */
int env_func(char **args)
{
	system("/bin/printenv");

	return (1);
}
