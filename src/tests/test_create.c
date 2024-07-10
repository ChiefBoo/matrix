#include "../test_includes/s21_tests.h"

START_TEST(create_1) {
  matrix_t A = {0};
  int rows = 4;
  int cols = 5;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 0);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      A.matrix[i][j] = 0;
      ck_assert_ldouble_eq_tol(0, A.matrix[i][j], 1e-07);
    }
  }
  ck_assert_int_eq(A.rows, rows);
  ck_assert_int_eq(A.columns, cols);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(create_2) {
  matrix_t A = {0};
  int rows = -4;
  int cols = 5;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 1);
}
END_TEST

START_TEST(create_3) {
  matrix_t A = {0};
  int rows = 5;
  int cols = 0;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 1);
}
END_TEST

START_TEST(create_4) {
  matrix_t A = {0};
  int rows = 1;
  int cols = 1;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 0);
  ck_assert_ldouble_eq_tol(0, A.matrix[0][0], 1e-07);
  ck_assert_int_eq(A.rows, rows);
  ck_assert_int_eq(A.columns, cols);
  s21_remove_matrix(&A);
}
END_TEST

Suite *suite_s21_create_matrix(void) {
  Suite *s = suite_create("\033[1;31m--CREATE--\033[m");
  TCase *tc = tcase_create("create_tc");

  tcase_add_test(tc, create_1);
  tcase_add_test(tc, create_2);
  tcase_add_test(tc, create_3);
  tcase_add_test(tc, create_4);
  suite_add_tcase(s, tc);

  return s;
}
