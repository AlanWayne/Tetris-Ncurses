#include "frontend.h"

void front_set_up(GameInfo_t* game_info) {
  setlocale(LC_ALL, "");
  initscr();
  timeout(0);
  noecho();
  cbreak();
  curs_set(0);
  game_info->main_window =
      create_window(HEIGHT * H_SCALE + 2, WIDTH * W_SCALE * 2 + 2, 0, 0);
  game_info->game_window =
      create_window(HEIGHT * H_SCALE + 2, WIDTH * W_SCALE + 2, 0, 0);
  game_info->next_window = create_window(
      HEIGHT * H_SCALE / 4, WIDTH * W_SCALE / 2 + 6, 0, WIDTH * W_SCALE + 3);
  game_info->stat_window =
      create_window(HEIGHT * H_SCALE / 2, WIDTH * W_SCALE / 2 + 6,
                    HEIGHT * H_SCALE / 4 + 1, WIDTH * W_SCALE + 3);
}

WIN* create_window(const int height, const int width, const int pos_y,
                   const int pos_x) {
  WIN* window = (WIN*)malloc(sizeof(WIN));
  window->window = newwin(height, width, pos_y, pos_x);
  window->height = getmaxy(window->window);
  window->width = getmaxx(window->window);
  window->pos_y = pos_y;
  window->pos_x = pos_x;
  return window;
}

void front_tear_down(GameInfo_t* game_info) {
  delwin(game_info->main_window->window);
  delwin(game_info->game_window->window);
  delwin(game_info->next_window->window);
  delwin(game_info->stat_window->window);
  endwin();
  free(game_info->main_window);
  free(game_info->game_window);
  free(game_info->next_window);
  free(game_info->stat_window);
}