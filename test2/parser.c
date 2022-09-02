#include "shell.h"

void parser(char *buf, char *buf_cpy)
{
	char *token;
	int num_tok = 0, i;
	char delim[] = " \n";
	char **argv = NULL;

	/* specify how many token are present in buf
	* this helps determine size of argv array
	*/

	token = strtok(buf, delim);
	while (token)
	{
		num_tok++;
		token = strtok(NULL, delim);
	}

	num_tok++;
	argv = malloc(sizeof(char *) * num_tok);

	token = strtok(buf_cpy, delim);
	for (i = 0; token; i++)
	{
		argv[i] = malloc(sizeof(char) * strlen(token));
		strcpy(argv[i], token);
		token = strtok(NULL, delim);
	}

}