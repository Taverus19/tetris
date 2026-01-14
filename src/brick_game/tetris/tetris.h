#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#include "defines.h"

#ifndef TETRIS_H
#define TETRIS_H

typedef enum {
  START,
  SPAWN,
  MOVING_LEFT,
  MOVING_RIGHT,
  MOVING_DOWN,
  MOVING_ROTATE,
  SHIFTING,
  ATTACHING,
  PAUSE,
  GAME_OVER,
  EXIT
} GameState_t;

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action,
  None
} UserAction_t;

typedef struct {
  int current_pos_x;
  int current_pos_y;
  int number_next_f;
  int number_now_f;
  long long int prev_time;
} Tag_point_t;

typedef struct {
  int **field;
  int **next;
  int **now;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

GameInfo_t *getGameInfo();
void setup_game(GameInfo_t *tetris);
void create_matrix(GameInfo_t *tetris);
void remove_matrix(GameInfo_t *tetris);
void initialize_game(GameInfo_t *tetris, GameState_t *state,
                     Tag_point_t *point);
void generate_rand_figure(GameInfo_t *tetris, Tag_point_t *point);
void reset_game(GameInfo_t *tetris, GameState_t *state, Tag_point_t *point);
long long int time_in_millisec();
void copy_figures(GameInfo_t *tetris, Tag_point_t *point);
int collision(GameInfo_t *tetris, Tag_point_t *point);
void fall_figure(GameInfo_t *tetris, GameState_t *state, Tag_point_t *point);
void filling_field(GameInfo_t *tetris, Tag_point_t *point);
void move_figure(GameInfo_t *tetris, Tag_point_t *point, UserAction_t action);
void rotate_figure(GameInfo_t *tetris, Tag_point_t *point);
void try_standard_wall_kick(GameInfo_t *tetris, Tag_point_t *point,
                            int original_figure[4][4]);
void try_I_figure_wall_kick(GameInfo_t *tetris, Tag_point_t *point,
                            int original_figure[4][4]);
int remove_row(GameInfo_t *tetris);
void scoring_point(GameInfo_t *tetris, int count);
void increase_level(GameInfo_t *tetris);
void save_high_score(GameInfo_t *tetris);
void create_initial_high_score(void);
void state_game(GameInfo_t *tetris, GameState_t *state, Tag_point_t *point);
void update_game(GameInfo_t *tetris, GameState_t *state, Tag_point_t *point);
int **convert_matrix(int **arr1, int row, int col, int x, int y);
int **join_matrix(int **arr1, int **arr2);
void free_matrix(int **arr);
void free_gameinfo(GameInfo_t *info);

void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();

#endif