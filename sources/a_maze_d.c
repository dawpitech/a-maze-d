/*
** EPITECH PROJECT, 2024
** B-PSU-100-BDX-1-1-navy-antoine.candelon
** File description:
** main header
*/

#include <limits.h>
#include <stdbool.h>
#include <malloc.h>

#include "a_maze_d.h"

static
dijkstra_utils_t *init_dijkstra_utils(int size)
{
    dijkstra_utils_t *d = malloc(sizeof(dijkstra_utils_t));

    d->dst_frm_src = malloc(sizeof(int) * size);
    d->prev = malloc(sizeof(int) * size);
    d->vst = malloc(sizeof(bool) * size);
    for (int i = 0; i < size; i++) {
        d->dst_frm_src[i] = INT_MAX;
        d->prev[i] = NO_PREV;
        d->vst[i] = false;
    }
    return d;
}

static
int search_nearest_node(maze_t *maze, dijkstra_utils_t *d)
{
    int min_distance_node = -1;

    for (int index = 0; index < maze->matrix_size; index++) {
        if (d->vst[index])
            continue;
        if (min_distance_node == -1 ||
            d->dst_frm_src[index] < d->dst_frm_src[min_distance_node])
            min_distance_node = index;
    }
    return min_distance_node;
}

static
int route_weight(maze_t *maze, int node, dijkstra_utils_t *d, int idx)
{
    return d->dst_frm_src[node] + maze->matrix[node][idx];
}

static
void update_linked_nodes(maze_t *maze, int node, dijkstra_utils_t *d) {
    for (int index = 0; index < maze->matrix_size; index++) {
        if (d->vst[index] || maze->matrix[node][index] == NO_LINKS_TO_NODE)
            continue;
        if (d->dst_frm_src[node] == NODE_IS_ITSELF)
            continue;
        if (route_weight(maze, node, d, index) < d->dst_frm_src[index]) {
            d->dst_frm_src[index] = route_weight(maze, node, d, index);
            d->prev[index] = node;
        }
    }
}

static
route_t *dijkstra(maze_t *maze, int source, int destination)
{
    dijkstra_utils_t *d = init_dijkstra_utils((int) maze->matrix_size);
    route_t *route = malloc(sizeof(route_t));
    int min_distance_node;

    if (d == NULL || route == NULL)
        return NULL;
    d->dst_frm_src[source] = 0;
    for (int count = 0; count < maze->matrix_size - 1; count++) {
        min_distance_node = search_nearest_node(maze, d);
        d->vst[min_distance_node] = true;
        update_linked_nodes(maze, min_distance_node, d);
    }
    route->weight = d->dst_frm_src[destination];
    route->nodes = malloc(sizeof(int) * (route->weight + 1));
    for (int idx = 0; idx < (int) route->weight; idx++) {
        printf("Idx: %d, value: %d\n", idx, d->prev[destination]);
        route->nodes[idx] = d->prev[destination];
        destination = d->prev[destination];
    }
    printf("Idx: %d, value: %d\n", route->weight, destination);
    route->nodes[route->weight - 1] = destination;
    printf("\n");
    return route;
}

int amazed(int argc, char const **argv)
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
