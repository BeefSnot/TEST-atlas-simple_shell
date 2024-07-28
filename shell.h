#ifndef _SHELL_H_
#define _SHELL_H_

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#define TOK_DELIM " \t\r\n\a"
#define TOK_BUFSIZE 64
#define MAX_CMDS 16
#define MAX_ARGS 64
#define MAX_LINE_LENGTH 256
#define MAX_BUILTINS 3

int main(void);
char **parse(const char *line); // Assuming parse should return char **
char **prompt(void);
void fork_exec(char **command, char *full_path);
void find_path(char **cmds);
void ss_cd(char **args);
void ss_exit(char **args);
void ss_help(char **args);
void findenv(char **cmds); // Corrected typo here

#endif
