/*
** EPITECH PROJECT, 2026
** Shell
** File description:
** free_array
*/

#include "shell.h"
#include "my.h"

void free_array(char **array)
{
    if (!array)
        return;
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}
