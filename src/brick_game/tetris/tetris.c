#include "tetris.h"

GameInfo_t *getGameInfo() {
  static GameInfo_t info;
  return &info;
}

GameInfo_t updateCurrentState() {
  GameInfo_t *info = getGameInfo();
  return *info;
}

void setup_game(GameInfo_t *tetris) {
  srand(time(NULL));
  create_matrix(tetris);
}

void create_matrix(GameInfo_t *tetris) {
  tetris->field = malloc(ROWS * sizeof(int *) + ROWS * COLUMNS * sizeof(int));
  tetris->next = malloc(ROWS_FIGURE * sizeof(int *) +
                        ROWS_FIGURE * COLUMNS_FIGURE * sizeof(int));
  tetris->now = malloc(ROWS_FIGURE * sizeof(int *) +
                       ROWS_FIGURE * COLUMNS_FIGURE * sizeof(int));

  if (tetris->field != NULL || tetris->next != NULL || tetris->now != NULL) {
    int *ptr_field = (int *)(tetris->field + ROWS);
    int *ptr_next = (int *)(tetris->next + ROWS_FIGURE);
    int *ptr_now = (int *)(tetris->now + ROWS_FIGURE);

    for (int i = 0; i < ROWS; i++) {
      tetris->field[i] = ptr_field + COLUMNS * i;
    }

    for (int i = 0; i < ROWS_FIGURE; i++) {
      tetris->next[i] = ptr_next + COLUMNS_FIGURE * i;
      tetris->now[i] = ptr_now + COLUMNS_FIGURE * i;
    }

    memset(ptr_field, 0, ROWS * COLUMNS * sizeof(int));
    memset(ptr_next, 0, ROWS_FIGURE * COLUMNS_FIGURE * sizeof(int));
    memset(ptr_now, 0, ROWS_FIGURE * COLUMNS_FIGURE * sizeof(int));
  }

  FILE *highScore;
  highScore = fopen("high_score_tetris.txt", "r");
  if (highScore) {
    if (fscanf(highScore, "%d", &tetris->high_score) == 0) {
      tetris->high_score = 0;
    }
    fclose(highScore);
  } else {
    tetris->high_score = 0;
    create_initial_high_score();
  }
}

void remove_matrix(GameInfo_t *tetris) {
  if (tetris->field) {
    free(tetris->field);
  }

  if (tetris->next) {
    free(tetris->next);
  }

  if (tetris->now) {
    free(tetris->now);
  }
}

void initialize_game(GameInfo_t *tetris, GameState_t *state,
                     Tag_point_t *point) {
  tetris->score = 0;
  tetris->level = 1;
  tetris->speed = 1000;
  tetris->pause = 0;

  *state = START;

  generate_rand_figure(tetris, point);
}

void generate_rand_figure(GameInfo_t *tetris, Tag_point_t *point) {
  int figures[TETRIS_F][ROWS_FIGURE][COLUMNS_FIGURE] = FIGURES;
  int type = rand() % TETRIS_F;

  for (int i = 0; i < ROWS_FIGURE; i++) {
    for (int j = 0; j < COLUMNS_FIGURE; j++)
      tetris->next[i][j] = figures[type][i][j];
  }

  point->number_next_f = type;
}

void reset_game(GameInfo_t *tetris, GameState_t *state, Tag_point_t *point) {
  if (tetris->field) {
    int *ptr_field = (int *)(tetris->field + ROWS);
    memset(ptr_field, 0, ROWS * COLUMNS * sizeof(int));
  }

  if (tetris->next) {
    int *ptr_next = (int *)(tetris->next + ROWS_FIGURE);
    memset(ptr_next, 0, ROWS_FIGURE * COLUMNS_FIGURE * sizeof(int));
  }

  if (tetris->now) {
    int *ptr_now = (int *)(tetris->now + ROWS_FIGURE);
    memset(ptr_now, 0, ROWS_FIGURE * COLUMNS_FIGURE * sizeof(int));
  }

  tetris->score = 0;
  tetris->level = 1;
  tetris->speed = 1000;
  tetris->pause = 0;

  generate_rand_figure(tetris, point);
  *state = START;
}

