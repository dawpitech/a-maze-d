/*
** EPITECH PROJECT, 2024
** parser
** File description:
** title
*/

#include "parser.h"
#include "a_maze_d.h"
#include "my.h"
#include "my_printf.h"
#include <stdio.h>
#include <stdlib.h>

void free_maze(maze_t *maze)
{
    for (int i = 0; i < maze->matrix_size; i++)
        free(maze->matrix[i]);
    free(maze->matrix);
    free(maze->starts);
    free(maze->ends);
    free(maze);
}

static void populate_matrix(maze_t *maze, int n1, int n2)
{
    if (maze->matrix != NULL) {
        maze->matrix[n1][n2] = 1;
        maze->matrix[n2][n1] = 1;
        return;
    }
    maze->matrix = malloc(sizeof(int *) * (maze->matrix_size + 1));
    my_memset(maze->matrix, 0, sizeof(int *) * (maze->matrix_size + 1));
    for (int i = 0; i < (maze->matrix_size + 1); i++) {
        maze->matrix[i] = malloc(sizeof(int) * (maze->matrix_size + 1));
        my_memset(maze->matrix[i], 0, sizeof(int) * (maze->matrix_size + 1));
        maze->matrix[i][i] = -1;
    }
    populate_matrix(maze, n1, n2);
}

static int print_tun(void)
{
    static int tun = 0;

    if (tun == 0) {
        my_printf("#tunnels\n");
        tun++;
    }
    return 0;
}

static int check_mat_line(maze_t *maze, char *buffer)
{
    int i = 0;
    int j = 0;
    int n1 = 0;
    int n2 = 0;

    for (; buffer[i] != '\0' && buffer[i] != '-'; i++)
        if (!IS_NUM(buffer[i]))
            return 1;
    n1 = -my_getnbr(buffer - i + 1);
    j = i;
    if (buffer[i] != '-')
        return 1;
    for (i = i + 1; buffer[i] != '\0' && buffer[i] != '\n'; i++)
        if (!IS_NUM(buffer[i]))
            return 1;
    n2 = -my_getnbr(&buffer[j]);
    populate_matrix(maze, n1, n2);
    return print_tun();
}

static int check_coords_line(char *buffer)
{
    int i = 0;

    for (; buffer[i] != '\0' && buffer[i] != ' ' && buffer[i] != '\n'; i++)
        if (!IS_NUM(buffer[i]))
            return 1;
    if (buffer[i] != ' ')
        return 1;
    for (; buffer[i] != '\0' && buffer[i] != ' ' && buffer[i] != '\n'; i++)
        if (!IS_NUM(buffer[i]))
            return 1;
    if (buffer[i] != ' ')
        return 1;
    for (; buffer[i] != '\0' && buffer[i] != ' ' && buffer[i] != '\n'; i++)
        if (!IS_NUM(buffer[i]))
            return 1;
    return i == 0;
}

static int get_start_end(maze_t *maze, char *buffer)
{
    if (my_strncmp(buffer, "##start\n", 8) == 0 &&
        !check_coords_line(&buffer[8])) {
        maze->starts = my_realloc(maze->starts,
            (maze->nstarts + 1) * sizeof(int), maze->nstarts * sizeof(int));
        maze->starts[maze->nstarts] = my_getnbr(&buffer[6]);
        maze->nstarts++;
        return 0;
    }
    if (my_strncmp(buffer, "##end\n", 6) == 0 &&
        !check_coords_line(&buffer[6])) {
        maze->ends = my_realloc(maze->ends, (maze->nends + 1) * sizeof(int),
                                maze->nends * sizeof(int));
        maze->ends[maze->nends] = my_getnbr(&buffer[6]);
        maze->nends++;
        return 0;
    }
    return 1;
}

static void print_line(char *buffer)
{
    int s = my_strstr(buffer, "\n") - buffer;
    char tmp[s];

    my_memset(tmp, 0, s);
    my_strncpy(tmp, buffer, s);
    tmp[s] = '\0';
    if (s >= 2 && tmp[0] == '#' && tmp[1] != '#')
        return;
    if (s >= 2 && tmp[0] != '#' && tmp[1] != '#' &&
        my_strstr(tmp, "#") != 0) {
        tmp[my_strstr(tmp, "#") - tmp - 1] = '\0';
    }
    my_printf("%s\n", tmp);
}

static int parse_lines(maze_t *maze, char *buffer)
{
    ++buffer;
    for (; *(buffer - 1) != '\n' && *buffer != '\0'; ++buffer);
    for (ssize_t i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '#' && buffer[i + 1] == '#')
            get_start_end(maze, &buffer[i]);
        if (buffer[i] == '#' || !check_mat_line(maze, &buffer[i])) {
            print_line(&buffer[i]);
            i = (my_strstr(&buffer[i], "\n") - buffer);
            continue;
        }
        if (check_coords_line(&buffer[i]))
            return 1;
        print_line(&buffer[i]);
        if (my_getnbr_long(&buffer[i]) > maze->matrix_size)
            maze->matrix_size = my_getnbr_long(&buffer[i]);
        i = (my_strstr(&buffer[i], "\n") - buffer);
    }
    return 0;
}

maze_t *parser_get_maze(char *buffer, unsigned int ants)
{
    maze_t *maze = malloc(sizeof(maze_t));

    if (buffer == NULL || maze == NULL)
        return NULL;
    my_memset(maze, 0, sizeof(maze_t));
    my_printf("#number_of_robots\n%d\n#rooms\n", ants);
    for (int i = 0; buffer[i] != '\0' && buffer[i] != '\n'; i++)
        if (buffer[i] == '#')
            buffer = my_strstr(&buffer[i], "\n") + 1;
    if (parse_lines(maze, buffer))
        return NULL;
    maze->nrobots = ants;
    maze->matrix_size++;
    my_printf("#moves\n");
    return maze;
}
