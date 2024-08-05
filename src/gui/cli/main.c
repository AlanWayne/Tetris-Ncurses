#include "frontend.h"

// Entry poing
int main() {
  tetris();
  return 0;
}

// Main function
void tetris() {
  GameInfo_t game_info;
  set_up(&game_info);
  game_loop(&game_info);
  tear_down(&game_info);
}

// Game Loop
void game_loop(GameInfo_t* game_info) {
  pause_game(game_info);
  while (!game_info->game_over) {
    backend(game_info);
    frontend(game_info);
    usleep(game_info->speed_io);
  }
}

// Initialization of environment (malloc, declaration)
void set_up(GameInfo_t* game_info) {
  back_set_up(game_info);
  front_set_up(game_info);
}

// Termination of environment (free)
void tear_down(GameInfo_t* game_info) {
  front_tear_down(game_info);
  back_tear_down(game_info);
}