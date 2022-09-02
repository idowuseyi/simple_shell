#ifndef _MAIN_H
#define _MAIN_H

#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"
void shell_loop(void);
char *read_line(void);
char **split(char *str);
int launch_sh(char **args);
int exec_func(char **args);
int exit_func(char **args);
int help_func(char **args);
int cd_func(char **args);
int num_builtins(void);
int env_func(char **args);

#endif 
