#include "test.h"

START_TEST(test_tetris_1) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  ck_assert_ptr_nonnull(tetris.field);
  ck_assert_ptr_nonnull(tetris.next);
  ck_assert_ptr_nonnull(tetris.now);
  ck_assert_int_eq(tetris.score, 0);
  ck_assert_int_eq(state, START);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_2) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  ck_assert_int_eq(tetris.score, 0);
  ck_assert_int_eq(tetris.high_score, 0);
  ck_assert_int_eq(tetris.level, 1);
  ck_assert_int_eq(tetris.speed, 1000);
  ck_assert_int_eq(tetris.pause, 0);
  ck_assert_int_eq(state, START);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_3) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  generate_rand_figure(&tetris, &point);
  ck_assert_int_ge(point.number_next_f, 0);

  copy_figures(&tetris, &point);
  point.current_pos_x = 3;
  point.current_pos_y = 0;

  int collide = collision(&tetris, &point);
  ck_assert_int_eq(collide, 0);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_4) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  copy_figures(&tetris, &point);
  point.current_pos_x = 3;
  point.current_pos_y = 0;

  int res = collision(&tetris, &point);
  ck_assert_int_eq(res, 0);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_5) {
  long long time = time_in_millisec();
  ck_assert_int_ge(time, 0);
}
END_TEST

START_TEST(test_tetris_6) {
  GameInfo_t tetris;
  GameState_t state;
  Tag_point_t point;

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  tetris.score = 1000;
  tetris.level = 5;
  reset_game(&tetris, &state, &point);

  ck_assert_int_eq(tetris.score, 0);
  ck_assert_int_eq(tetris.level, 1);
  ck_assert_int_eq(tetris.speed, 1000);
  ck_assert_int_eq(state, START);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_7) {
  int **test_arr = malloc(2 * sizeof(int *));
  test_arr[0] = malloc(3 * sizeof(int));
  test_arr[1] = malloc(3 * sizeof(int));

  test_arr[0][0] = 1;
  test_arr[0][1] = 1;
  test_arr[0][2] = 0;
  test_arr[1][0] = -1;
  test_arr[1][1] = -1;
  test_arr[1][2] = -1;

  int **converted = convert_matrix(test_arr, 1, 3, 0, 0);
  ck_assert_ptr_nonnull(converted);

  free_matrix(converted);
  free(test_arr[0]);
  free(test_arr[1]);
  free(test_arr);
}
END_TEST

