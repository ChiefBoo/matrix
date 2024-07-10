#include "s21_matrix.h"

// cleaning and initialization
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error_code = 0;
  if (rows < 1 || columns < 1) {
    error_code = 1;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix == NULL) {
      error_code = 1;
    } else {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) {
          for (int j = 0; j < i; j++) {
            free(result->matrix[j]);
          }
          free(result->matrix);
          error_code = 1;
          break;
        }
      }
    }
  }
  return error_code;
}

void s21_remove_matrix(matrix_t *A) {
  if (is_correct(A)) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->rows = 0;
    A->columns = 0;
  }
}

// comparison
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int error_code = SUCCESS;
  if (((A->columns != B->columns) || (A->rows != B->rows)) || !is_correct(A) ||
      !is_correct(B)) {
    error_code = FAILURE;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-07) {
          error_code = FAILURE;
          break;
        }
      }
    }
  }
  return error_code;
}

// arithmetic
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error_code = 0;
  if (is_correct(A) && is_correct(B)) {
    if ((A->columns == B->columns) && (A->rows == B->rows)) {
      error_code = s21_create_matrix(A->rows, A->columns, result);
      if (!error_code) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
          }
        }
      }
    } else {
      error_code = 2;
    }
  } else {
    error_code = 1;
  }
  return error_code;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error_code = 0;
  if (is_correct(A) && is_correct(B)) {
    if ((A->columns == B->columns) && (A->rows == B->rows)) {
      error_code = s21_create_matrix(A->rows, A->columns, result);
      if (!error_code) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
          }
        }
      }
    } else {
      error_code = 2;
    }
  } else {
    error_code = 1;
  }
  return error_code;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error_code = 0;
  if (is_correct(A)) {
    error_code = s21_create_matrix(A->rows, A->columns, result);
    if (!error_code) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    }
  } else {
    error_code = 1;
  }
  return error_code;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error_code = 0;
  if (is_correct(A) && is_correct(B)) {
    if (A->columns == B->rows) {
      error_code = s21_create_matrix(A->rows, B->columns, result);
      if (!error_code) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < B->columns; j++) {
            for (int k = 0; k < B->rows; k++) {
              result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
            }
          }
        }
      }
    } else {
      error_code = 2;
    }
  } else {
    error_code = 1;
  }
  return error_code;
}

// matrix operations
int s21_transpose(matrix_t *A, matrix_t *result) {
  int error_code = 0;
  if (is_correct(A)) {
    error_code = s21_create_matrix(A->columns, A->rows, result);
    if (!error_code) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    }
  } else {
    error_code = 1;
  }
  return error_code;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error_code = 0;
  if (is_correct(A)) {
    if (A->columns == A->rows) {
      error_code = s21_create_matrix(A->columns, A->rows, result);
      if (!error_code) {
        if (A->rows == 1) {
          result->matrix[0][0] = 1;
        } else {
          for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
              matrix_t minor = {0};
              double det = 0.0;
              s21_create_matrix(A->columns - 1, A->rows - 1, &minor);
              get_minor(i, j, A, &minor);
              s21_determinant(&minor, &det);
              result->matrix[i][j] = pow(-1, (i + j)) * det;
              s21_remove_matrix(&minor);
            }
          }
        }
      }
    } else {
      error_code = 2;
    }
  } else {
    error_code = 1;
  }
  return error_code;
}
int s21_determinant(matrix_t *A, double *result) {
  int error_code = 0;
  *result = 0.0;
  if (is_correct(A)) {
    if (A->columns == A->rows) {
      *result = get_determinant(A);
    } else {
      error_code = 2;
    }
  } else {
    error_code = 1;
  }
  return error_code;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error_code = 0;
  if (is_correct(A)) {
    if (A->columns == A->rows) {
      double det = 0.0;
      error_code = s21_determinant(A, &det);
      if (fabs(det) < 1e-6 || error_code) {
        error_code = 2;
      } else {
        matrix_t adj_matrix = {0};
        if (!(error_code = s21_calc_complements(A, &adj_matrix))) {
          matrix_t tr_adj_matrix = {0};
          if (!(error_code = s21_transpose(&adj_matrix, &tr_adj_matrix))) {
            s21_create_matrix(A->rows, A->columns, result);
            for (int i = 0; i < A->rows; i++) {
              for (int j = 0; j < A->columns; j++)
                result->matrix[i][j] = tr_adj_matrix.matrix[i][j] / det;
            }
          }
          s21_remove_matrix(&tr_adj_matrix);
        }
        s21_remove_matrix(&adj_matrix);
      }
    } else {
      error_code = 2;
    }
  } else {
    error_code = 1;
  }
  return error_code;
}

// extra functions
int is_correct(matrix_t *A) {
  int error_code = 1;
  if (A == NULL || A->matrix == NULL || A->columns < 1 || A->rows < 1)
    error_code = 0;
  return error_code;
}

double get_determinant(matrix_t *A) {  // -1 ^ (i+1) * a1i * M1i
  double det = 0.0;
  double sign = 1.0;
  if (A->rows == 1) {
    det = A->matrix[0][0];
  } else if (A->rows == 2) {
    det = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    matrix_t minor = {0};
    s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
    for (int i = 0; i < A->rows; i++) {
      get_minor(0, i, A, &minor);
      sign = (i % 2) ? -1.0 : 1.0;
      det += sign * A->matrix[0][i] * get_determinant(&minor);
    }
    s21_remove_matrix(&minor);
  }
  return det;
}

void get_minor(int row, int column, matrix_t *A, matrix_t *result) {
  for (int i = 0, res_i = 0; i < A->rows; i++) {
    for (int j = 0, res_j = 0; j < A->columns; j++) {
      if (i != row && j != column) {
        result->matrix[res_i][res_j] = A->matrix[i][j];
        res_j++;
        if (res_j == A->columns - 1) {
          res_j = 0;
          res_i++;
        }
      }
    }
  }
}
