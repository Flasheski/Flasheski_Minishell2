/*
** EPITECH PROJECT, 2026
** Shell
** File description:
** my_strndup
*/

#include "my.h"

char *my_strndup(char const *str, int n)
{
    char *dest = malloc(sizeof(char) * (n + 1));

    if (!dest)
        return NULL;
    for (int i = 0; i < n; i++)
        dest[i] = str[i];
    dest[n] = '\0';
    return dest;
}
