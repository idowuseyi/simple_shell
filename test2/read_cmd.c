#include "shell.h"

void read_cmd(void)
{
	size_t buf_size;
	ssize_t nread;
	char *buf = NULL;
	char *buf_cpy = NULL;

	write(1, "#myshell$ ", 10);
	nread = getline(&buf, &buf_size, stdin);

	/* handle EOF condition*/
	if (nread == -1)
	{
		printf("\n...aborting\n");
		exit(0);
	}

	buf_cpy = malloc(sizeof(char) * nread);
	strcpy(buf_cpy, buf);

	parser(buf, buf_cpy);

	free(buf);
	free(buf_cpy);
}