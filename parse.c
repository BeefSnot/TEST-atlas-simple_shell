#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * parse - Parses user input into distinct commands and arguments.
 * @line: The user input string to be parsed.
 *
 * Return: A double pointer to an array of commands and their arguments,
 *         or NULL on failure.
 */
char **parse(const char *line);
{
    int command_index = 0;
    char *current_command, *argument;
    char ***parsed_commands = NULL;
    char *line_copy;
    
    parsed_commands = malloc(MAX_CMDS * sizeof(char **));
    if (!parsed_commands)
    {
        fprintf(stderr, "Failed to allocate memory for parsed commands.\n");
        exit(EXIT_FAILURE);
    }

    line_copy = strdup(line);
    if (!line_copy)
    {
        fprintf(stderr, "Failed to duplicate input line.\n");
        free(parsed_commands);
        exit(EXIT_FAILURE);
    }

    current_command = strtok(line_copy, "|");
    while (current_command && command_index < MAX_CMDS)
    {
        int argument_index = 0;
        char **command_args = NULL;

        command_args = malloc(MAX_ARGS * sizeof(char *));
        if (!command_args)
        {
            fprintf(stderr, "Failed to allocate memory for command arguments.\n");
            free(parsed_commands);
            free(line_copy);
            exit(EXIT_FAILURE);
        }

        argument = strtok(current_command, TOK_DELIM);
        while (argument && argument_index < MAX_ARGS - 1)
        {
            command_args[argument_index] = strdup(argument);
            if (!command_args[argument_index])
            {
                fprintf(stderr, "Failed to duplicate argument string.\n");
                for (int i = 0; i < argument_index; i++)
                    free(command_args[i]);
                free(command_args);
                free(parsed_commands);
                free(line_copy);
                exit(EXIT_FAILURE);
            }
            argument_index++;
            argument = strtok(NULL, TOK_DELIM);
        }

        command_args[argument_index] = NULL;
        parsed_commands[command_index] = command_args;
        command_index++;

        current_command = strtok(NULL, "|");
    }

    parsed_commands[command_index] = NULL;
    free(line_copy);

    return parsed_commands;
}
