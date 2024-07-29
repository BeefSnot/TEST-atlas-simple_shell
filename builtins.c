#include "shell.h"

/**
 * ss_cd - Changes the current working directory.
 * @cmds: The command to be executed.
 *
 * Return: 1 on success, -1 on failure.
 */
int ss_cd(const char *cmds)
{
    if (!cmds || !cmds[1])
    {
        fprintf(stderr, "ss: expected argument to \"cd\"\n");
        return (-1);
    }
    if (chdir(&cmds[1]) == -1)
    {
        perror("ss");
        return (-1);
    }
    return (1);
}

/**
 * ss_exit - Exits the shell.
 */
int ss_exit(void)
{
    exit(EXIT_SUCCESS);
    return 0;
}

/**
 * ss_help - Lists the built-in functions of the shell.
 */
void ss_help(void)
{
    int i;
    const char *builtins[] = {"ss_cd", "ss_exit", "ss_help"};

    printf("Welcome to the ATLAS Simple Shell!\n");
    printf("A group project made by Max and James\n");
    printf("Here are the built-in features:\n");
    printf("Type the program names and arguments,\n");
    printf("Press the 'enter' key to execute your command!\n");
    for (i = 0; i < sizeof(builtins) / sizeof(builtins[0]); i++)
    {
        printf("%s\n", builtins[i]);
    }
    printf("If you need more information, feel free to use the 'man' command\n");
    printf("to view the manual for the shell!\n");
}
