/*
** EPITECH PROJECT, 2024
** B-PSU-100-BDX-1-1-navy-antoine.candelon
** File description:
** main header
*/

#include "a_maze_d.h"
#include "file_utils.h"
#include "my_printf.h"
#include "dijkstra.h"
#include "parser.h"
#include <stdint.h>
#include <stdlib.h>

static void show_route(route_t *route)
{
    if (route->weight != INT32_MAX) {
        my_printf("Route -> ");
        for (int i = 0; i <= (int) route->weight; i++)
            my_printf("%d ", route->nodes[i]);
    }
}

int amazed(__attribute__((unused)) int argc,
    __attribute__((unused)) char const **argv)
{
    char *buffer = NULL;
    maze_t *maze = NULL;
    route_t *route = NULL;
    unsigned int r = 0;

    if (fs_read_stdin(&buffer) || fs_get_number_from_first_line(buffer, &r))
        return EXIT_FAILURE_TECH;
    maze = parser_get_maze(buffer, r);
    if (maze == NULL || maze->matrix == NULL)
        return EXIT_FAILURE_TECH;
    route = dijkstra(maze, maze->starts[0], maze->ends[0]);
    if (route == NULL)
        return EXIT_FAILURE_TECH;
    show_route(route);
    free(buffer);
    free_maze(maze);
    free_route(route);
    return EXIT_SUCCESS_TECH;
}