long long int time_in_millisec() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (((long long int)tv.tv_sec) * 1000) + (tv.tv_usec / 1000);
}

void copy_figures(GameInfo_t *tetris, Tag_point_t *point) {
  for (int i = 0; i < ROWS_FIGURE; i++) {
    for (int j = 0; j < COLUMNS_FIGURE; j++) {
      tetris->now[i][j] = tetris->next[i][j];
    }
  }

  point->number_now_f = point->number_next_f;
}

int collision(GameInfo_t *tetris, Tag_point_t *point) {
  for (int y = 0; y < ROWS_FIGURE; y++) {
    for (int x = 0; x < COLUMNS_FIGURE; x++) {
      if (tetris->now[y][x] == 1) {
        int field_y = point->current_pos_y + y;
        int field_x = point->current_pos_x + x;

        if (field_x < 0 || field_x >= COLUMNS || field_y >= ROWS ||
            field_y < 0) {
          return 1;
        }

        if (tetris->field[field_y][field_x] == 1) {
          return 1;
        }
      }
    }
  }

  return 0;
}

void fall_figure(GameInfo_t *tetris, GameState_t *state, Tag_point_t *point) {
  long long int time = time_in_millisec();
  if (time - point->prev_time > tetris->speed) {
    point->current_pos_y++;
    if (collision(tetris, point) != 0) {
      point->current_pos_y--;
      *state = ATTACHING;
    }
    point->prev_time = time;
  }
}

void filling_field(GameInfo_t *tetris, Tag_point_t *point) {
  for (int y = 0; y < ROWS_FIGURE; y++) {
    for (int x = 0; x < COLUMNS_FIGURE; x++) {
      if (tetris->now[y][x] == 1) {
        int field_y = point->current_pos_y + y;
        int field_x = point->current_pos_x + x;

        if (field_y >= 0 && field_y < ROWS && field_x >= 0 &&
            field_x < COLUMNS) {
          tetris->field[field_y][field_x] = 1;
        }
      }
    }
  }
}

void move_figure(GameInfo_t *tetris, Tag_point_t *point, UserAction_t action) {
  if (action == Left) {
    point->current_pos_x--;
    if (collision(tetris, point) != 0) {
      point->current_pos_x++;
    }
  } else if (action == Right) {
    point->current_pos_x++;
    if (collision(tetris, point) != 0) {
      point->current_pos_x--;
    }
  } else if (action == Down) {
    while (collision(tetris, point) == 0) {
      point->current_pos_y++;
    }
    point->current_pos_y--;
  }
}

void rotate_figure(GameInfo_t *tetris, Tag_point_t *point) {
  if (point->number_now_f != 3) {
    int size;
    if (point->number_now_f == 0) {
      size = 4;
    } else {
      size = 3;
    }

    int original_figure[4][4];
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        original_figure[i][j] = tetris->now[i][j];
      }
    }

    int tmp[size][size];
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        tmp[j][i] = tetris->now[i][j];
      }
    }
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        tetris->now[i][j] = tmp[i][size - j - 1];
      }
    }

    if (collision(tetris, point) != 0) {
      if (point->number_now_f == 0) {
        try_I_figure_wall_kick(tetris, point, original_figure);
      } else {
        try_standard_wall_kick(tetris, point, original_figure);
      }
    }
  }
}

void try_standard_wall_kick(GameInfo_t *tetris, Tag_point_t *point,
                            int original_figure[4][4]) {
  int old_x = point->current_pos_x;
  int old_y = point->current_pos_y;

  int kick_attempts[5][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-2, 0}};

  for (int attempt = 0; attempt < 5; attempt++) {
    point->current_pos_x = old_x + kick_attempts[attempt][0];
    point->current_pos_y = old_y + kick_attempts[attempt][1];

    if (collision(tetris, point) == 0) {
      return;
    }
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      tetris->now[i][j] = original_figure[i][j];
    }
  }
  point->current_pos_x = old_x;
  point->current_pos_y = old_y;
}

