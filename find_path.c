#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "./shell.h"

/* Function prototypes */
void ss_cd(char **args);
void ss_exit(char **args);
void ss_help(char **args);
void find_path(char **cmds);
void find_env(char **cmds);

int main(int argc, char *argv[])
{
    char *commands[] = {"cd", "/home/user", "exit", "ls", NULL};
    find_path(commands);
    return 0;
}

void ss_cd(char **args)
{
    if (args[1] == '\0')
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
}

void ss_exit(char **args)
{
    int status = 0;
    if (args[1] != NULL)
    {
        status = atoi(args[1]);
    }
    exit(status);
}

void ss_help(char **args)
{
    printf("Simple Shell\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");
    printf("  cd\n");
    printf("  exit\n");
    printf("  help\n");
}

void find_path(char **cmds)
{
    int cmd_index = 0;
    while (cmds[cmd_index] != NULL)
    {
        int is_builtin = 0;
        int builtin_index = 0;
        const char *builtin_commands[] = {"cd", "exit", "help"};
        void (*builtin_functions[])(char **) = {ss_cd, ss_exit, ss_help};

        for (builtin_index = 0; builtin_index < sizeof(builtin_commands) / sizeof(const char *); builtin_index++)
        {
            if (strcmp(cmds[cmd_index], builtin_commands[builtin_index]) == 0)
            {
                is_builtin = 1;
                (*builtin_functions[builtin_index])(&cmds[cmd_index]);
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
