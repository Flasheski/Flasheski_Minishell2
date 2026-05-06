/*
** EPITECH PROJECT, 2026
** G-PSU-200-LIL-2-1-minishell2-1
** File description:
** shell
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

#ifndef SHELL_H_
    #define SHELL_H_

    #define ERROR_EXIT 84
    #define SUCCESS_EXIT 0

typedef struct shell_s {
    char **env;
    char *prev_path;
    int status;
    int run_status;
} shell_t;

// commands
char *find_command(char *command, char **env);
// execute_commands
int exec_cmd(char **args, shell_t *shell);
int exec_simple_command(char **args, shell_t *shell);
void exec_builtin_cd(char **args, shell_t *shell);
void exec_builtin_env(char **env, int *status);
void exec_builtin_setenv(char **args, shell_t *shell);
void exec_builtin_unsetenv(char **args, shell_t *shell);
// paths
char *build_path(char *dir, char *command);
void print_cd_path(char *path);
void display_path_prompt(shell_t *shell);
char *get_env_with_path(char **env);
char *get_env_specific(char **env, char *var);
char *check_path_with_dirs(char *path_copy, char *command);
int find_var_idx(char **env, char *name);
// signals
void sigint_handler(int sig);
void check_child_status(int status, shell_t *shell);
// env
char **copy_env(char **env);
void free_env(char **env);
// pipes and redirections
void exec_pipe(char **commands, shell_t *shell);
int handle_redirections(char **args);
int process_line(char *line, shell_t *shell);
int check_pipe_errors(char **pipes, shell_t *shell);
// others
void free_array(char **array);
int is_invalid_bin(char *path, shell_t *shell);
#endif /* !SHELL_H_ */
