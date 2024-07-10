#include "../test_includes/s21_tests.h"

START_TEST(mult_mat_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  matrix_t res = {0};
  int rows = 4;
  int cols = 5;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 0);
  ck_assert_int_eq(s21_create_matrix(cols, rows, &B), 0);
  ck_assert_int_eq(s21_create_matrix(rows, rows, &C), 0);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      A.matrix[i][j] = (float)(1 + rand() % 100);
    }
  }
  for (int i = 0; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
      B.matrix[i][j] = (float)(1 + rand() % 100);
    }
  }

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      C.matrix[i][j] = 0;
      for (int k = 0; k < A.columns; k++)
        C.matrix[i][j] += A.matrix[i][k] * B.matrix[k][j];
    }
  }

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &res), 0);
  ck_assert_int_eq(s21_eq_matrix(&C, &res), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(mult_mat_2) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t res = {0};
  int rows = 4;
  int cols = 5;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 0);
  ck_assert_int_eq(s21_create_matrix(rows, cols, &B), 0);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &res), 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(mult_mat_3) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t res = {0};
  int rows = 4;
  int cols = 5;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 0);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      A.matrix[i][j] = (float)(1 + rand() % 100);
    }
  }
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &res), 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(mult_mat_4) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t res = {0};
  int rows = 1;
  int cols = 1;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 0);
  ck_assert_int_eq(s21_create_matrix(cols, rows, &B), 0);
  A.matrix[0][0] = 5;
  B.matrix[0][0] = 3;

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &res), 0);
  ck_assert_int_eq(15, res.matrix[0][0]);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(mult_mat_5) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t res = {0};

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &res), 1);
}
END_TEST

Suite *suite_s21_mult_matrix(void) {
  Suite *s = suite_create("\033[1;31m--MULT_MATRIX--\033[m");
  TCase *tc = tcase_create("mult_mat_tc");

  tcase_add_test(tc, mult_mat_1);
  tcase_add_test(tc, mult_mat_2);
  tcase_add_test(tc, mult_mat_3);
  tcase_add_test(tc, mult_mat_4);
  tcase_add_test(tc, mult_mat_5);
  suite_add_tcase(s, tc);

  return s;
}
