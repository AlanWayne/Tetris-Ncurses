#include "test.h"

void arrcpy(int a[4], int b[4]) {
  for (int i = 0; i < 4; ++i) a[i] = b[i];
}

START_TEST(test_move_left) {
  GameInfo_t gi;
  GameInfo_t* game_info = &gi;
  back_set_up(game_info);

  int x[4] = {0};
  int y[4] = {0};
  arrcpy(x, game_info->block->x);
  arrcpy(y, game_info->block->y);
  user_input(Left, game_info);
  for (int i = 0; i < 4; ++i) {
    ck_assert_int_gt(x[i], game_info->block->x[i]);
    ck_assert_int_eq(y[i], game_info->block->y[i]);
  }

  back_tear_down(game_info);
}
END_TEST

START_TEST(test_move_right) {
  GameInfo_t gi;
  GameInfo_t* game_info = &gi;
  back_set_up(game_info);

  int x[4] = {0};
  int y[4] = {0};
  arrcpy(x, game_info->block->x);
  arrcpy(y, game_info->block->y);

  user_input(Right, game_info);

  for (int i = 0; i < 4; ++i) {
    ck_assert_int_lt(x[i], game_info->block->x[i]);
    ck_assert_int_eq(y[i], game_info->block->y[i]);
  }

  back_tear_down(game_info);
}
END_TEST

START_TEST(test_move_down) {
  GameInfo_t gi;
  GameInfo_t* game_info = &gi;
  back_set_up(game_info);

  int x[4] = {0};
  int y[4] = {0};
  arrcpy(x, game_info->block->x);
  arrcpy(y, game_info->block->y);

  for (int i = 0; i < 60; ++i) moving_down(game_info);

  for (int i = 0; i < 4; ++i) {
    ck_assert_int_eq(x[i], game_info->block->x[i]);
    ck_assert_int_lt(y[i], game_info->block->y[i]);
  }

  back_tear_down(game_info);
}
END_TEST

START_TEST(test_move_down_auto) {
  GameInfo_t gi;
  GameInfo_t* game_info = &gi;
  back_set_up(game_info);

  backend(game_info);

  ck_assert_int_ne(1, 2);

  back_tear_down(game_info);
}
END_TEST

START_TEST(test_drop_and_attach) {
  GameInfo_t gi;
  GameInfo_t* game_info = &gi;
  back_set_up(game_info);

  user_input(Down, game_info);

  int result = 0;
  for (int i = 0; i < WIDTH; ++i) {
    result += game_info->field[i][HEIGHT - 1];
  }

  ck_assert_int_gt(result, 0);

  back_tear_down(game_info);
}
END_TEST

START_TEST(test_block_to_block_collision) {
  GameInfo_t gi;
  GameInfo_t* game_info = &gi;
  back_set_up(game_info);

  user_input(Down, game_info);
  user_input(Down, game_info);

  int result = 0;
  for (int i = 0; i < WIDTH; ++i) {
    result += game_info->field[i][HEIGHT - 2];
  }

  ck_assert_int_gt(result, 0);

  back_tear_down(game_info);
}
END_TEST

START_TEST(test_rotation) {
  GameInfo_t gi;
  GameInfo_t* game_info = &gi;
  back_set_up(game_info);

  int rotation = game_info->block->rotation;
  user_input(Action, game_info);

  ck_assert_int_lt(rotation, game_info->block->rotation);

  for (int i = 0; i < 7; ++i) {
    spawn(game_info);
    game_info->block->type = i;
    choose_spawn(i, game_info->block->x, game_info->block->y);
    for (int k = 0; k < 4; ++k) {
      user_input(Action, game_info);
    }
  }

  back_tear_down(game_info);
}
END_TEST

START_TEST(test_pause) {
  GameInfo_t gi;
  GameInfo_t* game_info = &gi;
  back_set_up(game_info);

  user_input(Pause, game_info);

  ck_assert_int_eq(game_info->pause, TRUE);

  user_input(Pause, game_info);

  ck_assert_int_eq(game_info->pause, FALSE);

  back_tear_down(game_info);
}
END_TEST

START_TEST(test_line_and_save) {
  GameInfo_t gi;
  GameInfo_t* game_info = &gi;
  back_set_up(game_info);

  for (int i = 0; i < 5; ++i) {
    game_info->block->type = Oshape;
    choose_spawn(game_info->block->type, game_info->block->x,
                 game_info->block->y);
    for (int i = 0; i < 4; ++i) {
      game_info->next_block->y[i] += 1;
      game_info->next_block->x[i] -= 2;
    }

    switch (i) {
      case 1:
        user_input(Left, game_info);
        user_input(Left, game_info);
        break;
      case 2:
        user_input(Left, game_info);
        user_input(Left, game_info);
        user_input(Left, game_info);
        user_input(Left, game_info);
        break;
      case 3:
        user_input(Right, game_info);
        user_input(Right, game_info);
        break;
      case 4:
        user_input(Right, game_info);
        user_input(Right, game_info);
        user_input(Right, game_info);
        user_input(Right, game_info);
        break;
    }

    user_input(Down, game_info);
  }

  ck_assert_int_eq(game_info->score, 300);

  user_input(Terminate, game_info);
}
END_TEST

START_TEST(test_esc) {
  GameInfo_t gi;
  GameInfo_t* game_info = &gi;
  back_set_up(game_info);

  user_input(Terminate, game_info);

  ck_assert_int_eq(game_info->game_over, TRUE);
}
END_TEST

START_TEST(test_input) {
  GameInfo_t gi;
  GameInfo_t* game_info = &gi;
  back_set_up(game_info);

  UserAction_t action = 0;

  action = input_to_action(27);
  ck_assert_int_eq(action, Terminate);

  action = input_to_action('A');
  ck_assert_int_eq(action, Left);

  action = input_to_action('D');
  ck_assert_int_eq(action, Right);

  action = input_to_action('S');
  ck_assert_int_eq(action, Down);

  action = input_to_action('E');
  ck_assert_int_eq(action, Action);

  action = input_to_action('W');
  ck_assert_int_eq(action, Action);

  action = input_to_action(' ');
  ck_assert_int_eq(action, Pause);

  back_tear_down(game_info);
}
END_TEST

Suite* add_suite(void) {
  Suite* suite = suite_create("tetris_suite");
  TCase* tcase = tcase_create("tetris_tcase");

  tcase_add_test(tcase, test_move_left);
  tcase_add_test(tcase, test_move_right);
  tcase_add_test(tcase, test_move_down);
  tcase_add_test(tcase, test_move_down_auto);
  tcase_add_test(tcase, test_drop_and_attach);
  tcase_add_test(tcase, test_block_to_block_collision);
  tcase_add_test(tcase, test_rotation);
  tcase_add_test(tcase, test_pause);
  tcase_add_test(tcase, test_line_and_save);
  tcase_add_test(tcase, test_esc);
  tcase_add_test(tcase, test_input);

  suite_add_tcase(suite, tcase);

  return suite;
}

int main() {
  int number_failed;
  Suite* suite = add_suite();
  SRunner* srunner = srunner_create(suite);

  srunner_run_all(srunner, CK_NORMAL);
  number_failed = srunner_ntests_failed(srunner);
  srunner_free(srunner);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}