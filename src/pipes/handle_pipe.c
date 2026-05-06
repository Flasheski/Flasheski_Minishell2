/*
** EPITECH PROJECT, 2026
** Shell
** File description:
** handle_pipe
*/

#include "my.h"
#include "shell.h"

void setup_pipe(int file_din, int pipe_fd[2], char *next_cmmd)
{
    if (file_din != STDIN_FILENO) {
        dup2(file_din, STDIN_FILENO);
        close(file_din);
    }
    if (next_cmmd != NULL) {
        dup2(pipe_fd[1], STDOUT_FILENO);
    }
    close(pipe_fd[0]);
}

static void parent_exec(int file_din, char *command, shell_t *shell)
{
    char **args = NULL;
    int save_in = dup(STDIN_FILENO);
    int save_out = dup(STDOUT_FILENO);

    if (!command)
        return;
    if (file_din != STDIN_FILENO) {
        dup2(file_din, STDIN_FILENO);
        close(file_din);
    }
    args = my_str_to_word_array(command, " \t\n");
    if (args) {
        shell->run_status = exec_cmd(args, shell);
        free_array(args);
    }
    dup2(save_in, STDIN_FILENO);
    dup2(save_out, STDOUT_FILENO);
    close(save_in);
    close(save_out);
}

static void child_logic(int file_din, int pipe_fd[2], char **cmds, shell_t *sh)
{
    char **args = my_str_to_word_array(cmds[0], " \t\n");
    char *path = NULL;

    setup_pipe(file_din, pipe_fd, cmds[1]);
    if (handle_redirections(args) == -1 || exec_simple_command(args, sh) != -1)
        exit(sh->status);
    path = find_command(args[0], sh->env);
    if (!path || is_invalid_bin(path, sh)) {
        my_puterror(args[0]);
        my_puterror(": Command not found.\n");
        exit(1);
    }
    execve(path, args, sh->env);
    exit(sh->status);
}

void exec_pipe(char **commands, shell_t *shell)
{
    int pipe_init[2];
    int file_din = STDIN_FILENO;
    int i = 0;

    for (; commands[i] && commands[i + 1] != NULL; i++) {
        if (pipe(pipe_init) == -1)
            return;
        if (fork() == 0)
            child_logic(file_din, pipe_init, &commands[i], shell);
        close(pipe_init[1]);
        if (file_din != STDIN_FILENO)
            close(file_din);
        file_din = pipe_init[0];
    }
    parent_exec(file_din, commands[i], shell);
    while (wait(NULL) > 0);
}
