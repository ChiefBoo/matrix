#include "../test_includes/s21_tests.h"

START_TEST(calc_complement_1) {
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

  B.matrix[0][0] = 2;
  B.matrix[0][1] = 2;
  B.matrix[0][2] = -2;

  B.matrix[1][0] = -1;
  B.matrix[1][1] = 0;
  B.matrix[1][2] = 1;

  B.matrix[2][0] = 1;
  B.matrix[2][1] = -2;
  B.matrix[2][2] = 1;

  ck_assert_int_eq(s21_calc_complements(&A, &res), 0);
  ck_assert_int_eq(s21_eq_matrix(&B, &res), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(calc_complement_2) {
  matrix_t A = {0};
  matrix_t res = {0};
  int rows = 4;
  int cols = 5;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 0);
  ck_assert_int_eq(s21_calc_complements(&A, &res), 2);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(calc_complement_3) {
  matrix_t A = {0};
  matrix_t res = {0};
  ck_assert_int_eq(s21_calc_complements(&A, &res), 1);
}
END_TEST

START_TEST(calc_complement_4) {
  matrix_t A = {0};
  matrix_t res = {0};
  int rows = 1;
  int cols = 1;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 0);
  ck_assert_int_eq(s21_calc_complements(&A, &res), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
}
END_TEST

Suite *suite_s21_calc_complements(void) {
  Suite *s = suite_create("\033[1;31m--CALC_COMPLEMENTS--\033[m");
  TCase *tc = tcase_create("calc_complements_tc");

  tcase_add_test(tc, calc_complement_1);
  tcase_add_test(tc, calc_complement_2);
  tcase_add_test(tc, calc_complement_3);
  tcase_add_test(tc, calc_complement_4);
  suite_add_tcase(s, tc);

  return s;
}
