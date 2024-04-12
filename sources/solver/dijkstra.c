/*
** EPITECH PROJECT, 2024
** a-maze-d
** File description:
** dijkstra header
*/

#include <malloc.h>
#include <limits.h>

#include "dijkstra.h"

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
void update_linked_nodes(maze_t *maze, int node, dijkstra_utils_t *d)
{
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

void free_route(route_t *route)
{
    free(route->nodes);
    free(route);
}

static
void destroy_dijkstra_utils(dijkstra_utils_t *d)
{
    free(d->dst_frm_src);
    free(d->prev);
    free(d->vst);
    free(d);
}

static
route_t *generate_route(int destination, dijkstra_utils_t *d)
{
    route_t *route = malloc(sizeof(route_t));

    if (route == NULL || d->prev[destination] == NO_PREV)
        return NULL;
    if (route->weight == 0)
        return NULL;
    route->weight = d->dst_frm_src[destination];
    route->nodes = malloc(sizeof(int) * (route->weight + 1));
    route->nodes[route->weight] = destination;
    for (int idx = 0; idx < (int) route->weight; idx++) {
        route->nodes[route->weight - idx - 1] = d->prev[destination];
        destination = d->prev[destination];
    }
    destroy_dijkstra_utils(d);
    return route;
}

route_t *dijkstra(maze_t *maze, int source, int destination)
{
    dijkstra_utils_t *d = init_dijkstra_utils((int) maze->matrix_size);
    int min_distance_node;

    if (d == NULL)
        return NULL;
    d->dst_frm_src[source] = 0;
    for (int count = 0; count < maze->matrix_size - 1; count++) {
        min_distance_node = search_nearest_node(maze, d);
        d->vst[min_distance_node] = true;
        update_linked_nodes(maze, min_distance_node, d);
    }
    return generate_route(destination, d);
}
