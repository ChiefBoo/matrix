#include "../test_includes/s21_tests.h"

START_TEST(sub_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  matrix_t res = {0};
  int rows = 4;
  int cols = 5;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 0);
  ck_assert_int_eq(s21_create_matrix(rows, cols, &B), 0);
  ck_assert_int_eq(s21_create_matrix(rows, cols, &C), 0);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      A.matrix[i][j] = (float)(1 + rand() % 100);
      B.matrix[i][j] = (float)(1 + rand() % 100);
      C.matrix[i][j] = A.matrix[i][j] - B.matrix[i][j];
    }
  }
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &res), 0);
  ck_assert_int_eq(s21_eq_matrix(&C, &res), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(sub_2) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t res = {0};
  int rows = 4;
  int cols = 5;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 0);
  ck_assert_int_eq(s21_create_matrix(rows + 1, cols + 1, &B), 0);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &res), 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub_3) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t res = {0};
  int rows = 4;
  int cols = 5;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 0);
  ck_assert_int_eq(s21_create_matrix(-2, cols, &B), 1);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &res), 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(sub_4) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t res = {0};
  int rows = 4;
  int cols = 5;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 0);
  ck_assert_int_eq(s21_create_matrix(cols, rows, &B), 0);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &res), 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub_5) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t res = {0};

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &res), 1);
}
END_TEST

Suite *suite_s21_sub_matrix(void) {
  Suite *s = suite_create("\033[1;31m--SUB--\033[m");
  TCase *tc = tcase_create("sub_tc");

  tcase_add_test(tc, sub_1);
  tcase_add_test(tc, sub_2);
  tcase_add_test(tc, sub_3);
  tcase_add_test(tc, sub_4);
  tcase_add_test(tc, sub_5);
  suite_add_tcase(s, tc);

  return s;
}
