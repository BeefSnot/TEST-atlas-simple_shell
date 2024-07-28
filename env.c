#include "shell.h"

/**
 * find_env - Searches the PATH environment variable for the executable.
 * @cmds: An array of command tokens.
 *
 * This function constructs paths based on the PATH environment variable,
 * searches for the executable, and executes it if found.
 *
 * Note: This function does not return a value; it operates by side effect.
 */
void find_env(char **cmds) {
    char *path_env = getenv("PATH");
    if (!path_env) {
        fprintf(stderr, "Environment variable PATH is not set.\n");
        return;
    }

    char *path_copy = strdup(path_env);
    if (!path_copy) {
        perror("Failed to duplicate PATH environment variable.");
        return;
    }

    char *path_dir = strtok(path_copy, ":");
    while (path_dir != NULL) {
        char *full_path = malloc(strlen(path_dir) + strlen(cmds[0]) + 2);
        if (!full_path) {
            perror("Memory allocation failed");
            free(path_copy);
            exit(EXIT_FAILURE);
        }

        strcpy(full_path, path_dir);
        strcat(full_path, "/");
        strcat(full_path, cmds[0]);

        if (access(full_path, X_OK) == 0) {
            if (fork_exec(cmds, full_path)) {
                perror("Failed to execute command");
            }
        } else {
            fprintf(stderr, "Executable '%s' not found in PATH.\n", cmds[0]);
        }

        free(full_path);
        path_dir = strtok(NULL, ":");
    }

    free(path_copy);
}
