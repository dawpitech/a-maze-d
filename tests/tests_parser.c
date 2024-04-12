/*
** EPITECH PROJECT, 2024
** a-maze-d
** File description:
** tests_parser.c
*/

#include <criterion/criterion.h>
#include <fcntl.h>
#include <stdio.h>

#include "../include/a_maze_d.h"
#include "../include/parser.h"
#include "../include/file_utils.h"

Test(parser, test_parser_with_good_buffer) {
    maze_t maze = {
            .nrobots = 3,
            .matrix_size = 9,
            .matrix = NULL,
            .starts = NULL,
            .ends = NULL,
            .nstarts = 1,
            .nends = 1,
    };
    maze.matrix = malloc(sizeof(int *) * 9);
    for (int i = 0; i != 9; i++)
        maze.matrix[i] = malloc(sizeof(int) * 9);
    maze.starts = malloc(sizeof(int) * 1);
    maze.starts[0] = 4;
    maze.ends = malloc(sizeof(int) * 1);
    maze.ends[0] = 1;
    maze.matrix = (int *[]) {
            (int[]) {-1, 1, 0, 1, 0, 0, 0, 0, 0},
            (int[]) {1, -1, 0, 1, 0, 0, 0, 0, 0},
            (int[]) {0, 0, -1, 1, 1, 0, 0, 0, 0},
            (int[]) {1, 1, 1, -1, 1, 0, 0, 0, 0},
            (int[]) {0, 0, 1, 1, -1, 0, 0, 0, 0},
            (int[]) {0, 0, 0, 0, 0, -1, 0, 0, 0},
            (int[]) {0, 0, 0, 0, 0, 0, -1, 0, 0},
            (int[]) {0, 0, 0, 0, 0, 0, 0, -1, 0},
            (int[]) {0, 0, 0, 0, 0, 0, 0, 0, -1}};
    int r = 3;
    char *buffer = malloc(sizeof(char) * 137);
    buffer = "3\n##start\n4 34 11\n1 38 68\n2 90 81 #room\n3 43 97\n4 51 97\n#comment\n5 62 52\n6 84 48\n7 7 81\n8 80 46\n##end\n1 79 74\n0-1\n0-3\n1-3\n2-4\n2-3\n3-4\n";
    maze_t *maze_func = parser_get_maze(buffer, r);
    for (int i = 0; i != 9; i++)
        for (int j = 0; j != 9; j++)
            cr_expect_eq(maze_func->matrix[i][j], maze.matrix[i][j]);
    cr_expect_eq(maze_func->matrix_size, maze.matrix_size);
    cr_expect_eq(maze_func->nstarts, maze.nstarts);
    cr_expect_eq(maze_func->nends, maze.nends);
    cr_expect_eq(maze_func->starts[0], maze.starts[0]);
    cr_expect_eq(maze_func->ends[0], maze.ends[0]);
    cr_assert_eq(maze_func->nrobots, maze.nrobots);
}

Test(parser, test_parser_with_empty_buffer) {
    char *buffer = NULL;
    int r = 0;
    cr_assert_null(parser_get_maze(buffer, r));
}