START_TEST(test_tetris_8) {
  GameInfo_t *info = getGameInfo();

  info->pause = START;
  userInput(Start, false);
  ck_assert_int_eq(info->pause, SPAWN);

  info->pause = SHIFTING;
  userInput(Start, false);
  ck_assert_int_eq(info->pause, SHIFTING);

  info->pause = PAUSE;
  userInput(Start, false);
  ck_assert_int_eq(info->pause, PAUSE);

  info->pause = SHIFTING;
  userInput(Pause, false);
  ck_assert_int_eq(info->pause, PAUSE);

  info->pause = SHIFTING;
  userInput(Left, false);
  ck_assert_int_eq(info->pause, MOVING_LEFT);

  info->pause = SHIFTING;
  userInput(Left, true);
  ck_assert_int_eq(info->pause, SHIFTING);

  info->pause = SHIFTING;
  userInput(Right, false);
  ck_assert_int_eq(info->pause, MOVING_RIGHT);

  info->pause = SHIFTING;
  userInput(Right, true);
  ck_assert_int_eq(info->pause, SHIFTING);

  info->pause = SHIFTING;
  userInput(Down, false);
  ck_assert_int_eq(info->pause, MOVING_DOWN);

  info->pause = SHIFTING;
  userInput(Down, true);
  ck_assert_int_eq(info->pause, MOVING_DOWN);

  info->pause = SHIFTING;
  userInput(Action, false);
  ck_assert_int_eq(info->pause, MOVING_ROTATE);

  info->pause = SHIFTING;
  userInput(Action, true);
  ck_assert_int_eq(info->pause, MOVING_ROTATE);

  info->pause = SHIFTING;
  userInput(None, false);
  ck_assert_int_eq(info->pause, SHIFTING);

  info->pause = SHIFTING;
  userInput(Up, false);
  ck_assert_int_eq(info->pause, SHIFTING);

  info->pause = PAUSE;
  userInput(Pause, false);
  ck_assert_int_eq(info->pause, SHIFTING);

  info->pause = PAUSE;
  userInput(Terminate, false);
  ck_assert_int_eq(info->pause, GAME_OVER);

  info->pause = PAUSE;
  userInput(Start, false);
  ck_assert_int_eq(info->pause, PAUSE);

  info->pause = PAUSE;
  userInput(Left, false);
  ck_assert_int_eq(info->pause, PAUSE);

  info->pause = PAUSE;
  userInput(Right, false);
  ck_assert_int_eq(info->pause, PAUSE);

  info->pause = PAUSE;
  userInput(Down, false);
  ck_assert_int_eq(info->pause, PAUSE);

  info->pause = PAUSE;
  userInput(Action, false);
  ck_assert_int_eq(info->pause, PAUSE);

  info->pause = PAUSE;
  userInput(None, false);
  ck_assert_int_eq(info->pause, PAUSE);

  info->pause = SPAWN;
  userInput(Left, false);
  ck_assert_int_eq(info->pause, SPAWN);

  info->pause = MOVING_LEFT;
  userInput(Left, false);
  ck_assert_int_eq(info->pause, MOVING_LEFT);

  info->pause = MOVING_RIGHT;
  userInput(Right, false);
  ck_assert_int_eq(info->pause, MOVING_RIGHT);

  info->pause = MOVING_DOWN;
  userInput(Down, false);
  ck_assert_int_eq(info->pause, MOVING_DOWN);

  info->pause = MOVING_ROTATE;
  userInput(Action, false);
  ck_assert_int_eq(info->pause, MOVING_ROTATE);

  info->pause = ATTACHING;
  userInput(Left, false);
  ck_assert_int_eq(info->pause, ATTACHING);

  info->pause = GAME_OVER;
  userInput(Start, false);
  ck_assert_int_eq(info->pause, GAME_OVER);

  info->pause = EXIT;
  userInput(Pause, false);
  ck_assert_int_eq(info->pause, EXIT);
}
END_TEST

START_TEST(test_tetris_9) {
  int **t_now = malloc(3 * sizeof(int *));
  t_now[0] = malloc(3 * sizeof(int));
  t_now[1] = malloc(3 * sizeof(int));
  t_now[2] = malloc(3 * sizeof(int));

  t_now[0][0] = 1;
  t_now[0][1] = 2;
  t_now[0][2] = 0;
  t_now[1][0] = 2;
  t_now[1][1] = 3;
  t_now[1][2] = 0;
  t_now[2][0] = -1;
  t_now[2][1] = -1;
  t_now[2][2] = -1;

  int **t_next = malloc(3 * sizeof(int *));
  t_next[0] = malloc(3 * sizeof(int));
  t_next[1] = malloc(3 * sizeof(int));
  t_next[2] = malloc(3 * sizeof(int));

  t_next[0][0] = 0;
  t_next[0][1] = 1;
  t_next[0][2] = 0;
  t_next[1][0] = 1;
  t_next[1][1] = 1;
  t_next[1][2] = 0;
  t_next[2][0] = -1;
  t_next[2][1] = -1;
  t_next[2][2] = -1;

  int **join = join_matrix(t_now, t_next);

  ck_assert_ptr_nonnull(join);

  if (join) {
    int count = 0;
    while (join[count][0] != -1) {
      count++;
    }
    ck_assert_int_eq(count, 4);
    free_matrix(join);
  }
}
END_TEST

START_TEST(test_tetris_10) {
  int **arr = NULL;
  ck_assert_ptr_null(arr);
  free_matrix(arr);
}
END_TEST

START_TEST(test_tetris_11) {
  GameInfo_t *original_info = getGameInfo();

  original_info->score = 100;
  original_info->level = 2;
  original_info->high_score = 500;
  original_info->speed = 800;
  original_info->pause = 1;

  GameInfo_t returned_info = updateCurrentState();

  ck_assert_int_eq(returned_info.score, 100);
  ck_assert_int_eq(returned_info.level, 2);
  ck_assert_int_eq(returned_info.high_score, 500);
  ck_assert_int_eq(returned_info.speed, 800);
  ck_assert_int_eq(returned_info.pause, 1);

  ck_assert_ptr_ne(&returned_info, original_info);
}
END_TEST

