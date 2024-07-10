#include "../test_includes/s21_tests.h"

START_TEST(inverse_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t res = {0};
  int rows = 3;
  int cols = 3;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 0);
  ck_assert_int_eq(s21_create_matrix(rows, cols, &B), 0);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 1;
  A.matrix[0][2] = 1;

  A.matrix[1][0] = 1;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 3;

  A.matrix[2][0] = 1;
  A.matrix[2][1] = 0;
  A.matrix[2][2] = 1;

  B.matrix[0][0] = 1;
  B.matrix[0][1] = -0.5;
  B.matrix[0][2] = 0.5;

  B.matrix[1][0] = 1;
  B.matrix[1][1] = 0;
  B.matrix[1][2] = -1;

  B.matrix[2][0] = -1;
  B.matrix[2][1] = 0.5;
  B.matrix[2][2] = 0.5;

  ck_assert_int_eq(s21_inverse_matrix(&A, &res), 0);
  ck_assert_int_eq(s21_eq_matrix(&B, &res), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(inverse_2) {
  matrix_t A = {0};
  matrix_t res = {0};
  int rows = 4;
  int cols = 5;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 0);
  ck_assert_int_eq(s21_inverse_matrix(&A, &res), 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_3) {
  matrix_t A = {0};
  matrix_t res = {0};
  ck_assert_int_eq(s21_inverse_matrix(&A, &res), 1);
}
END_TEST

START_TEST(inverse_4) {
  matrix_t A = {0};
  matrix_t res = {0};
  int rows = 1;
  int cols = 1;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 0);
  A.matrix[0][0] = 10;
  ck_assert_int_eq(s21_inverse_matrix(&A, &res), 0);
  ck_assert_double_eq_tol(res.matrix[0][0], (1.0 / A.matrix[0][0]), 1e-6);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(inverse_5) {
  matrix_t A = {0};
  matrix_t res = {0};
  int rows = 4;
  int cols = 4;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 0);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      A.matrix[i][j] = 4;
    }
  }
  ck_assert_int_eq(s21_inverse_matrix(&A, &res), 2);
  s21_remove_matrix(&A);
}
END_TEST

Suite *suite_s21_inverse_matrix(void) {
  Suite *s = suite_create("\033[1;31m--INVERSE--\033[m");
  TCase *tc = tcase_create("inverse_tc");

  tcase_add_test(tc, inverse_1);
  tcase_add_test(tc, inverse_2);
  tcase_add_test(tc, inverse_3);
  tcase_add_test(tc, inverse_4);
  tcase_add_test(tc, inverse_5);
  suite_add_tcase(s, tc);

  return s;
}