void try_I_figure_wall_kick(GameInfo_t *tetris, Tag_point_t *point,
                            int original_figure[4][4]) {
  int old_x = point->current_pos_x;
  int old_y = point->current_pos_y;

  int kick_attempts[8][2] = {{-1, 0}, {1, 0}, {-1, -1}, {2, -1},
                             {-2, 0}, {1, 0}, {-2, 1},  {1, 1}};

  int extreme_kicks[4][2] = {{-3, 0}, {3, 0}, {0, -2}, {0, 2}};

  for (int attempt = 0; attempt < 8; attempt++) {
    point->current_pos_x = old_x + kick_attempts[attempt][0];
    point->current_pos_y = old_y + kick_attempts[attempt][1];

    if (collision(tetris, point) == 0) {
      return;
    }
  }

  for (int attempt = 0; attempt < 4; attempt++) {
    point->current_pos_x = old_x + extreme_kicks[attempt][0];
    point->current_pos_y = old_y + extreme_kicks[attempt][1];

    if (collision(tetris, point) == 0) {
      return;
    }
  }

  if (old_x > COLUMNS - 4) {
    point->current_pos_x = COLUMNS - 4;
    point->current_pos_y = old_y;

    if (collision(tetris, point) == 0) {
      return;
    }
  }

  if (old_x < 2) {
    point->current_pos_x = 0;
    point->current_pos_y = old_y;

    if (collision(tetris, point) == 0) {
      return;
    }
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      tetris->now[i][j] = original_figure[i][j];
    }
  }
  point->current_pos_x = old_x;
  point->current_pos_y = old_y;
}

int remove_row(GameInfo_t *tetris) {
  int full_row = ROWS - 1;
  int count = 0;

  for (int i = ROWS - 1; i >= 0; i--) {
    bool is_full = true;
    for (int j = 0; j < COLUMNS; j++) {
      if (tetris->field[i][j] == 0) {
        is_full = false;
      }
    }
    if (is_full == false) {
      full_row--;
    } else {
      count++;
      for (int k = full_row; k > 0; k--) {
        for (int j = 0; j < COLUMNS; j++) {
          tetris->field[k][j] = tetris->field[k - 1][j];
          tetris->field[k - 1][j] = 0;
        }
      }
      i++;
    }
  }

  return count;
}

void scoring_point(GameInfo_t *tetris, int count) {
  if (count == 1) {
    tetris->score += SCORE_1;
  } else if (count == 2) {
    tetris->score += SCORE_2;
  } else if (count == 3) {
    tetris->score += SCORE_3;
  } else if (count == 4) {
    tetris->score += SCORE_4;
  }
}

void increase_level(GameInfo_t *tetris) {
  while (tetris->score >= tetris->level * LEVEL_NEXT &&
         tetris->level != MAX_LEVEL) {
    tetris->level++;
    tetris->speed -= 100;
  }
}

void save_high_score(GameInfo_t *tetris) {
  if (tetris->score >= tetris->high_score) {
    tetris->high_score = tetris->score;
    FILE *file_high_score = fopen("high_score_tetris.txt", "w");
    if (file_high_score) {
      fprintf(file_high_score, "%d", tetris->high_score);
      fclose(file_high_score);
    }
  }
}

void create_initial_high_score(void) {
  FILE *file_high_score = fopen("high_score_tetris.txt", "w");
  if (file_high_score) {
    fprintf(file_high_score, "%d", 0);
    fclose(file_high_score);
  }
}

void state_game(GameInfo_t *tetris, GameState_t *state, Tag_point_t *point) {
  if (*state == START) {
    initialize_game(tetris, state, point);
  } else if (*state == SPAWN) {
    point->current_pos_x = 3;

    if (point->number_next_f == 0) {
      point->current_pos_y = -1;
    } else {
      point->current_pos_y = 0;
    }
    point->prev_time = time_in_millisec();
    copy_figures(tetris, point);
    generate_rand_figure(tetris, point);
    if (collision(tetris, point) != 0) {
      *state = GAME_OVER;
    } else {
      *state = SHIFTING;
    }
  } else if (*state == SHIFTING) {
    fall_figure(tetris, state, point);
  } else if (*state == MOVING_LEFT) {
    move_figure(tetris, point, (UserAction_t)Left);
    *state = SHIFTING;
  } else if (*state == MOVING_RIGHT) {
    move_figure(tetris, point, (UserAction_t)Right);
    *state = SHIFTING;
  } else if (*state == MOVING_DOWN) {
    move_figure(tetris, point, (UserAction_t)Down);
    *state = SHIFTING;
  } else if (*state == MOVING_ROTATE) {
    rotate_figure(tetris, point);
    *state = SHIFTING;
  } else if (*state == ATTACHING) {
    filling_field(tetris, point);
    scoring_point(tetris, remove_row(tetris));
    increase_level(tetris);
    save_high_score(tetris);
    *state = SPAWN;
  }
}

