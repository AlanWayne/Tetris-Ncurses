#ifndef TETRIS_H
#define TETRIS_H

#define _X_OPEN_SOURCE_EXTENDED
#include <locale.h>
#include <math.h>
#include <ncursesw/curses.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>

typedef enum {
  NoInput,
  Pause,
  Terminate,
  Left,
  Right,
  Down,
  Action
} UserAction_t;

typedef struct WIN {
  WINDOW* window;
  int width;
  int height;
  int pos_x;
  int pos_y;
} WIN;

typedef enum {
  Oshape,
  Ishape,
  Tshape,
  Sshape,
  Zshape,
  Lshape,
  Jshape,
} BlockType_t;

typedef struct {
  BlockType_t type;
  int rotation;
  int x[4];
  int y[4];
} Block_t;

typedef struct {
  int** field;
  Block_t* block;
  Block_t* next_block;
  int score;
  int high_score;
  int level;
  bool game_over;
  int speed_game;
  int speed_io;
  bool pause;
  WIN* main_window;
  WIN* game_window;
  WIN* next_window;
  WIN* stat_window;
} GameInfo_t;

#define WIDTH 10
#define HEIGHT 20
#define W_SCALE 4
#define H_SCALE 2
#define SEC 1000000
#define FPS 60

// back_init
void back_set_up(GameInfo_t* game_info);
void back_tear_down(GameInfo_t* game_info);

// input
UserAction_t input_to_action(int input);
void user_input(UserAction_t action, GameInfo_t* game_info);

// logic
void backend(GameInfo_t* game_info);
void moving_down(GameInfo_t* game_info);
void spawn(GameInfo_t* game_info);
void attach(GameInfo_t* game_info);
void check_lines(GameInfo_t* game_info);
bool check_collision(GameInfo_t* game_info, int x_shift, int y_shift);
bool check_collision_xy(GameInfo_t* game_info, int x[4], int y[4]);
void pause_game(GameInfo_t* game_info);
void check_game_over(GameInfo_t* game_info);

// movement
bool move_down(GameInfo_t* game_info);
void move_left(GameInfo_t* game_info);
void move_right(GameInfo_t* game_info);
void drop(GameInfo_t* game_info);
void rotate(GameInfo_t* game_info);

// spawn
void choose_spawn(BlockType_t type, int x[4], int y[4]);

// rotation
void choose_rotation(GameInfo_t* game_info, int x[4], int y[4]);

#endif