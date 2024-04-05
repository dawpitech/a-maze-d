/*
** EPITECH PROJECT, 2024
** a-maze-d
** File description:
** dijkstra header
*/

#ifndef A_MAZE_D_DIJKSTRA_H
    #define A_MAZE_D_DIJKSTRA_H
    #include <stdbool.h>
    #include "a_maze_d.h"
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
route_t *dijkstra(maze_t *maze, int source, int destination);
#endif //A_MAZE_D_DIJKSTRA_H
