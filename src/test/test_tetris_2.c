#include "test.h"

START_TEST(test_tetris_1) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  point.number_now_f = 0;
  int I_figure[4][4] = {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      tetris.now[i][j] = I_figure[i][j];
    }
  }

  point.current_pos_x = COLUMNS - 2;
  point.current_pos_y = 0;

  rotate_figure(&tetris, &point);

  ck_assert_int_ge(point.current_pos_x, 0);
  ck_assert_int_lt(point.current_pos_x, COLUMNS);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_2) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  tetris.field[2][4] = 1;
  tetris.field[2][5] = 1;

  point.number_now_f = 5;
  int T_figure[4][4] = {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      tetris.now[i][j] = T_figure[i][j];
    }
  }

  point.current_pos_x = 3;
  point.current_pos_y = 0;

  rotate_figure(&tetris, &point);

  ck_assert_int_ge(point.current_pos_x, 0);
  ck_assert_int_lt(point.current_pos_x, COLUMNS);
  ck_assert_int_ge(point.current_pos_y, 0);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_3) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  point.number_now_f = 4;
  int S_figure[4][4] = {{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

  int original_figure[4][4];
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      tetris.now[i][j] = S_figure[i][j];
      original_figure[i][j] = S_figure[i][j];
    }
  }

  point.current_pos_x = 3;
  point.current_pos_y = ROWS - 2;

  int size = 3;
  int tmp[size][size];
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      tmp[j][i] = tetris.now[i][j];
    }
  }
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      tetris.now[i][j] = tmp[i][size - j - 1];
    }
  }

  int old_y = point.current_pos_y;

  try_standard_wall_kick(&tetris, &point, original_figure);

  ck_assert_int_lt(point.current_pos_y, old_y);
  ck_assert_int_eq(collision(&tetris, &point), 0);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_4) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  point.number_now_f = 5;
  int T_figure[4][4] = {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

  int original_figure[4][4];
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      tetris.now[i][j] = T_figure[i][j];
      original_figure[i][j] = T_figure[i][j];
    }
  }

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      tetris.field[i][j] = 1;
    }
  }

  point.current_pos_x = 3;
  point.current_pos_y = 3;

  int old_x = point.current_pos_x;
  int old_y = point.current_pos_y;

  int size = 3;
  int tmp[size][size];
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      tmp[j][i] = tetris.now[i][j];
    }
  }
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      tetris.now[i][j] = tmp[i][size - j - 1];
    }
  }

  try_standard_wall_kick(&tetris, &point, original_figure);

  ck_assert_int_eq(point.current_pos_x, old_x);
  ck_assert_int_eq(point.current_pos_y, old_y);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_int_eq(tetris.now[i][j], original_figure[i][j]);
    }
  }

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_5) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  point.number_now_f = 0;
  int I_figure[4][4] = {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};

  int original_figure[4][4];
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      tetris.now[i][j] = I_figure[i][j];
      original_figure[i][j] = I_figure[i][j];
    }
  }

  int tmp[4][4];
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      tmp[j][i] = tetris.now[i][j];
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      tetris.now[i][j] = tmp[i][4 - j - 1];
    }
  }

  point.current_pos_x = COLUMNS - 2;
  point.current_pos_y = 0;

  for (int dx = -3; dx <= 3; dx++) {
    for (int dy = -2; dy <= 2; dy++) {
      if (dx != -2) {
        int test_x = point.current_pos_x + dx;
        int test_y = point.current_pos_y + dy;
        if (test_x >= 0 && test_x < COLUMNS && test_y >= 0 && test_y < ROWS) {
          tetris.field[test_y][test_x] = 1;
        }
      }
    }
  }

  try_I_figure_wall_kick(&tetris, &point, original_figure);

  ck_assert_int_eq(point.current_pos_x, 8);
  ck_assert_int_eq(collision(&tetris, &point), 1);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_6) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  point.number_now_f = 0;
  int I_figure[4][4] = {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};

  int original_figure[4][4];
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      tetris.now[i][j] = I_figure[i][j];
      original_figure[i][j] = I_figure[i][j];
    }
  }

  int tmp[4][4];
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      tmp[j][i] = tetris.now[i][j];
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      tetris.now[i][j] = tmp[i][4 - j - 1];
    }
  }

  point.current_pos_x = 1;
  point.current_pos_y = 0;

  for (int dx = -3; dx <= 3; dx++) {
    for (int dy = -2; dy <= 2; dy++) {
      if (dx != 2) {
        int test_x = point.current_pos_x + dx;
        int test_y = point.current_pos_y + dy;
        if (test_x >= 0 && test_x < COLUMNS && test_y >= 0 && test_y < ROWS) {
          tetris.field[test_y][test_x] = 1;
        }
      }
    }
  }

  try_I_figure_wall_kick(&tetris, &point, original_figure);

  ck_assert_int_eq(point.current_pos_x, 4);
  ck_assert_int_eq(collision(&tetris, &point), 0);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_7) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  point.number_now_f = 0;
  int I_figure[4][4] = {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};

  int original_figure[4][4];
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      tetris.now[i][j] = I_figure[i][j];
      original_figure[i][j] = I_figure[i][j];
    }
  }

  int tmp[4][4];
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      tmp[j][i] = tetris.now[i][j];
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      tetris.now[i][j] = tmp[i][4 - j - 1];
    }
  }

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      tetris.field[i][j] = 1;
    }
  }

  point.current_pos_x = 3;
  point.current_pos_y = 3;

  int old_x = point.current_pos_x;
  int old_y = point.current_pos_y;

  try_I_figure_wall_kick(&tetris, &point, original_figure);

  ck_assert_int_eq(point.current_pos_x, old_x);
  ck_assert_int_eq(point.current_pos_y, old_y);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_int_eq(tetris.now[i][j], original_figure[i][j]);
    }
  }

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_8) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  point.number_now_f = 0;
  int I_figure[4][4] = {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};

  int original_figure[4][4];
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      tetris.now[i][j] = I_figure[i][j];
      original_figure[i][j] = I_figure[i][j];
    }
  }

  int tmp[4][4];
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      tmp[j][i] = tetris.now[i][j];
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      tetris.now[i][j] = tmp[i][4 - j - 1];
    }
  }

  point.current_pos_x = 1;
  point.current_pos_y = 2;

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      tetris.field[i][j] = 1;
    }
  }

  int old_x = point.current_pos_x;
  int old_y = point.current_pos_y;

  try_I_figure_wall_kick(&tetris, &point, original_figure);

  ck_assert_int_eq(point.current_pos_x, old_x);
  ck_assert_int_eq(point.current_pos_y, old_y);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_int_eq(tetris.now[i][j], original_figure[i][j]);
    }
  }

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_9) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      tetris.field[i][j] = (j % 2 == 0 && i % 2 == 0) ? 1 : 0;
    }
  }

  int removed_count = remove_row(&tetris);

  ck_assert_int_eq(removed_count, 0);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_10) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  for (int j = 0; j < COLUMNS; j++) {
    tetris.field[ROWS - 1][j] = 1;
  }

  tetris.field[ROWS - 2][3] = 1;
  tetris.field[ROWS - 2][4] = 1;

  int removed_count = remove_row(&tetris);

  ck_assert_int_eq(removed_count, 1);

  ck_assert_int_eq(tetris.field[ROWS - 1][3], 1);
  ck_assert_int_eq(tetris.field[ROWS - 1][4], 1);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_11) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  scoring_point(&tetris, 1);
  ck_assert_int_eq(tetris.score, 100);

  scoring_point(&tetris, 2);
  ck_assert_int_eq(tetris.score, 400);

  scoring_point(&tetris, 3);
  ck_assert_int_eq(tetris.score, 1100);

  scoring_point(&tetris, 4);
  ck_assert_int_eq(tetris.score, 2600);

  scoring_point(&tetris, 5);
  ck_assert_int_eq(tetris.score, 2600);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_12) {
  GameInfo_t tetris = {0};

  tetris.score = 500;
  tetris.level = 1;
  tetris.speed = 1000;

  increase_level(&tetris);

  ck_assert_int_eq(tetris.level, 1);
  ck_assert_int_eq(tetris.speed, 1000);
}
END_TEST

