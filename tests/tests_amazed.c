/*
** EPITECH PROJECT, 2024
** a-maze-d
** File description:
** tests-parser.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fcntl.h>
#include <stdio.h>

#include "../include/a_maze_d.h"
#include "../include/file_utils.h"
#include "../include/dijkstra.h"

Test(amazed, test_good_file) {
    freopen("./tests/good_file.txt", "r", stdin);
    int ac = 1;
    const char *av[2] = {"./amazed", NULL};
    cr_assert_eq(amazed(ac, av), 0);
}

Test(amazed, test_good_moove, .init=cr_redirect_stdout) {
    freopen("./tests/good_file.txt", "r", stdin);
    int ac = 1;
    const char *av[2] = {"./amazed", NULL};
    amazed(ac, av);
    cr_assert_stdout_eq_str("#number_of_robots\n3\n#rooms\n##start\n4 34 11\n1 38 68\n2 90 81\n3 43 97\n4 51 97\n5 62 52\n6 84 48\n7 7 81\n8 80 46\n##end\n1 79 74\n#tunnels\n0-1\n0-3\n1-3\n2-3\n3-4\n#moves\nP1-3\nP1-1 P2-3\nP2-1 P3-3\nP3-1\n");
}