/*
** EPITECH PROJECT, 2024
** a-maze-d
** File description:
** tests-parser.c
*/

#include <criterion/criterion.h>
#include <fcntl.h>
#include <stdio.h>

#include "a_maze_d.h"
#include "file_utils.h"
#include "dijkstra.h"

Test(amazed, test_good_file) {
    freopen("./tests/good_file.txt", "r", stdin);
    int ac = 1;
    const char *av[2] = {"./amazed", NULL};
    cr_assert_eq(amazed(ac, av), 0);
}
