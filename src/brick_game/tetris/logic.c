#include "tetris.h"

// Main back
void backend(GameInfo_t* game_info) {
  UserAction_t action = input_to_action(getch());
  user_input(action, game_info);
  moving_down(game_info);
}

// Moving block down every <speed_game> (1 second at level 1)
void moving_down(GameInfo_t* game_info) {
  if (game_info->pause) return;

  static int counter = 0;
  counter += game_info->speed_io;
  if (counter >= game_info->speed_game - game_info->level * 75000) {
    counter = 0;
    move_down(game_info);
  }
}

// Spawn new block on top of the field
void spawn(GameInfo_t* game_info) {
  game_info->block->type = game_info->next_block->type;
  game_info->next_block->type = rand() % 7;
  game_info->block->rotation = 0;
  game_info->next_block->rotation = 0;
  game_info->pause = FALSE;
  choose_spawn(game_info->block->type, game_info->block->x,
               game_info->block->y);
  choose_spawn(game_info->next_block->type, game_info->next_block->x,
               game_info->next_block->y);
  for (int i = 0; i < 4; ++i) {
    game_info->next_block->y[i] += 1;
    game_info->next_block->x[i] -= 2;
  }
}

// Attach your block to pile, spawn new one
void attach(GameInfo_t* game_info) {
  for (int i = 0; i < 4; ++i) {
    game_info->field[game_info->block->x[i]][game_info->block->y[i]] = 1;
  }
  check_lines(game_info);
}

void check_lines(GameInfo_t* game_info) {
  int line = 0;
  for (int k = HEIGHT - 1; k >= 0; --k) {
    int sum = 0;
    for (int i = 0; i < WIDTH; ++i) sum += game_info->field[i][k];
    if (sum == WIDTH) {
      ++line;
      for (int k2 = k; k2 > 0; --k2)
        for (int i = 0; i < WIDTH; ++i)
          game_info->field[i][k2] = game_info->field[i][k2 - 1];
      ++k;
    }
  }
  game_info->score += pow(2, line) * 100 - 100;
  game_info->high_score = game_info->score > game_info->high_score
                              ? game_info->score
                              : game_info->high_score;
  game_info->level = game_info->score / 600 + 1;
  if (game_info->level > 10) game_info->level = 10;
}

// Check if collide with borders or other blocks
bool check_collision(GameInfo_t* game_info, int x_shift, int y_shift) {
  for (int i = 0; i < 4; ++i) {
    int x = game_info->block->x[i];
    int y = game_info->block->y[i];
    if (x + x_shift < 0 || x + x_shift >= WIDTH || y + y_shift >= HEIGHT)
      return TRUE;
    if (y + y_shift > 0 && game_info->field[x + x_shift][y + y_shift])
      return TRUE;
  }
  return FALSE;
}

// Check if collide with borders or other blocks (by coords)
bool check_collision_xy(GameInfo_t* game_info, int x[4], int y[4]) {
  for (int i = 0; i < 4; ++i) {
    if (x[i] < 0 || x[i] >= WIDTH || y[i] >= HEIGHT) return TRUE;
    if (y[i] > 0 && game_info->field[x[i]][y[i]]) return TRUE;
  }
  return FALSE;
}

void pause_game(GameInfo_t* game_info) {
  if (game_info->pause) {
    game_info->pause = FALSE;
  } else {
    game_info->pause = TRUE;
  }
}

void check_game_over(GameInfo_t* game_info) {
  for (int i = 0; i < WIDTH; ++i) {
    if (game_info->field[i][0]) game_info->game_over = TRUE;
  }
}