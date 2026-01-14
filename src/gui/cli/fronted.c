#include "display_tetris.h"

const char *game_star[] = {"New game", "Exit"};
const char *game_over[] = {"Restart", "Exit"};

int print_start(void) {
  int choice = 0;
  int ch;

  clear();
  printw("=== MAIN MENU ===\n\n");

  for (int i = 0; i < N_ITEMS; i++) {
    if (i == choice) {
      attron(A_REVERSE);
      printw("> %s <\n", game_star[i]);
      attroff(A_REVERSE);
    } else {
      printw("  %s\n", game_star[i]);
    }
  }
  printw("\nUse the arrows to select, and Enter to confirm");
  refresh();

  do {
    ch = getch();

    if (ch != ERR) {
      int prev_choice = choice;

      switch (ch) {
        case KEY_UP:
          choice = (choice - 1 + N_ITEMS) % N_ITEMS;
          break;
        case KEY_DOWN:
          choice = (choice + 1) % N_ITEMS;
          break;
        case 'w':
          choice = (choice - 1 + N_ITEMS) % N_ITEMS;
          break;
        case 's':
          choice = (choice + 1) % N_ITEMS;
          break;
        case 'W':
          choice = (choice - 1 + N_ITEMS) % N_ITEMS;
          break;
        case 'S':
          choice = (choice + 1) % N_ITEMS;
          break;
      }

      if (choice != prev_choice) {
        for (int i = 2; i < 2 + N_ITEMS; i++) {
          move(i, 0);
          clrtoeol();
        }

        for (int i = 0; i < N_ITEMS; i++) {
          move(2 + i, 0);
          if (i == choice) {
            attron(A_REVERSE);
            printw("> %s <", game_star[i]);
            attroff(A_REVERSE);
          } else {
            printw("  %s", game_star[i]);
          }
          clrtoeol();
        }
        refresh();
      }
    }

  } while (ch != '\n' && ch != '\r' && ch != KEY_ENTER);

  clear();
  return choice;
}

int print_game_over(void) {
  for (int i = 0; i < ROWS + 2; i++) {
    for (int j = 0; j < (COLUMNS * 2) + 2; j++) {
      mvprintw(i, j, " ");
    }
  }

  int choice = 0;
  int ch;

  clear();
  printw("=== GAME OVER ===\n\n");

  for (int i = 0; i < N_ITEMS; i++) {
    if (i == choice) {
      attron(A_REVERSE);
      printw("> %s <\n", game_over[i]);
      attroff(A_REVERSE);
    } else {
      printw("  %s\n", game_over[i]);
    }
  }
  printw("\nUse the arrows to select, and Enter to confirm");
  refresh();

  do {
    ch = getch();

    if (ch != ERR) {
      int prev_choice = choice;

      switch (ch) {
        case KEY_UP:
          choice = (choice - 1 + N_ITEMS) % N_ITEMS;
          break;
        case KEY_DOWN:
          choice = (choice + 1) % N_ITEMS;
          break;
        case 'w':
          choice = (choice - 1 + N_ITEMS) % N_ITEMS;
          break;
        case 's':
          choice = (choice + 1) % N_ITEMS;
          break;
        case 'W':
          choice = (choice - 1 + N_ITEMS) % N_ITEMS;
          break;
        case 'S':
          choice = (choice + 1) % N_ITEMS;
          break;
      }

      if (choice != prev_choice) {
        for (int i = 2; i < 2 + N_ITEMS; i++) {
          move(i, 0);
          clrtoeol();
        }

        for (int i = 0; i < N_ITEMS; i++) {
          move(2 + i, 0);
          if (i == choice) {
            attron(A_REVERSE);
            printw("> %s <", game_over[i]);
            attroff(A_REVERSE);
          } else {
            printw("  %s", game_over[i]);
          }
          clrtoeol();
        }
        refresh();
      }
    }

  } while (ch != '\n' && ch != '\r' && ch != KEY_ENTER);

  clear();
  return choice;
}

void print_pause(void) {
  mvprintw(9, 0, "%*c", 22, ' ');
  mvprintw(10, 0, "        PAUSE         ");
  mvprintw(11, 0, "%*c", 22, ' ');
}

void print_game_board(void) {
  for (int i = 0; i < ROWS + 2; i++) {
    for (int j = 0; j < (COLUMNS * 2) + 2; j++) {
      if (i == 0 || i == (ROWS + 2) - 1) {
        mvaddch(i, j, ACS_HLINE);
      } else if (j == 0 || j == (COLUMNS * 2) + 1) {
        mvaddch(i, j, ACS_VLINE);
      } else {
        mvaddch(i, j, ' ');
      }
    }
  }
  mvaddch(0, 0, ACS_ULCORNER);
  mvaddch(21, 0, ACS_LLCORNER);
  mvaddch(0, 21, ACS_URCORNER);
  mvaddch(21, 21, ACS_LRCORNER);
}

void print_field_information(void) {
  for (int i = 0; i < ROWS + 2; i++) {
    for (int j = 0; j < (COLUMNS * 2) + 3; j++) {
      if (i == 0 || i == (ROWS + 2) - 1) {
        mvaddch(i, j + 23, ACS_HLINE);
      } else if (j == 0 || j == (COLUMNS * 2) + 2) {
        mvaddch(i, j + 23, ACS_VLINE);
      }
    }
  }
  mvaddch(0, 23, ACS_ULCORNER);
  mvaddch(21, 23, ACS_LLCORNER);
  mvaddch(0, 45, ACS_URCORNER);
  mvaddch(21, 45, ACS_LRCORNER);
}

void print_stats_ban(void) {
  mvprintw(1, 25, "Next:");
  mvprintw(7, 25, "Score:");
  mvprintw(9, 25, "High score:");
  mvprintw(11, 25, "Level:");
  mvprintw(13, 25, "Speed:");
}

void print_information(void) {
  mvprintw(16, 25, "Controls:");
  mvprintw(17, 25, "Move: Left/Right");
  mvprintw(18, 25, "Down: Fall");
  mvprintw(19, 25, "Rotate: Space");
  mvprintw(20, 25, "Pause: P");
}

void print_stats(int score, int high_score, int level, int speed,
                 int begin_speed) {
  mvprintw(7, 37, "%d", score);
  mvprintw(9, 37, "%d", high_score);
  mvprintw(11, 37, "%d", level);
  mvprintw(13, 37, "%.2f", (double)begin_speed / speed);
}

void print_fallfigure(int **arr, int row, int col) {
  if (arr != NULL) {
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        if (arr[i][j] != 0) {
          mvprintw(i + 1, j * 2 + 1, "[]");
        }
      }
    }
  }
}

void clear_next_figure(void) {
  for (int i = 0; i < ROWS_FIGURE - 1; i++) {
    for (int j = 0; j < COLUMNS_FIGURE; j++) {
      mvprintw(2 + i, 24 + j * 2 + 1, "  ");
    }
  }
}

void print_arr(int **arr) {
  if (arr != NULL) {
    size_t i = 0;
    while (arr[i][0] != -1) {
      mvprintw(arr[i][0] + 1, arr[i][1] * 2 + 1, "[]");
      i++;
    }
  }
}