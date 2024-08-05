#include "tetris.h"

void rotate_I_0(int x[4], int y[4]) {
  x[0] += 2;
  x[1] += 1;
  x[3] -= 1;
  y[0] -= 3;
  y[1] -= 2;
  y[2] -= 1;
}

void rotate_I_1(int x[4], int y[4]) {
  x[0] -= 2;
  x[1] -= 1;
  x[3] += 1;
  y[0] += 3;
  y[1] += 2;
  y[2] += 1;
}

void rotate_T_0(int x[4], int y[4]) {
  x[3] -= 1;
  y[3] -= 1;
}

void rotate_T_1(int x[4], int y[4]) {
  y[2] += 1;
  x[3] += 1;
  y[3] += 2;
}

void rotate_T_2(int x[4], int y[4]) {
  x[2] += 1;
  y[2] -= 2;
  y[3] -= 1;
}

void rotate_T_3(int x[4], int y[4]) {
  x[2] -= 1;
  y[2] += 1;
}

void rotate_S_0(int x[4], int y[4]) {
  y[0] -= 2;
  x[3] -= 2;
}

void rotate_S_1(int x[4], int y[4]) {
  y[0] += 2;
  x[3] += 2;
}

void rotate_Z_0(int x[4], int y[4]) {
  y[2] -= 2;
  x[3] -= 2;
}

void rotate_Z_1(int x[4], int y[4]) {
  y[2] += 2;
  x[3] += 2;
}

void rotate_L_0(int x[4], int y[4]) {
  x[0] += 1;
  y[0] -= 1;
  y[1] -= 2;
  x[3] -= 1;
  y[3] += 1;
}

void rotate_L_1(int x[4], int y[4]) {
  x[0] += 1;
  y[0] += 1;
  y[1] += 2;
  x[2] += 1;
  y[2] += 1;
}

void rotate_L_2(int x[4], int y[4]) {
  x[0] -= 2;
  y[0] -= 1;
  x[2] -= 2;
  y[2] -= 1;
}

void rotate_L_3(int x[4], int y[4]) {
  y[0] += 1;
  x[2] += 1;
  x[3] += 1;
  y[3] -= 1;
}

void rotate_J_0(int x[4], int y[4]) {
  y[0] += 1;
  x[2] -= 1;
  y[2] += 1;
  x[3] -= 1;
  y[3] -= 2;
}

void rotate_J_1(int x[4], int y[4]) {
  y[0] -= 1;
  x[1] -= 1;
  y[1] += 1;
  x[3] += 1;
  y[3] += 2;
}

void rotate_J_2(int x[4], int y[4]) {
  x[2] -= 1;
  y[2] -= 2;
  x[3] -= 1;
  y[3] -= 2;
}

void rotate_J_3(int x[4], int y[4]) {
  x[1] += 1;
  y[1] -= 1;
  x[2] += 2;
  y[2] += 1;
  x[3] += 1;
  y[3] += 2;
}

void choose_rotation(GameInfo_t* game_info, int x[4], int y[4]) {
  switch (game_info->block->type) {
    case Oshape:
      break;
    case Ishape:
      switch (game_info->block->rotation) {
        case 0:
        case 2:
          rotate_I_0(x, y);
          break;
        case 1:
        case 3:
          rotate_I_1(x, y);
          break;
      }
      break;
    case Tshape:
      switch (game_info->block->rotation) {
        case 0:
          rotate_T_0(x, y);
          break;
        case 1:
          rotate_T_1(x, y);
          break;
        case 2:
          rotate_T_2(x, y);
          break;
        case 3:
          rotate_T_3(x, y);
          break;
      }
      break;
    case Sshape:
      switch (game_info->block->rotation) {
        case 0:
        case 2:
          rotate_S_0(x, y);
          break;
        case 1:
        case 3:
          rotate_S_1(x, y);
          break;
      }
      break;
    case Zshape:
      switch (game_info->block->rotation) {
        case 0:
        case 2:
          rotate_Z_0(x, y);
          break;
        case 1:
        case 3:
          rotate_Z_1(x, y);
          break;
      }
      break;
    case Lshape:
      switch (game_info->block->rotation) {
        case 0:
          rotate_L_0(x, y);
          break;
        case 1:
          rotate_L_1(x, y);
          break;
        case 2:
          rotate_L_2(x, y);
          break;
        case 3:
          rotate_L_3(x, y);
          break;
      }
      break;
    case Jshape:
      switch (game_info->block->rotation) {
        case 0:
          rotate_J_0(x, y);
          break;
        case 1:
          rotate_J_1(x, y);
          break;
        case 2:
          rotate_J_2(x, y);
          break;
        case 3:
          rotate_J_3(x, y);
          break;
      }
      break;
  }
}