START_TEST(test_tetris_12) {
  GameInfo_t tetris = {0};

  setup_game(&tetris);

  ck_assert_ptr_nonnull(tetris.field);
  ck_assert_ptr_nonnull(tetris.next);
  ck_assert_ptr_nonnull(tetris.now);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_13) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  free(tetris.field);
  tetris.field = NULL;

  ck_assert_ptr_null(tetris.field);
  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_14) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  free(tetris.next);
  tetris.next = NULL;

  ck_assert_ptr_null(tetris.next);
  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_15) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  free(tetris.now);
  tetris.now = NULL;

  ck_assert_ptr_null(tetris.now);
  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_16) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  free(tetris.field);
  tetris.field = NULL;
  reset_game(&tetris, &state, &point);

  ck_assert_ptr_null(tetris.field);
  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_17) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  free(tetris.now);
  tetris.now = NULL;
  reset_game(&tetris, &state, &point);

  ck_assert_ptr_null(tetris.now);
  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_18) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  generate_rand_figure(&tetris, &point);
  ck_assert_int_ge(point.number_next_f, 0);

  copy_figures(&tetris, &point);
  point.current_pos_x = -1;
  point.current_pos_y = 0;

  int collide = collision(&tetris, &point);
  ck_assert_int_eq(collide, 1);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_19) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  generate_rand_figure(&tetris, &point);
  ck_assert_int_ge(point.number_next_f, 0);

  copy_figures(&tetris, &point);
  point.current_pos_x = 11;
  point.current_pos_y = 0;

  int collide = collision(&tetris, &point);
  ck_assert_int_eq(collide, 1);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_20) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  generate_rand_figure(&tetris, &point);
  ck_assert_int_ge(point.number_next_f, 0);

  copy_figures(&tetris, &point);
  point.current_pos_x = 3;
  point.current_pos_y = -2;

  int collide = collision(&tetris, &point);
  ck_assert_int_eq(collide, 1);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_21) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  generate_rand_figure(&tetris, &point);
  ck_assert_int_ge(point.number_next_f, 0);

  copy_figures(&tetris, &point);
  point.current_pos_x = 3;
  point.current_pos_y = 21;

  int collide = collision(&tetris, &point);
  ck_assert_int_eq(collide, 1);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_22) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  tetris.field[19][5] = 1;
  tetris.field[19][6] = 1;
  tetris.field[19][7] = 1;
  tetris.field[19][8] = 1;

  generate_rand_figure(&tetris, &point);
  ck_assert_int_ge(point.number_next_f, 0);

  copy_figures(&tetris, &point);
  point.current_pos_x = 6;
  point.current_pos_y = 19;

  int collide = collision(&tetris, &point);
  ck_assert_int_eq(collide, 1);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_23) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  state = SHIFTING;
  tetris.speed = 1000;
  point.current_pos_x = 3;
  point.current_pos_y = 0;
  point.prev_time = time_in_millisec() - 1500;

  copy_figures(&tetris, &point);

  int old_y = point.current_pos_y;

  fall_figure(&tetris, &state, &point);

  ck_assert_int_eq(point.current_pos_y, old_y + 1);
  ck_assert_int_eq(state, SHIFTING);
  ck_assert_int_ge(point.prev_time, old_y);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_24) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  state = ATTACHING;
  tetris.speed = 1000;
  point.current_pos_x = 3;
  point.current_pos_y = 21;
  point.prev_time = time_in_millisec() - 1500;

  copy_figures(&tetris, &point);

  int old_y = point.current_pos_y;

  fall_figure(&tetris, &state, &point);

  ck_assert_int_eq(point.current_pos_y, old_y);
  ck_assert_int_eq(state, ATTACHING);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_25) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  state = SHIFTING;
  tetris.speed = 1000;
  point.current_pos_x = 3;
  point.current_pos_y = 5;
  point.prev_time = time_in_millisec() - 500;

  copy_figures(&tetris, &point);

  int old_y = point.current_pos_y;
  GameState_t old_state = state;

  fall_figure(&tetris, &state, &point);

  ck_assert_int_eq(point.current_pos_y, old_y);
  ck_assert_int_eq(state, old_state);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_26) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  for (int i = 0; i < ROWS_FIGURE; i++) {
    for (int j = 0; j < COLUMNS_FIGURE; j++) {
      tetris.now[i][j] = (i >= 1 && i <= 2 && j >= 1 && j <= 2) ? 1 : 0;
    }
  }

  point.current_pos_x = 3;
  point.current_pos_y = 5;

  filling_field(&tetris, &point);

  ck_assert_int_eq(tetris.field[6][4], 1);
  ck_assert_int_eq(tetris.field[6][5], 1);
  ck_assert_int_eq(tetris.field[7][4], 1);
  ck_assert_int_eq(tetris.field[7][5], 1);
  ck_assert_int_eq(tetris.field[5][3], 0);
  ck_assert_int_eq(tetris.field[6][3], 0);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_27) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  for (int i = 0; i < ROWS_FIGURE; i++) {
    for (int j = 0; j < COLUMNS_FIGURE; j++) {
      tetris.now[i][j] = (i == 0 && j == 1) ? 1 : 0;
    }
  }

  point.current_pos_x = 3;
  point.current_pos_y = -1;

  int field_before[ROWS][COLUMNS];
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      field_before[i][j] = tetris.field[i][j];
    }
  }

  filling_field(&tetris, &point);

  int changed = 0;
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      if (tetris.field[i][j] != field_before[i][j]) {
        changed++;
      }
    }
  }

  ck_assert_int_ge(changed, 0);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_28) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  for (int i = 0; i < ROWS_FIGURE; i++) {
    for (int j = 0; j < COLUMNS_FIGURE; j++) {
      tetris.now[i][j] = (i == 0 && j == 1) ? 1 : 0;
    }
  }

  point.current_pos_x = 3;
  point.current_pos_y = 21;

  int field_before[ROWS][COLUMNS];
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      field_before[i][j] = tetris.field[i][j];
    }
  }

  filling_field(&tetris, &point);

  int changed = 0;
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      if (tetris.field[i][j] != field_before[i][j]) {
        changed++;
      }
    }
  }

  ck_assert_int_ge(changed, 0);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_29) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  for (int i = 0; i < ROWS_FIGURE; i++) {
    for (int j = 0; j < COLUMNS_FIGURE; j++) {
      tetris.now[i][j] = (i == 0 && j == 1) ? 1 : 0;
    }
  }

  point.current_pos_x = 11;
  point.current_pos_y = 5;

  int field_before[ROWS][COLUMNS];
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      field_before[i][j] = tetris.field[i][j];
    }
  }

  filling_field(&tetris, &point);

  int changed = 0;
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      if (tetris.field[i][j] != field_before[i][j]) {
        changed++;
      }
    }
  }

  ck_assert_int_ge(changed, 0);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_30) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  for (int i = 0; i < ROWS_FIGURE; i++) {
    for (int j = 0; j < COLUMNS_FIGURE; j++) {
      tetris.now[i][j] = (i == 0 && j == 1) ? 1 : 0;
    }
  }

  point.current_pos_x = -2;
  point.current_pos_y = 5;

  int field_before[ROWS][COLUMNS];
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      field_before[i][j] = tetris.field[i][j];
    }
  }

  filling_field(&tetris, &point);

  int changed = 0;
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      if (tetris.field[i][j] != field_before[i][j]) {
        changed++;
      }
    }
  }

  ck_assert_int_ge(changed, 0);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_31) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  point.current_pos_x = 3;
  point.current_pos_y = 0;

  move_figure(&tetris, &point, (UserAction_t)Left);

  ck_assert_int_ge(point.current_pos_x, 2);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_32) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  copy_figures(&tetris, &point);
  point.current_pos_x = 5;
  point.current_pos_y = 3;

  int old_x = point.current_pos_x;

  move_figure(&tetris, &point, Left);

  ck_assert_int_eq(point.current_pos_x, old_x - 1);
  ck_assert_int_eq(point.current_pos_y, 3);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_33) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  copy_figures(&tetris, &point);
  point.current_pos_x = 0;
  point.current_pos_y = 3;

  int old_x = point.current_pos_x;

  move_figure(&tetris, &point, Left);

  ck_assert_int_eq(point.current_pos_x, old_x);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_34) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  copy_figures(&tetris, &point);
  point.current_pos_x = 5;
  point.current_pos_y = 3;

  int old_x = point.current_pos_x;

  move_figure(&tetris, &point, Right);

  ck_assert_int_eq(point.current_pos_x, old_x + 1);
  ck_assert_int_eq(point.current_pos_y, 3);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_35) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  copy_figures(&tetris, &point);

  point.current_pos_x = 10;
  point.current_pos_y = 3;

  int old_x = point.current_pos_x;

  move_figure(&tetris, &point, Right);

  ck_assert_int_eq(point.current_pos_x, old_x);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_36) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  copy_figures(&tetris, &point);
  point.current_pos_x = 3;
  point.current_pos_y = 0;

  int old_y = point.current_pos_y;

  move_figure(&tetris, &point, Down);

  ck_assert_int_gt(point.current_pos_y, old_y);
  ck_assert_int_lt(point.current_pos_y, ROWS);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_37) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  copy_figures(&tetris, &point);
  point.current_pos_x = 5;
  point.current_pos_y = 3;

  int old_x = point.current_pos_x;
  int old_y = point.current_pos_y;

  move_figure(&tetris, &point, None);

  ck_assert_int_eq(point.current_pos_x, old_x);
  ck_assert_int_eq(point.current_pos_y, old_y);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_38) {
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

  point.current_pos_x = 3;
  point.current_pos_y = 0;

  rotate_figure(&tetris, &point);

  ck_assert_int_eq(tetris.now[0][2], 1);
  ck_assert_int_eq(tetris.now[1][2], 1);
  ck_assert_int_eq(tetris.now[2][2], 1);
  ck_assert_int_eq(tetris.now[3][2], 1);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_39) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  int O_figure[3][3] = {
      {1, 1, 0},
      {1, 1, 0},
      {0, 0, 0},
  };

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      tetris.now[i][j] = O_figure[i][j];
    }
  }

  int original[3][3];
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      original[i][j] = tetris.now[i][j];
    }
  }

  point.number_now_f = 3;
  rotate_figure(&tetris, &point);

  ck_assert_int_eq(tetris.now[0][0], original[0][0]);
  ck_assert_int_eq(tetris.now[0][1], original[0][1]);
  ck_assert_int_eq(tetris.now[1][0], original[1][0]);
  ck_assert_int_eq(tetris.now[1][1], original[1][1]);

  remove_matrix(&tetris);
}
END_TEST