START_TEST(test_tetris_13) {
  GameInfo_t tetris = {0};

  tetris.score = 600;
  tetris.level = 1;
  tetris.speed = 1000;

  increase_level(&tetris);

  ck_assert_int_eq(tetris.level, 2);
  ck_assert_int_eq(tetris.speed, 900);
}
END_TEST

START_TEST(test_tetris_14) {
  GameInfo_t tetris = {0};

  tetris.score = 1800;
  tetris.level = 1;
  tetris.speed = 1000;

  increase_level(&tetris);

  ck_assert_int_eq(tetris.level, 4);
  ck_assert_int_eq(tetris.speed, 700);
}
END_TEST

START_TEST(test_tetris_15) {
  GameInfo_t tetris = {0};

  tetris.score = 10000;
  tetris.level = MAX_LEVEL;
  tetris.speed = 100;

  increase_level(&tetris);

  ck_assert_int_eq(tetris.level, MAX_LEVEL);
  ck_assert_int_eq(tetris.speed, 100);
}
END_TEST

START_TEST(test_tetris_16) {
  GameInfo_t tetris = {0};

  tetris.score = 10000;
  increase_level(&tetris);
  ck_assert_int_eq(tetris.level, MAX_LEVEL);
}
END_TEST

START_TEST(test_tetris_17) {
  GameInfo_t tetris = {0};

  tetris.score = 1500;
  tetris.high_score = 1000;

  save_high_score(&tetris);

  ck_assert_int_eq(tetris.high_score, 1500);

  FILE *file = fopen("high_score_tetris.txt", "r");
  if (file) {
    int file_score;
    fscanf(file, "%d", &file_score);
    fclose(file);
    ck_assert_int_eq(file_score, 1500);
  }
}
END_TEST

