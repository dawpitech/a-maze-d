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
    freopen("./tests/file_tests/good_file.txt", "r", stdin);
    int ac = 1;
    const char *av[2] = {"./amazed", NULL};
    cr_assert_eq(amazed(ac, av), 0);
}

Test(amazed, test_with_file_neg_number) {
    freopen("./tests/file_tests/number_neg.txt", "r", stdin);
    int ac = 1;
    const char *av[2] = {"./amazed", NULL};
    cr_assert_eq(amazed(ac, av), 84);
}

Test(amazed, test_good_moove, .init=cr_redirect_stdout) {
    freopen("./tests/file_tests/pdf_example", "r", stdin);
    int ac = 1;
    const char *av[2] = {"./amazed", NULL};
    amazed(ac, av);
    cr_assert_stdout_eq_str("#number_of_robots\n3\n#rooms\n2 5 0\n##start\n0 1 2\n##end\n1 9 2\n3 5 4\n#tunnels\n0-2\n0-3\n2-1\n3-1\n2-3\n#moves\nP1-2\nP1-1 P2-2\nP2-1 P3-2\nP3-1\n");
}

Test(amazed, test_stdout_empty_file, .init=cr_redirect_stdout) {
    freopen("./tests/file_tests/empty_file.txt", "r", stdin);
    int ac = 1;
    const char *av[2] = {"./amazed", NULL};
    amazed(ac, av);
    cr_assert_stdout_eq_str("#number_of_robots\n0\n#rooms\n#moves\n");
}

Test(amazed, test_file_witout_start) {
    freopen("./tests/file_tests/no_start.txt", "r", stdin);
    int ac = 1;
    const char *av[2] = {"./amazed", NULL};
    cr_assert_eq(amazed(ac, av), 84);
}

Test(amazed, test_file_witout_end) {
    freopen("./tests/file_tests/no_end.txt", "r", stdin);
    int ac = 1;
    const char *av[2] = {"./amazed", NULL};
    cr_assert_eq(amazed(ac, av), 84);
}

Test(amazed, test_file_witout_matrix) {
    freopen("./tests/file_tests/no_matrix.txt", "r", stdin);
    int ac = 1;
    const char *av[2] = {"./amazed", NULL};
    cr_assert_eq(amazed(ac, av), 84);
}