void update_game(GameInfo_t *tetris, GameState_t *state, Tag_point_t *point) {
  state_game(tetris, state, point);

  GameInfo_t *info = getGameInfo();
  if (info) {
    info->field = tetris->field;
    if (*state != GAME_OVER) {
      int **t_now = convert_matrix(tetris->now, ROWS_FIGURE, COLUMNS_FIGURE,
                                   point->current_pos_y, point->current_pos_x);
      int **t_next =
          convert_matrix(tetris->next, ROWS_FIGURE, COLUMNS_FIGURE, 2, 12);
      info->next = join_matrix(t_next, t_now);
    } else {
      int **t_now =
          convert_matrix(tetris->now, ROWS_FIGURE, COLUMNS_FIGURE, 2, 12);
      info->next = t_now;
    }
    info->score = tetris->score;
    info->high_score = tetris->high_score;
    info->level = tetris->level;
    info->speed = tetris->speed;
  }
}

void userInput(UserAction_t action, bool hold) {
  GameInfo_t *info = getGameInfo();
  int *state = &info->pause;

  if (action == Start && *state == START) {
    *state = SPAWN;
  } else if (*state == SHIFTING) {
    if (action == Pause) {
      *state = PAUSE;
    } else if (action == Left && !hold) {
      *state = MOVING_LEFT;
    } else if (action == Right && !hold) {
      *state = MOVING_RIGHT;
    } else if (action == Down) {
      *state = MOVING_DOWN;
    } else if (action == Action) {
      *state = MOVING_ROTATE;
    }
  } else if (*state == PAUSE) {
    if (action == Pause) {
      *state = SHIFTING;
    } else if (action == Terminate) {
      *state = GAME_OVER;
    }
  }
}

int **convert_matrix(int **arr1, int row, int col, int x, int y) {
  int count = 0;
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      if (arr1[i][j] == 1) {
        count++;
      }
    }
  }

  int **mat = (int **)malloc((count + 1) * sizeof(int *));
  int k = 0;
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      if (arr1[i][j] == 1) {
        mat[k] = (int *)malloc(3 * sizeof(int));
        mat[k][0] = i + x;
        mat[k][1] = j + y;
        mat[k][2] = 0;
        k++;
      }
    }
  }

  mat[k] = (int *)malloc(3 * sizeof(int));
  mat[k][0] = -1;
  mat[k][1] = -1;
  mat[k][2] = -1;

  return mat;
}

int **join_matrix(int **arr1, int **arr2) {
  int i = 0;
  int count = 0;

  while (arr1[i][0] != -1) {
    i++;
    count++;
  }

  i = 0;
  while (arr2[i][0] != -1) {
    i++;
    count++;
  }

  i = 0;
  int **mat = (int **)malloc((count + 1) * sizeof(int *));
  int j = 0;

  while (arr1[i][1] != -1) {
    mat[j] = arr1[i];
    i++;
    j++;
  }

  free(arr1[i]);
  i = 0;
  while (arr2[i][1] != -1) {
    mat[j] = arr2[i];
    i++;
    j++;
  }
  mat[j] = arr2[i];

  free(arr1);
  free(arr2);
  return mat;
}

void free_matrix(int **arr) {
  if (arr != NULL) {
    size_t i = 0;
    while (arr[i][0] != -1) {
      free(arr[i]);
      i++;
    }
    free(arr[i]);
    free(arr);
  }
}

void free_gameinfo(GameInfo_t *info) { free_matrix(info->next); }