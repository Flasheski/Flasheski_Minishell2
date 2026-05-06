/*
** EPITECH PROJECT, 2026
** G-PSU-200-LIL-2-1-minishell2-1
** File description:
** exec
*/

#include "my.h"
#include "shell.h"

void clean_quotes(char *str)
{
    int len = my_strlen(str);

    if (len < 2)
        return;
    if ((str[0] == '\"' && str[len - 1] == '\"') ||
        (str[0] == '\'' && str[len - 1] == '\'')) {
        for (int i = 0; str[i] != '\0'; i++)
            str[i] = str[i + 1];
        str[len - 2] = '\0';
    }
}

int is_invalid_bin(char *path, shell_t *shell)
{
    struct stat s;

    if (stat(path, &s) == -1)
        return 0;
    if (S_ISDIR(s.st_mode)) {
        my_puterror(path);
        my_puterror(": Permission denied.\n");
        shell->status = 1;
        return 1;
    }
    return 0;
}

void handle_exec_error(char *path, shell_t *shell)
{
    my_puterror(path);
    if (errno == ENOEXEC) {
        my_puterror(": Exec format error. Binary file not executable.\n");
        shell->status = 1;
    } else {
        my_puterror(": Permission denied.\n");
        shell->status = 1;
    }
    exit(ERROR_EXIT);
}

void run_process(char *path, char **args, char **env, shell_t *shell)
{
    pid_t pid = fork();
    int status = 0;

    if (pid == 0) {
        if (handle_redirections(args) == -1) {
            exit(1);
        }
        if (execve(path, args, env) == -1)
            handle_exec_error(path, shell);
    } else {
        waitpid(pid, &status, 0);
        check_child_status(status, shell);
    }
}

static int get_and_run_bin(char **args, char **env, shell_t *sh)
{
    char *path = NULL;

    for (int i = 0; args[i]; i++)
        clean_quotes(args[i]);
    path = find_command(args[0], env);
    if (!path) {
        my_puterror(args[0]);
        my_puterror(": Command not found.\n");
        sh->status = 1;
        return 1;
    }
    if (is_invalid_bin(path, sh)) {
        free(path);
        return 1;
    }
    run_process(path, args, env, sh);
    free(path);
    return sh->status;
}

int exec_cmd(char **args, shell_t *shell)
{
    int ret_builtin = 0;

    if (!args || !args[0]) {
        my_puterror("Invalid null command.\n");
        shell->status = 1;
        return 1;
    }
    ret_builtin = exec_simple_command(args, shell);
    if (ret_builtin != -1)
        return ret_builtin;
    get_and_run_bin(args, shell->env, shell);
    return 1;
}
