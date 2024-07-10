#include "../test_includes/s21_tests.h"

START_TEST(mult_num_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t res = {0};
  int rows = 4;
  int cols = 5;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 0);
  ck_assert_int_eq(s21_create_matrix(rows, cols, &B), 0);
  double number = 3.2;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      A.matrix[i][j] = (float)(1 + rand() % 100);
      B.matrix[i][j] = A.matrix[i][j] * number;
    }
  }
  ck_assert_int_eq(s21_mult_number(&A, number, &res), 0);
  ck_assert_int_eq(s21_eq_matrix(&B, &res), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(mult_num_2) {
  matrix_t A = {0};
  matrix_t res = {0};
  int rows = -4;
  int cols = 5;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 1);
  double number = 3.2;
  ck_assert_int_eq(s21_mult_number(&A, number, &res), 1);
}
END_TEST

START_TEST(mult_num_3) {
  matrix_t A = {0};
  matrix_t res = {0};
  double number = 3.2;
  ck_assert_int_eq(s21_mult_number(&A, number, &res), 1);
}
END_TEST

START_TEST(mult_num_4) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t res = {0};
  int rows = 4;
  int cols = 5;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 0);
  ck_assert_int_eq(s21_create_matrix(rows, cols, &B), 0);
  double number = -3.2;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      A.matrix[i][j] = (float)(1 + rand() % 100);
      B.matrix[i][j] = A.matrix[i][j] * number;
    }
  }
  ck_assert_int_eq(s21_mult_number(&A, number, &res), 0);
  ck_assert_int_eq(s21_eq_matrix(&B, &res), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);
}
END_TEST

Suite *suite_s21_mult_number(void) {
  Suite *s = suite_create("\033[1;31m--MULT_NUMBER--\033[m");
  TCase *tc = tcase_create("mult_num_tc");

  tcase_add_test(tc, mult_num_1);
  tcase_add_test(tc, mult_num_2);
  tcase_add_test(tc, mult_num_3);
  tcase_add_test(tc, mult_num_4);
  suite_add_tcase(s, tc);

  return s;
}
