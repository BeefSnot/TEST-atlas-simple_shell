#include "shell.h"

/**
 * find_path - Processes parsed commands.
 * @cmds: An array of command strings to be processed.
 *
 * This function iterates through an array of command strings,
 * identifying and executing built-in shell commands if present.
 * Otherwise, it delegates the execution to the environment.
 */
void find_path(char **cmds)
{
    int cmd_index = 0;

    while (cmds[cmd_index] != NULL)
    {
        char **current_command = cmds[cmd_index];
        int is_builtin = 0;
        int builtin_index = 0;
        char *builtin_commands[] = {"cd", "exit", "help"};
        void (*builtin_functions[])() = {ss_cd, ss_exit, ss_help};

        for (builtin_index = 0; builtin_index < sizeof(builtin_commands) / sizeof(char *); builtin_index++)
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
