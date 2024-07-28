#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

/**
 * prompt - Prompts and parses user input.
 *
 * Return: Parsed user input.
 */
char **prompt(void)
{
    char *line = NULL;
    char **parsed_cmds;
    ssize_t line_length;
    size_t bufsize = 0;

    printf(":) ");
    line_length = getline(&line, &bufsize, stdin);
    if (line_length == -1)
    {
        if (feof(stdin))
            exit(EXIT_SUCCESS);
        else
        {
            perror("getline failed");
            exit(EXIT_FAILURE);
        }
    }

    parsed_cmds = parse(line);
    free(line);

    return parsed_cmds;
}
