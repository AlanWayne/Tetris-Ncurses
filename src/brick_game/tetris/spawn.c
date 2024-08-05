#include "tetris.h"

void spawn_O(int x[4], int y[4]) {
  x[0] = WIDTH / 2 - 1;
  x[1] = WIDTH / 2;
  x[2] = WIDTH / 2 - 1;
  x[3] = WIDTH / 2;
  y[0] = 0;
  y[1] = 0;
  y[2] = 1;
  y[3] = 1;
}

void spawn_I(int x[4], int y[4]) {
  x[0] = WIDTH / 2 - 2;
  x[1] = WIDTH / 2 - 1;
  x[2] = WIDTH / 2;
  x[3] = WIDTH / 2 + 1;
  y[0] = 0;
  y[1] = 0;
  y[2] = 0;
  y[3] = 0;
}

void spawn_T(int x[4], int y[4]) {
  x[0] = WIDTH / 2 - 1;
  x[1] = WIDTH / 2 - 1;
  x[2] = WIDTH / 2 - 2;
  x[3] = WIDTH / 2;
  y[0] = 0;
  y[1] = 1;
  y[2] = 0;
  y[3] = 0;
}

void spawn_S(int x[4], int y[4]) {
  x[0] = WIDTH / 2 - 2;
  x[1] = WIDTH / 2 - 1;
  x[2] = WIDTH / 2 - 1;
  x[3] = WIDTH / 2;
  y[0] = 1;
  y[1] = 1;
  y[2] = 0;
  y[3] = 0;
}

void spawn_Z(int x[4], int y[4]) {
  x[0] = WIDTH / 2 - 2;
  x[1] = WIDTH / 2 - 1;
  x[2] = WIDTH / 2 - 1;
  x[3] = WIDTH / 2;
  y[0] = 0;
  y[1] = 0;
  y[2] = 1;
  y[3] = 1;
}

void spawn_L(int x[4], int y[4]) {
  x[0] = WIDTH / 2 - 2;
  x[1] = WIDTH / 2 - 2;
  x[2] = WIDTH / 2 - 1;
  x[3] = WIDTH / 2;
  y[0] = 0;
  y[1] = 1;
  y[2] = 0;
  y[3] = 0;
}

void spawn_J(int x[4], int y[4]) {
  x[0] = WIDTH / 2 - 2;
  x[1] = WIDTH / 2 - 1;
  x[2] = WIDTH / 2;
  x[3] = WIDTH / 2;
  y[0] = 0;
  y[1] = 0;
  y[2] = 0;
  y[3] = 1;
}

void choose_spawn(BlockType_t type, int x[4], int y[4]) {
  switch (type) {
    case Oshape:
      spawn_O(x, y);
      break;
    case Ishape:
      spawn_I(x, y);
      break;
    case Tshape:
      spawn_T(x, y);
      break;
    case Sshape:
      spawn_S(x, y);
      break;
    case Zshape:
      spawn_Z(x, y);
      break;
    case Lshape:
      spawn_L(x, y);
      break;
    case Jshape:
      spawn_J(x, y);
      break;
  }
}