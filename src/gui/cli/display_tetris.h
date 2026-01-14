#include <ncurses.h>

#include "../../brick_game/tetris/tetris.h"

#ifndef DISPAY_TETRIS_H
#define DISPLAY_TETRIS_H

extern const char *game_star[];
extern const char *game_over[];

UserAction_t input_key();
void setup_gui(void);
void delete_gui(void);
int print_start(void);
int print_game_over(void);
void print_pause(void);
void print_game_board(void);
void print_stats_ban(void);
void print_information(void);
void print_field_information(void);
void print_stats(int score, int high_score, int level, int speed,
                 int begin_speed);
void print_fallfigure(int **arr, int row, int col);
void clear_next_figure(void);
void print_arr(int **arr);
void printCurrentState(GameInfo_t *info, GameInfo_t *tetris, GameState_t *state,
                       Tag_point_t *point);
void game_loop(void);
#endif