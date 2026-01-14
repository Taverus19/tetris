#include <stdio.h>

#include "test.h"

int main(void) {
  Suite *suite_1 = test_tetris();
  Suite *suite_2 = test_tetris_function();

  SRunner *sr = srunner_create(suite_1);
  srunner_add_suite(sr, suite_2);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_VERBOSE);
  int number_failed = srunner_ntests_failed(sr);
  printf("%s========== NUMBER OF FAILURES: %d ==========%s\n", YELLOW,
         number_failed, RESET);
  srunner_free(sr);

  return 0;
}