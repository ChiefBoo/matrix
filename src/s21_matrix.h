#ifndef SRC_S21_MATRIX_H
#define SRC_S21_MATRIX_H

#include <math.h>
#include <stdio.h>  // delete later
#include <stdlib.h>

// status for eq_matrix
#define SUCCESS 1
#define FAILURE 0

// status for another functions
// 0 - OK
// 1 - Error, incorrect matrix
// 2 - Calculation error

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// cleaning and initialization
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);

// comparison
int s21_eq_matrix(matrix_t *A, matrix_t *B);

// arithmetic
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// matrix operations
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// extra functions
int is_correct(matrix_t *A);
void get_minor(int row, int column, matrix_t *A, matrix_t *result);
double get_determinant(matrix_t *A);

#endif  // SRC_S21_MATRIX_H
