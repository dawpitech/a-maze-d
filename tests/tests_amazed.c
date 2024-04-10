/*
** EPITECH PROJECT, 2024
** a-maze-d
** File description:
** tests-parser.c
*/

#include "../include/a_maze_d.h"
#include "../include/file_utils.h"
#include "../include/dijkstra.h"
#include <criterion/criterion.h>
#include <fcntl.h>
#include <stdio.h>

Test(amazed, test_good_file) {
    freopen("./tests/good_file.txt", "r", stdin);
    int ac = 1;
    const char *av[2] = {"./amazed", NULL};
    cr_assert_eq(amazed(ac, av), 0);
}

