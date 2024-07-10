#include "../test_includes/s21_tests.h"

START_TEST(eq_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  int rows = 4;
  int cols = 5;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 0);
  ck_assert_int_eq(s21_create_matrix(rows, cols, &B), 0);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      float item = (float)(1 + rand() % 100);
      A.matrix[i][j] = item;
      B.matrix[i][j] = item;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_2) {
  matrix_t A = {0};
  matrix_t B = {0};
  int rows = 4;
  int cols = 5;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 0);
  ck_assert_int_eq(s21_create_matrix(rows, cols, &B), 0);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      float item = (float)(1 + rand() % 100);
      A.matrix[i][j] = item;
    }
  }
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      float item = (float)(1 + rand() % 100);
      B.matrix[i][j] = item;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_3) {
  matrix_t A = {0};
  matrix_t B = {0};
  int rows = 4;
  int cols = 5;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 0);
  ck_assert_int_eq(s21_create_matrix(rows + 1, cols + 1, &B), 0);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      float item = (float)(1 + rand() % 100);
      A.matrix[i][j] = item;
    }
  }
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      float item = (float)(1 + rand() % 100);
      B.matrix[i][j] = item;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_4) {
  matrix_t A = {0};
  matrix_t B = {0};
  int rows = 4;
  int cols = 5;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 0);
  ck_assert_int_eq(s21_create_matrix(-rows, -cols, &B), 1);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(eq_5) {
  matrix_t A = {0};
  matrix_t B = {0};
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
}
END_TEST

START_TEST(eq_6) {
  matrix_t A = {0};
  matrix_t B = {0};
  int rows = 1;
  int cols = 1;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 0);
  ck_assert_int_eq(s21_create_matrix(rows, cols, &B), 0);
  A.matrix[0][0] = 1;
  B.matrix[0][0] = 1;
  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_7) {
  matrix_t A = {0};
  matrix_t B = {0};
  int rows = 1;
  int cols = 1;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 0);
  ck_assert_int_eq(s21_create_matrix(rows, cols, &B), 0);
  A.matrix[0][0] = 1;
  B.matrix[0][0] = -14;
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_8) {
  matrix_t A = {0};
  matrix_t B = {0};
  int rows = 2;
  int cols = 2;
  ck_assert_int_eq(s21_create_matrix(rows, cols, &A), 0);
  ck_assert_int_eq(s21_create_matrix(rows, cols, &B), 0);

  A.matrix[0][0] = 1.0000000000024234;
  A.matrix[0][0] = 2;
  A.matrix[0][0] = 3;
  A.matrix[0][0] = 4.0200000000000234234;
  B.matrix[0][0] = 1.0000000003674;
  B.matrix[0][0] = 2;
  B.matrix[0][0] = 3.000000000005;
  B.matrix[0][0] = 4.02000000000002384754;
  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *suite_s21_eq_matrix(void) {
  Suite *s = suite_create("\033[1;31m--EQ--\033[m");
  TCase *tc = tcase_create("eq_tc");

  tcase_add_test(tc, eq_1);
  tcase_add_test(tc, eq_2);
  tcase_add_test(tc, eq_3);
  tcase_add_test(tc, eq_4);
  tcase_add_test(tc, eq_5);
  tcase_add_test(tc, eq_6);
  tcase_add_test(tc, eq_7);
  tcase_add_test(tc, eq_8);
  suite_add_tcase(s, tc);

  return s;
}
