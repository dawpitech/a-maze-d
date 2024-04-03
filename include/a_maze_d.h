/*
** EPITECH PROJECT, 2024
** a-maze-d
** File description:
** a-maze-d header
*/

#ifndef A_MAZE_D_A_MAZE_D_H
    #define A_MAZE_D_A_MAZE_D_H
    #include <stdio.h>
    #define EXIT_FAILURE_TECH 84
    #define EXIT_SUCCESS_TECH 0

    #define NO_PREV (-1)
    #define NODE_IS_ITSELF (-1)
    #define NO_LINKS_TO_NODE 0
typedef struct {
    int *dst_frm_src;
    int *prev;
    bool *vst;
} dijkstra_utils_t;
typedef struct {
    unsigned int weight;
    int *nodes;
} route_t;
typedef struct {
    unsigned int nrobots;
    ssize_t matrix_size;
    int **matrix;
    int *starts;
    int *ends;
} maze_t;

int amazed(int argc, char const **argv);
#endif //A_MAZE_D_A_MAZE_D_H
