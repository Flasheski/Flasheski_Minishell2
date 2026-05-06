/*
** EPITECH PROJECT, 2026
** Shell
** File description:
** my_str_to_word_array
*/

#include "my.h"
#include <stdlib.h>

int is_delim(char c, const char *delim)
{
    if (c == '\0' || c == '\n')
        return 1;
    for (int i = 0; delim[i]; i++) {
        if (c == delim[i])
            return 1;
    }
    return 0;
}

int count_words(char const *str, const char *delim)
{
    int count = 0;

    for (int i = 0; str[i]; i++) {
        if (!is_delim(str[i], delim) && is_delim(str[i + 1], delim))
            count++;
    }
    return count;
}

char **my_str_to_word_array(char const *str, const char *delim)
{
    int nb_words = count_words(str, delim);
    char **res = malloc(sizeof(char *) * (nb_words + 1));
    int i = 0;
    int k = 0;
    int start = 0;

    if (!res)
        return NULL;
    while (str[i] != '\0' && k < nb_words) {
        while (str[i] && is_delim(str[i], delim))
            i++;
        start = i;
        while (str[i] && !is_delim(str[i], delim))
            i++;
        res[k] = my_strndup(&str[start], i - start);
        k++;
    }
    res[k] = NULL;
    return res;
}
