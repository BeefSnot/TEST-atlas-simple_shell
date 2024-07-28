#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void ss_cd(char **args);
void ss_exit(int status);
void ss_help(void);

void find_env(char **cmds);

/**
 * find_path - Processes parsed commands.
 * @cmds: An array of command strings to be processed.
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
        void (*builtin_functions[])() = {ss_cd, ss_exit, ss_help};

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

void ss_cd(char **args)
{
    
}

void ss_exit(int status)
{
    
}

void ss_help(void)
{
    
}

void find_env(char **cmds)
{
    
}
