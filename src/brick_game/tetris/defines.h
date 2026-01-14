#ifndef DEFINES_H
#define DEFINES_H

#define ROWS 20
#define COLUMNS 10

#define TETRIS_F 7
#define ROWS_FIGURE 4
#define COLUMNS_FIGURE 4

#define N_ITEMS 2

#define SCORE_1 100
#define SCORE_2 300
#define SCORE_3 700
#define SCORE_4 1500

#define LEVEL_NEXT 600
#define MAX_LEVEL 10

#define FIGURES                                                     \
  {                                                                 \
    {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},       \
        {{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},   \
        {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},   \
        {{1, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},   \
        {{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},   \
        {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, { \
      {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, { 0, 0, 0, 0 }      \
    }                                                               \
  }

#endif