#include "tetris.h"

// Move block down on 1 unit
bool move_down(GameInfo_t* game_info) {
  if (game_info->pause) return FALSE;

  if (!check_collision(game_info, 0, 1)) {
    for (int i = 0; i < 4; ++i) game_info->block->y[i] += 1;
    return TRUE;
  }
  attach(game_info);
  check_game_over(game_info);
  spawn(game_info);
  return FALSE;
}

// Move block left on 1 unit
void move_left(GameInfo_t* game_info) {
  if (game_info->pause) return;

  if (!check_collision(game_info, -1, 0))
    for (int i = 0; i < 4; ++i) game_info->block->x[i] -= 1;
}

// Move block right on 1 unit
void move_right(GameInfo_t* game_info) {
  if (game_info->pause) return;

  if (!check_collision(game_info, 1, 0))
    for (int i = 0; i < 4; ++i) game_info->block->x[i] += 1;
}

// Move block to the possible bottom
void drop(GameInfo_t* game_info) {
  if (game_info->pause) return;

  for (int i = 0; i < 20; ++i) {
    if (!move_down(game_info)) break;
  }
}

void rotate(GameInfo_t* game_info) {
  if (game_info->pause) return;

  int x[4] = {0};
  int y[4] = {0};
  for (int i = 0; i < 4; ++i) {
    x[i] = game_info->block->x[i];
    y[i] = game_info->block->y[i];
  }
  choose_rotation(game_info, x, y);
  if (!check_collision_xy(game_info, x, y)) {
    for (int i = 0; i < 4; ++i) {
      game_info->block->x[i] = x[i];
      game_info->block->y[i] = y[i];
    }
    game_info->block->rotation += game_info->block->rotation > 2 ? -3 : 1;
  }
}