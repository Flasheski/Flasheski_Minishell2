/*
** EPITECH PROJECT, 2026
** G-PSU-200-LIL-2-1-minishell2-1
** File description:
** check_pipes
*/

#include "my.h"
#include "shell.h"

static int is_all_space(char *str)
{
    if (!str || str[0] == '\0')
        return 1;
    for (int i = 0; str[i]; i++) {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
            return 0;
    }
    return 1;
}

int check_pipe_errors(char **pipes, shell_t *shell)
{
    if (!pipes || !pipes[0])
        return 0;
    for (int i = 0; pipes[i] != NULL; i++) {
        if (is_all_space(pipes[i])) {
            my_puterror("Invalid null command.\n");
            shell->status = 1;
            return 1;
        }
    }
    return 0;
}
