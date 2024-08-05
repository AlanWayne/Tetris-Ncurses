#include "frontend.h"

void frontend(GameInfo_t* game_info) {
  game_info->pause ? draw_pause(game_info) : draw_game(game_info);
  if (!game_info->pause) draw_shadow(game_info);
  draw_next(game_info);
  draw_stat(game_info);
}

void draw_shadow(GameInfo_t* game_info) {
  WINDOW* game_w = game_info->game_window->window;
  int x[4] = {0};
  int y[4] = {0};

  calc_shadow(game_info, x, y);
  draw_block(game_w, x, y, 1);
  wrefresh(game_w);
}

void draw_game(GameInfo_t* game_info) {
  WINDOW* game_w = game_info->game_window->window;
  cls(game_w);
  draw_block(game_w, game_info->block->x, game_info->block->y, 0);
  box(game_w, 0, 0);
  mvwprintw(game_w, 0, 2, " [ GAME ] ");
  draw_pile(game_info);
  wrefresh(game_w);
}

void draw_pause(GameInfo_t* game_info) {
  WINDOW* game_w = game_info->game_window->window;
  cls(game_w);
  mvwprintw(game_w, HEIGHT * H_SCALE / 2 - 1, 16, "- PAUSE -");
  mvwprintw(game_w, HEIGHT * H_SCALE / 2 + 1, 11, "press SPACE to play");
  wrefresh(game_w);
}

void draw_block(WINDOW* window, int x[4], int y[4], int type) {
  for (int i = 0; i < 4; ++i) {
    draw_segment(window, H_SCALE * y[i], W_SCALE * x[i], type);
  }
}

void draw_pile(GameInfo_t* game_info) {
  for (int i = 0; i < WIDTH; ++i)
    for (int k = 0; k < HEIGHT; ++k) {
      if (game_info->field[i][k]) {
        draw_segment(game_info->game_window->window, H_SCALE * k, W_SCALE * i, 0);
      }
    }
}

void draw_next(GameInfo_t* game_info) {
  WINDOW* next_w = game_info->next_window->window;
  cls(next_w);
  box(next_w, 0, 0);
  mvwprintw(next_w, 0, 2, " [ NEXT ] ");
  draw_block(next_w, game_info->next_block->x, game_info->next_block->y, 0);
  wrefresh(next_w);
}

void draw_stat(GameInfo_t* game_info) {
  WINDOW* stat_w = game_info->stat_window->window;
  cls(stat_w);
  box(stat_w, 0, 0);
  mvwprintw(stat_w, 0, 6, " [ LEVEL %2d ] ", game_info->level);
  mvwprintw(stat_w, 2, 2, "SCORE:  %14d", game_info->score);
  mvwprintw(stat_w, 4, 2, "RECORD: %14d", game_info->high_score);
  mvwprintw(stat_w, 6, 3, "-------------");
  for (int i = 3; i < 23; ++i) mvwaddstr(stat_w, 6, i, "\xe2\x94\x80");
  mvwprintw(stat_w, 8, 2, "LEFT:                A");
  mvwprintw(stat_w, 10, 2, "RIGHT:               D");
  mvwprintw(stat_w, 12, 2, "ROTATE:              E");
  mvwprintw(stat_w, 14, 2, "DROP:                S");
  mvwprintw(stat_w, 16, 2, "EXIT:              Esc");
  wrefresh(stat_w);
}