START_TEST(test_tetris_18) {
  GameInfo_t tetris = {0};

  FILE *file_init = fopen("high_score_tetris.txt", "w");
  if (file_init) {
    fprintf(file_init, "%d", 2000);
    fclose(file_init);
  }

  tetris.score = 1500;
  tetris.high_score = 2000;

  save_high_score(&tetris);

  ck_assert_int_eq(tetris.high_score, 2000);

  FILE *file = fopen("high_score_tetris.txt", "r");
  if (file) {
    int file_score;
    fscanf(file, "%d", &file_score);
    fclose(file);
    ck_assert_int_eq(file_score, 2000);
  }
}
END_TEST

START_TEST(test_tetris_19) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  state = SPAWN;
  point.number_next_f = 0;

  state_game(&tetris, &state, &point);

  ck_assert_int_eq(point.current_pos_x, 3);
  ck_assert_int_eq(point.current_pos_y, -1);
  ck_assert_int_ge(point.prev_time, 0);
  ck_assert(state == SHIFTING || state == GAME_OVER);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_20) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  state = SPAWN;
  point.number_next_f = 1;

  state_game(&tetris, &state, &point);

  ck_assert_int_eq(point.current_pos_x, 3);
  ck_assert_int_eq(point.current_pos_y, 0);
  ck_assert_int_ge(point.prev_time, 0);
  ck_assert(state == SHIFTING || state == GAME_OVER);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_21) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  state = SPAWN;

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      tetris.field[i][j] = 1;
    }
  }

  point.number_next_f = 1;

  state_game(&tetris, &state, &point);
  ck_assert_int_eq(state, GAME_OVER);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_22) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  state = SHIFTING;

  point.current_pos_x = 3;
  point.current_pos_y = 0;
  point.prev_time = time_in_millisec() - 2000;
  copy_figures(&tetris, &point);

  state_game(&tetris, &state, &point);
  ck_assert(state == SHIFTING || state == ATTACHING);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_23) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  state = MOVING_LEFT;
  point.current_pos_x = 5;
  point.current_pos_y = 3;
  copy_figures(&tetris, &point);
  state_game(&tetris, &state, &point);

  ck_assert_int_eq(state, SHIFTING);
  ck_assert_int_ge(point.current_pos_x, 0);
  ck_assert_int_lt(point.current_pos_x, COLUMNS);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_24) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  state = MOVING_RIGHT;
  point.current_pos_x = 3;
  point.current_pos_y = 3;
  copy_figures(&tetris, &point);
  state_game(&tetris, &state, &point);

  ck_assert_int_eq(state, SHIFTING);
  ck_assert_int_ge(point.current_pos_x, 0);
  ck_assert_int_lt(point.current_pos_x, COLUMNS);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_25) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  state = MOVING_DOWN;
  point.current_pos_x = 3;
  point.current_pos_y = 3;
  copy_figures(&tetris, &point);

  int old_y = point.current_pos_y;

  state_game(&tetris, &state, &point);
  ck_assert_int_eq(state, SHIFTING);
  ck_assert_int_ge(point.current_pos_y, old_y);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_26) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  state = MOVING_ROTATE;
  point.number_now_f = 1;
  point.current_pos_x = 3;
  point.current_pos_y = 3;
  copy_figures(&tetris, &point);

  int original_figure[4][4];
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      original_figure[i][j] = tetris.now[i][j];
    }
  }

  state_game(&tetris, &state, &point);
  ck_assert_int_eq(state, SHIFTING);

  int changed = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetris.now[i][j] != original_figure[i][j]) {
        changed = 1;
        break;
      }
    }
    if (changed) break;
  }

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_27) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  state = ATTACHING;
  tetris.score = 100;
  tetris.level = 1;
  tetris.high_score = 0;

  for (int i = ROWS - 3; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      if (j % 2 == 0) {
        tetris.field[i][j] = 1;
      }
    }
  }

  point.current_pos_x = 3;
  point.current_pos_y = ROWS - 4;
  copy_figures(&tetris, &point);

  int old_score = tetris.score;
  int old_level = tetris.level;

  state_game(&tetris, &state, &point);

  ck_assert_int_eq(state, SPAWN);
  ck_assert_int_eq(tetris.score, old_score);
  ck_assert_int_eq(tetris.level, old_level);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_28) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  state_game(&tetris, &state, &point);
  state = EXIT;

  ck_assert_int_eq(state, EXIT);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_29) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  state = SHIFTING;
  tetris.score = 500;
  tetris.high_score = 1000;
  tetris.level = 2;
  tetris.speed = 900;

  copy_figures(&tetris, &point);
  point.current_pos_x = 3;
  point.current_pos_y = 5;

  tetris.field[10][5] = 1;
  tetris.field[11][6] = 1;

  update_game(&tetris, &state, &point);

  GameInfo_t *info = getGameInfo();

  ck_assert_ptr_nonnull(info);
  ck_assert_ptr_eq(info->field, tetris.field);
  ck_assert_int_eq(info->score, 500);
  ck_assert_int_eq(info->high_score, 1000);
  ck_assert_int_eq(info->level, 2);
  ck_assert_int_eq(info->speed, 900);
  ck_assert_ptr_nonnull(info->next);

  free_gameinfo(info);
  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_30) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  state = GAME_OVER;
  tetris.score = 1500;
  tetris.high_score = 2000;
  tetris.level = 3;
  tetris.speed = 800;

  copy_figures(&tetris, &point);
  update_game(&tetris, &state, &point);

  GameInfo_t *info = getGameInfo();

  ck_assert_ptr_nonnull(info);
  ck_assert_ptr_eq(info->field, tetris.field);
  ck_assert_int_eq(info->score, 1500);
  ck_assert_int_eq(info->high_score, 2000);
  ck_assert_int_eq(info->level, 3);
  ck_assert_int_eq(info->speed, 800);
  ck_assert_ptr_nonnull(info->next);

  free_gameinfo(info);
  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_31) {
  GameInfo_t tetris = {0};

  FILE *file_init = fopen("high_score_tetris.txt", "w");
  ck_assert_ptr_nonnull(file_init);
  if (file_init) {
    fprintf(file_init, "invalid_data");
    fclose(file_init);
  }

  create_matrix(&tetris);

  ck_assert_int_eq(tetris.high_score, 0);

  remove_matrix(&tetris);
}
END_TEST

