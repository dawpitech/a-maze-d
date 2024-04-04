/*
** EPITECH PROJECT, 2024
** B-PSU-100-BDX-1-1-navy-antoine.candelon
** File description:
** main header
*/

#include "a_maze_d.h"
#include "dijkstra.h"

int amazed(__attribute__((unused)) int argc,
    __attribute__((unused)) char const **argv)
{
    maze_t maze = {
            .nrobots = 4,
            .matrix_size = 5,
            .matrix = (int *[]) {(int []) {-1, 1, 0, 1, 0},
                                 (int []) {1, -1, 0, 1, 0},
                                 (int []) {0, 0, -1, 1, 1},
                                 (int []) {1, 1, 1, -1, 1},
                                 (int []) {0, 0, 1, 1, -1}},
            .starts = (int []){4},
            .ends = (int []){1}
    };

    printf("From %d to %d\n", maze.starts[0], maze.ends[0]);
    route_t *route = dijkstra(&maze, maze.starts[0], maze.ends[0]);
    if (route == NULL)
        return EXIT_FAILURE_TECH;
    printf("Weight of the route -> %d\n", route->weight);
    printf("Route -> ");
    for (int i = 0; i <= (int) route->weight; i++)
        printf("%d ", route->nodes[i]);
    printf("\n");
    return EXIT_SUCCESS_TECH;
}
