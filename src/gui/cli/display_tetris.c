#include "display_tetris.h"

UserAction_t input_key() {
  UserAction_t return_key;
  int key = getch();

  switch (key) {
    case 10:
      return_key = Start;
      break;
    case 32:
      return_key = Action;
      break;
    case 27:
      return_key = Terminate;
      break;
    case 263:
    case 'p':
    case 'P':
      return_key = Pause;
      break;
    case KEY_LEFT:
    case 'a':
    case 'A':
      return_key = Left;
      break;
    case KEY_RIGHT:
    case 'd':
    case 'D':
      return_key = Right;
      break;
    case KEY_DOWN:
    case 's':
    case 'S':
      return_key = Down;
      break;
    default:
      return_key = None;
      break;
  }

  return return_key;
}

void setup_gui(void) {
  initscr();
  curs_set(0);
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
}

void delete_gui(void) { endwin(); }

void printCurrentState(GameInfo_t *info, GameInfo_t *tetris, GameState_t *state,
                       Tag_point_t *point) {
  if (*state == START) {
    int choice = print_start();
    if (choice == 0) {
      *state = SPAWN;
    } else if (choice == 1) {
      *state = EXIT;
    }
  } else if (*state == GAME_OVER) {
    int choice = print_game_over();
    if (choice == 0) {
      reset_game(tetris, state, point);
    } else if (choice == 1) {
      *state = EXIT;
    }
  } else if (*state == PAUSE) {
    print_pause();
  } else {
    print_game_board();
    print_field_information();
    print_stats_ban();
    print_information();
    print_stats(info->score, info->high_score, info->level, info->speed, 1000);
    print_fallfigure(info->field, ROWS, COLUMNS);
    clear_next_figure();
    print_arr(info->next);
  }

  refresh();
}

void game_loop(void) {
  GameState_t state = START;
  GameInfo_t tetris;
  Tag_point_t point;

  setup_game(&tetris);

  while (state != EXIT) {
    GameInfo_t *info = getGameInfo();
    info->pause = (int)state;
    userInput(input_key(), false);
    state = (GameState_t)info->pause;

    update_game(&tetris, &state, &point);
    GameInfo_t info_tetris = updateCurrentState();
    printCurrentState(&info_tetris, &tetris, &state, &point);
    free_gameinfo(&info_tetris);
  }

  remove_matrix(&tetris);
}

int main(void) {
  setup_gui();
  game_loop();
  delete_gui();
  return 0;
}