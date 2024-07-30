#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

/* Function prototypes */
int ss_cd(const char *cmds);
void ss_exit(char **args);
void find_env(char **cmds);

/**
 * ss_cd - Changes the current working directory.
 * @args: Array of arguments, args[0] is "cd", args[1] is the directory path.
 */
int ss_cd(const char *cmds)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "ss: expected argument to \"cd\"\n");
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("ss");
        }
    }
    return 1;
}

/**
 * ss_exit - Exits the shell with an optional status code.
 * @args: Array of arguments, args[0] is "exit", args[1] is the exit status.
 */
void ss_exit(char **args)
{
    int status = 0;
    if (args[1] != NULL)
    {
        status = atoi(args[1]);
    }
    exit(status);
}

/**
 * ss_help - Prints help information about the shell.
 * @args: Array of arguments, args[0] is "help".
 */

/**
 * find_path - Finds and executes the command passed in the arguments.
 * @cmds: Array of command strings to be executed.
 */
void find_path(char **cmds)
{
    int cmd_index = 0;
    while (cmds[cmd_index] != NULL)
    {
        char **current_command = cmds[cmd_index];
        int is_builtin = 0;
        int builtin_index = 0;
        const char *builtin_commands[] = {"cd", "exit", "help"};
        void (*builtin_functions[])(char **) = {ss_cd, ss_exit, ss_help};

        for (builtin_index = 0; builtin_index < sizeof(builtin_commands) / sizeof(const char *); builtin_index++)
        {
            if (strcmp(current_command[0], builtin_commands[builtin_index]) == 0)
            {
                is_builtin = 1;
                (*builtin_functions[builtin_index])(current_command);
                break;
            }
        }

        if (!is_builtin)
        {
            find_env(cmds);
        }

        cmd_index++;
    }
}

/**
 * find_env - Executes the command passed in the arguments.
 * @cmds: Array of command strings to be executed.
 */
void find_env(char **cmds)
{
    pid_t pid = fork();
    if (pid == 0) /* Child process */
    {
        execvp(cmds[0], cmds);
        perror("ss"); /* execvp returns only on failure */
        exit(EXIT_FAILURE);
    }
    else if (pid > 0) /* Parent process */
    {
        wait(NULL); /* Wait for child to finish */
    }
    else /* Fork failed */
    {
        perror("ss");
    }
}
