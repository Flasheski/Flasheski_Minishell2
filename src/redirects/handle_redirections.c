/*
** EPITECH PROJECT, 2026
** G-PSU-200-LIL-2-1-minishell2-1
** File description:
** handle_redirections
*/

#include "my.h"
#include "shell.h"

int my_array_len(char **array)
{
    int i = 0;

    if (!array)
        return 0;
    while (array[i] != NULL)
        i++;
    return i;
}

static void shift_args(char **args, int i)
{
    int len = my_array_len(args);
    int j = i;

    free(args[i]);
    free(args[i + 1]);
    while (args[j + 2] != NULL) {
        args[j] = args[j + 2];
        j++;
    }
    args[len - 1] = NULL;
    args[len - 2] = NULL;
}

int apply_out(char **args, int i, int flags)
{
    int fd = 0;

    if (args[i + 1] == NULL)
        return -1;
    fd = open(args[i + 1], flags, 0644);
    if (fd == -1) {
        my_puterror(args[i + 1]);
        my_puterror(": Permission denied.\n");
        return -1;
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    shift_args(args, i);
    return 1;
}

int apply_in(char **args, int i)
{
    int fd = 0;

    if (args[i + 1] == NULL)
        return -1;
    fd = open(args[i + 1], O_RDONLY);
    if (fd == -1) {
        my_puterror(args[i + 1]);
        my_puterror(": No such file or directory.\n");
        return -1;
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    shift_args(args, i);
    return 1;
}

int check_symbols(char **args, int i)
{
    if (my_strcmp(args[i], ">") == 0)
        return apply_out(args, i, O_CREAT | O_WRONLY | O_TRUNC);
    if (my_strcmp(args[i], ">>") == 0)
        return apply_out(args, i, O_CREAT | O_WRONLY | O_APPEND);
    if (my_strcmp(args[i], "<") == 0)
        return apply_in(args, i);
    return 0;
}

int handle_redirections(char **args)
{
    int res = 0;

    if (!args || !args[0])
        return 0;
    for (int i = 0; args[i] != NULL; i++) {
        res = check_symbols(args, i);
        if (res == -1)
            return -1;
        if (res == 1)
            i = -1;
    }
    return 0;
}