Suite *test_tetris_function(void) {
  Suite *s = suite_create("Test tetris function");
  TCase *tc_tetris = tcase_create("s21_tetris");

  tcase_add_test(tc_tetris, test_tetris_1);
  tcase_add_test(tc_tetris, test_tetris_2);
  tcase_add_test(tc_tetris, test_tetris_3);
  tcase_add_test(tc_tetris, test_tetris_4);
  tcase_add_test(tc_tetris, test_tetris_5);
  tcase_add_test(tc_tetris, test_tetris_6);
  tcase_add_test(tc_tetris, test_tetris_7);
  tcase_add_test(tc_tetris, test_tetris_8);
  tcase_add_test(tc_tetris, test_tetris_9);
  tcase_add_test(tc_tetris, test_tetris_10);
  tcase_add_test(tc_tetris, test_tetris_11);
  tcase_add_test(tc_tetris, test_tetris_12);
  tcase_add_test(tc_tetris, test_tetris_13);
  tcase_add_test(tc_tetris, test_tetris_14);
  tcase_add_test(tc_tetris, test_tetris_15);
  tcase_add_test(tc_tetris, test_tetris_16);
  tcase_add_test(tc_tetris, test_tetris_17);
  tcase_add_test(tc_tetris, test_tetris_18);
  tcase_add_test(tc_tetris, test_tetris_19);
  tcase_add_test(tc_tetris, test_tetris_20);
  tcase_add_test(tc_tetris, test_tetris_21);
  tcase_add_test(tc_tetris, test_tetris_22);
  tcase_add_test(tc_tetris, test_tetris_23);
  tcase_add_test(tc_tetris, test_tetris_24);
  tcase_add_test(tc_tetris, test_tetris_25);
  tcase_add_test(tc_tetris, test_tetris_26);
  tcase_add_test(tc_tetris, test_tetris_27);
  tcase_add_test(tc_tetris, test_tetris_28);
  tcase_add_test(tc_tetris, test_tetris_29);
  tcase_add_test(tc_tetris, test_tetris_30);
  tcase_add_test(tc_tetris, test_tetris_31);

  suite_add_tcase(s, tc_tetris);
  return s;
}