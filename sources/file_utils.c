/*
** EPITECH PROJECT, 2023
** file_utils
** File description:
** title
*/

#include <file_utils.h>
#include <my.h>
#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

static unsigned int getnbr(char *buffer, int *minus, int *d, int l)
{
    unsigned int r = 0;

    for (unsigned int i = 0; buffer[i] != '\0' && buffer[i] != '\n'; i++) {
        if (!IS_NUM(buffer[i]) && buffer[i] != '-' && buffer[i] != '+')
            r = UINT32_MAX;
        if (buffer[i] == '-')
            *minus *= -1;
        if (IS_NUM(buffer[i])) {
            r += (buffer[i] - '0') * my_compute_power_rec(10, l - *d - 1);
            *d += 1;
        }
    }
    return r;
}

int fs_get_number_from_first_line(char *buffer, unsigned int *r)
{
    int d = 0;
    int l = 0;
    int minus = 1;

    for (int k = 0; buffer[k] != '\n' && buffer[k] != '\0'; k++) {
        if (!IS_NUM(buffer[k]))
            break;
        ++l;
    }
    *r = getnbr(buffer, &minus, &d, l);
    if (*r == UINT32_MAX || minus < 0)
        return my_put_stderr("bad number of ants.\n");
    return 0;
}

static int alloc_tmp(int *s, int *out, char **tmp)
{
    *tmp = malloc(*s + 2);
    if (*tmp == NULL) {
        *out = 84;
        return 1;
    }
    return 0;
}

static void free_inc(char *tmp, int *s)
{
    free(tmp);
    ++(*s);
}

static char *read_stdin_buf(char **buffer, int *out, int err, int s)
{
    char *tmp = NULL;
    char buf[1] = {0};

    while (err > 0) {
        err = read(STDIN_FILENO, buf, 1);
        if (alloc_tmp(&s, out, &tmp))
            return *buffer;
        my_strcpy(tmp, *buffer);
        tmp[s] = buf[0];
        tmp[s + 1] = '\0';
        free(*buffer);
        *buffer = malloc(my_strlen(tmp) + 1);
        if (*buffer == NULL) {
            *out = 84;
            return tmp;
        }
        my_strcpy(*buffer, tmp);
        free_inc(tmp, &s);
    }
    return 0;
}

static int all_buffer(char **buffer)
{
    *buffer = malloc(1);
    if (*buffer == NULL)
        return 84;
    *buffer[0] = 0;
    return 0;
}

int fs_read_stdin(char **buffer)
{
    int err_t = 1;
    int s = 0;
    char *ret = 0;
    int err = 1;
    struct stat fstat_;

    err = stat("/dev/stdin", &fstat_);
    if (err == -1 || !S_ISFIFO(fstat_.st_mode))
        return 84;
    if (all_buffer(buffer))
        return 84;
    ret = read_stdin_buf(buffer, &err, err_t, s);
    if (ret)
        free(ret);
    if (err < 0) {
        free(buffer);
        return 84;
    }
    (*buffer)[my_strlen(*buffer) - 1] = '\0';
    return 0;
}
