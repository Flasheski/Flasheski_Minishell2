/*
** EPITECH PROJECT, 2026
** G-PSU-200-LIL-2-1-minishell2-1
** File description:
** find_command
*/

#include "my.h"
#include "shell.h"

int is_char_in_str(char *str, char c)
{
    for (int i = 0; str[i]; i++) {
        if (c == str[i])
            return 1;
    }
    return 0;
}

char *find_command(char *command, char **env)
{
    char *path_env;
    char *path_cpy;
    char *res;

    if (command && (is_char_in_str(command, '/'))) {
        if (access(command, X_OK) == 0)
            return my_strdup(command);
        return NULL;
    }
    path_env = get_env_with_path(env);
    if (!path_env)
        return NULL;
    path_cpy = my_strdup(path_env);
    res = check_path_with_dirs(path_cpy, command);
    free(path_cpy);
    return res;
}
