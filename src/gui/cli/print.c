#include "frontend.h"

void draw_segment(WINDOW* window, int y, int x, int type) {
  for (int i = 0; i < 2; ++i) {
    for (int k = 0; k < 2; ++k) {
      print_char(window, y + i + 1, x + k * 2 + 1, type);
    }
  }
}

void print_char(WINDOW* window, int y, int x, int type) {
  char* wall = "\xe2\x96\x88\xe2\x96\x88";
  char* shadow = "\xe2\x96\x92\xe2\x96\x92";

  switch(type) {
    case 0:
      mvwaddstr(window, y, x, wall);
      break;
    case 1:
      mvwaddstr(window, y, x, shadow);
      break;      
  }
}

void calc_shadow(GameInfo_t* game_info, int x[4], int y[4]) {
  for (int i = 0; i < 4; ++i) {
    x[i] = game_info->block->x[i];
    y[i] = game_info->block->y[i];
  }

  while (!check_collision_xy(game_info, x, y)) {
    for (int i = 0; i < 4; ++i) {
      y[i] += 1;
    }
  }

  for (int i = 0; i < 4; ++i) {
    y[i] -= 1;
  }
}

void cls(WINDOW* window) {
  for (int i = 1; i <= WIDTH * W_SCALE - 1; ++i) {
    for (int k = 1; k <= HEIGHT * H_SCALE; ++k) {
      mvwaddstr(window, k, i, "  ");
    }
  }
}
