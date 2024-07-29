#include "shell.h"

/**
 * ss_help - Lists the built-in functions of the shell.
 */
void ss_help(char **args)
{
    size_t i;
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
