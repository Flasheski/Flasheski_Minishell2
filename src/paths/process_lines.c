/*
** EPITECH PROJECT, 2026
** G-PSU-200-LIL-2-1-minishell2-1
** File description:
** process_lines
*/

#include "my.h"
#include "shell.h"

int handle_pipes_logic(char *command_block, shell_t *shell)
{
    char **pipes = my_str_to_word_array(command_block, "|");
    int run = 1;
    char **args = NULL;

    if (!pipes || !pipes[0])
        return 1;
    if (check_pipe_errors(pipes, shell)) {
        free_array(pipes);
        return 1;
    }
    if (pipes[1] == NULL) {
        args = my_str_to_word_array(pipes[0], " \t\n");
        run = exec_cmd(args, shell);
        free_array(args);
    } else {
        exec_pipe(pipes, shell);
        run = shell->run_status;
    }
    free_array(pipes);
    return run;
}

int process_line(char *line, shell_t *shell)
{
    char **segms = my_str_to_word_array(line, ";");
    int run = 1;

    if (!segms)
        return 1;
    for (int i = 0; segms[i] != NULL && run == 1; i++)
        run = handle_pipes_logic(segms[i], shell);
    free_array(segms);
    return run;
}
