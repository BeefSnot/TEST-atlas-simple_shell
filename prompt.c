#include <sys/wait.h>
#include "shell.h"

/**
 * prompt - Prompts and parses user input.
 *
 * @return: Parsed user input.
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
