/*
** EPITECH PROJECT, 2024
** a-maze-d
** File description:
** tests_parser.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fcntl.h>
#include <stdio.h>

#include "../include/a_maze_d.h"
#include "../include/parser.h"
#include "../include/file_utils.h"

Test(parser, test_fs_get_number_from_first_line) {
    char buffer[] = "3\n##start\n4 34 11\n1 38 68\n2 90 81 #room\n3 43 97\n4 51 97\n#comment\n5 62 52\n6 84 48\n7 7 81\n8 80 46\n##end\n1 79 74\n0-1\n0-3\n1-3\n2-4\n2-3\n3-4\n";
    unsigned int r = 0;

    fs_get_number_from_first_line(buffer, &r);
    cr_assert_eq(r, 3);
}

Test(parser, test_fs_get_number_from_first_line_with_number_neg, .init=cr_redirect_stderr) {
    char buffer[] = "-3\n##start\n4 34 11\n1 38 68\n2 90 81 #room\n3 43 97\n4 51 97\n#comment\n5 62 52\n6 84 48\n7 7 81\n8 80 46\n##end\n1 79 74\n0-1\n0-3\n1-3\n2-4\n2-3\n3-4\n";
    unsigned int r = 0;

    cr_expect_eq(fs_get_number_from_first_line(buffer, &r), 84);
    cr_assert_stderr_eq_str("bad number of ants.\n");
}
