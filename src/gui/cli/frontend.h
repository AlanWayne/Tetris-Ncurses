#ifndef FRONTEND_H
#define FRONTEND_H

#include "../../brick_game/tetris/tetris.h"

// tetris.c
void tetris();
void game_loop();
void set_up(GameInfo_t* game_info);
void tear_down(GameInfo_t* game_info);

// front_init
WIN* create_window(const int height, const int width, const int pos_x,
                   const int pos_y);
void front_set_up(GameInfo_t* game_info);
void front_tear_down(GameInfo_t* game_info);

// draw
void frontend(GameInfo_t* game_info);
void draw_game(GameInfo_t* game_info);
void draw_pause(GameInfo_t* game_info);
void draw_block(WINDOW* window, int x[4], int y[4], int type);
void draw_pile(GameInfo_t* game_info);
void draw_next(GameInfo_t* game_info);
void draw_stat(GameInfo_t* game_info);
void draw_shadow(GameInfo_t* game_info);
void calc_shadow(GameInfo_t* game_info, int x[4], int y[4]);

// print
void print_char(WINDOW* window, int y, int x, int type);
void draw_segment(WINDOW* window, int y, int x, int type);
void cls(WINDOW* window);

#endif