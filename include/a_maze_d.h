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
typedef struct {
    unsigned int nrobots;
    ssize_t matrix_size;
    int **matrix;
    int *starts;
    int *ends;
} maze_t;
int amazed(__attribute__((unused)) int argc, __attribute__((unused)) char const **argv);
#endif //A_MAZE_D_A_MAZE_D_H