START_TEST(test_tetris_40) {
  GameInfo_t tetris = {0};
  GameState_t state = START;
  Tag_point_t point = {0};

  create_matrix(&tetris);
  initialize_game(&tetris, &state, &point);

  point.number_now_f = 1;
  int L_figure[4][4] = {{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      tetris.now[i][j] = L_figure[i][j];
    }
  }

  point.current_pos_x = 3;
  point.current_pos_y = 0;

  int original[4][4];
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      original[i][j] = tetris.now[i][j];
    }
  }

  rotate_figure(&tetris, &point);

  int changed = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (tetris.now[i][j] != original[i][j]) {
        changed = 1;
        break;
      }
    }
    if (changed) break;
  }
  ck_assert_int_eq(changed, 1);

  remove_matrix(&tetris);
}
END_TEST

Suite *test_tetris(void) {
  Suite *s = suite_create("Tetris Test");
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
  tcase_add_test(tc_tetris, test_tetris_32);
  tcase_add_test(tc_tetris, test_tetris_33);
  tcase_add_test(tc_tetris, test_tetris_34);
  tcase_add_test(tc_tetris, test_tetris_35);
  tcase_add_test(tc_tetris, test_tetris_36);
  tcase_add_test(tc_tetris, test_tetris_37);
  tcase_add_test(tc_tetris, test_tetris_38);
  tcase_add_test(tc_tetris, test_tetris_39);
  tcase_add_test(tc_tetris, test_tetris_40);

  suite_add_tcase(s, tc_tetris);
  return s;
}