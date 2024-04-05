/*
** EPITECH PROJECT, 2024
** realloc
** File description:
** title
*/

#include <malloc.h>
#include <stddef.h>
#include "my.h"

void *my_realloc(void *ptr, size_t new_size, size_t old_size)
{
    void *new_ptr;

    if (new_size == old_size)
        return ptr;
    if (ptr == NULL)
        return malloc(new_size);
    if (new_size == 0) {
        free(ptr);
        return NULL;
    }
    new_ptr = malloc(new_size);
    if (new_ptr == NULL)
        return NULL;
    my_memcpy(new_ptr, ptr, old_size);
    free(ptr);
    return new_ptr;
}
