#include "tetris.h"
// #include "controls.h"

// Convert int <input> to UserAction_t <action>
UserAction_t input_to_action(int input) {
  UserAction_t action = NoInput;
  switch (input) {
    case 27:
      action = Terminate;
      break;
    case 'A':
    case 'a':
      action = Left;
      break;
    case 'D':
    case 'd':
      action = Right;
      break;
    case 'S':
    case 's':
      action = Down;
      break;
    case 'W':
    case 'w':
    case 'E':
    case 'e':
      action = Action;
      break;
    case ' ':
      action = Pause;
      break;
  }
  return action;
}

// Call for specific behavior depending on <action>
void user_input(UserAction_t action, GameInfo_t* game_info) {
  switch (action) {
    case Terminate:
      game_info->game_over = TRUE;
      break;
    case Left:
      move_left(game_info);
      break;
    case Right:
      move_right(game_info);
      break;
    case Down:
      // move_down(game_info);
      drop(game_info);
      break;
    case Action:
      rotate(game_info);
      break;
    case Pause:
      pause_game(game_info);
      break;
    case NoInput:
      break;
  }
}