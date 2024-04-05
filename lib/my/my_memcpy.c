/*
** EPITECH PROJECT, 2024
** memcpy
** File description:
** title
*/

#include <malloc.h>
#include <stddef.h>
#include "my.h"

void my_memcpy(void *dest, void *src, size_t size)
{
    char *cdest = (char *) dest;
    char *csrc = (char *) src;

    for (size_t i = 0; i < size; i += 1)
        cdest[i] = csrc[i];
}
