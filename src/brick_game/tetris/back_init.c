#include "tetris.h"

void load_score(GameInfo_t* game_info) {
  int buffer[1] = {0};
  game_info->high_score = 0;
  FILE* file = fopen("build/record.bin", "rb");
  if (file != NULL) {
    fread(buffer, sizeof(int), 1, file);
    game_info->high_score = buffer[0];
    fclose(file);
  }
}

void save_score(GameInfo_t* game_info) {
  int buffer[1] = {0};
  FILE* file = fopen("build/record.bin", "wb");
  if (file != NULL) {
    buffer[0] = game_info->high_score;
    fwrite(buffer, sizeof(int), 1, file);
    fclose(file);
  }
}

void back_set_up(GameInfo_t* game_info) {
  game_info->field = (int**)malloc(sizeof(int*) * WIDTH);
  for (int i = 0; i < WIDTH; ++i) {
    game_info->field[i] = (int*)malloc(sizeof(int) * HEIGHT);
    for (int k = 0; k < HEIGHT; ++k) {
      game_info->field[i][k] = 0;
    }
  }
  load_score(game_info);
  srand(time(NULL));
  Block_t* block = (Block_t*)malloc(sizeof(Block_t));
  game_info->block = block;
  Block_t* next_block = (Block_t*)malloc(sizeof(Block_t));
  game_info->next_block = next_block;
  game_info->next_block->type = rand() % 7;
  spawn(game_info);
  game_info->speed_game = SEC;
  game_info->speed_io = SEC / FPS;
  game_info->level = 1;
  game_info->score = 0;
  game_info->pause = FALSE;
  game_info->game_over = FALSE;
}

void back_tear_down(GameInfo_t* game_info) {
  save_score(game_info);
  for (int i = 0; i < WIDTH; ++i) {
    free(game_info->field[i]);
  }
  free(game_info->field);
  free(game_info->block);
  free(game_info->next_block);
}