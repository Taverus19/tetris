#ifndef TEST_H
#define TEST_H

#include <check.h>

#include "../brick_game/tetris/tetris.h"

#define YELLOW "\x1B[33m"
#define RESET "\x1B[0m"

Suite *test_tetris(void);
Suite *test_tetris_function(void);

#endif