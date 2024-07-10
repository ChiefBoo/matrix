#include "../test_includes/s21_tests.h"

START_TEST(det_1) {
  matrix_t A = {0};
  int rows = 3;
  int cols = 3;
  double det = 0.0;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 0);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 1;
  A.matrix[0][2] = 1;

  A.matrix[1][0] = 1;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 3;

  A.matrix[2][0] = 1;
  A.matrix[2][1] = 0;
  A.matrix[2][2] = 1;

  ck_assert_int_eq(s21_determinant(&A, &det), 0);
  ck_assert_double_eq_tol(det, 2, 1e-6);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(det_2) {
  matrix_t A = {0};
  double det = 0.0;
  int rows = 4;
  int cols = 5;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 0);
  ck_assert_int_eq(s21_determinant(&A, &det), 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(det_3) {
  matrix_t A = {0};
  double det = 0.0;
  ck_assert_int_eq(s21_determinant(&A, &det), 1);
}
END_TEST

START_TEST(det_4) {
  matrix_t A = {0};
  double det = 0.0;
  int rows = 1;
  int cols = 1;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 0);
  A.matrix[0][0] = 5;
  ck_assert_int_eq(s21_determinant(&A, &det), 0);
  ck_assert_double_eq_tol(det, 5, 1e-6);
  s21_remove_matrix(&A);
}
END_TEST

Suite *suite_s21_determinant(void) {
  Suite *s = suite_create("\033[1;31m--DETERMINANT--\033[m");
  TCase *tc = tcase_create("det_tc");

  tcase_add_test(tc, det_1);
  tcase_add_test(tc, det_2);
  tcase_add_test(tc, det_3);
  tcase_add_test(tc, det_4);
  suite_add_tcase(s, tc);

  return s;
}
