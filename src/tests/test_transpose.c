#include "../test_includes/s21_tests.h"

START_TEST(transpose_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t res = {0};
  int rows = 4;
  int cols = 5;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 0);
  ck_assert_int_eq(s21_create_matrix(cols, rows, &B), 0);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      float item = (float)(1 + rand() % 100);
      A.matrix[i][j] = item;
      B.matrix[j][i] = item;
    }
  }

  ck_assert_int_eq(s21_transpose(&A, &res), 0);
  ck_assert_int_eq(s21_eq_matrix(&B, &res), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(transpose_2) {
  matrix_t A = {0};
  matrix_t res = {0};
  int rows = -4;
  int cols = 5;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 1);
  ck_assert_int_eq(s21_transpose(&A, &res), 1);
}
END_TEST

START_TEST(transpose_3) {
  matrix_t A = {0};
  matrix_t res = {0};
  ck_assert_int_eq(s21_transpose(&A, &res), 1);
}
END_TEST

START_TEST(transpose_4) {
  matrix_t A = {0};
  matrix_t res = {0};
  int rows = 1;
  int cols = 1;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 0);
  A.matrix[0][0] = 5;
  ck_assert_int_eq(s21_transpose(&A, &res), 0);
  ck_assert_int_eq(s21_eq_matrix(&A, &res), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
}
END_TEST

Suite *suite_s21_transpose(void) {
  Suite *s = suite_create("\033[1;31m--TRANSPOSE--\033[m");
  TCase *tc = tcase_create("transpose_tc");

  tcase_add_test(tc, transpose_1);
  tcase_add_test(tc, transpose_2);
  tcase_add_test(tc, transpose_3);
  tcase_add_test(tc, transpose_4);
  suite_add_tcase(s, tc);

  return s;
}
