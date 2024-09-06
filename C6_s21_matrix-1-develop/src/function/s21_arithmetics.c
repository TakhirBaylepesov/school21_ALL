#include "../s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return simpleArithmetics(A, B, result, 1);
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return simpleArithmetics(A, B, result, 2);
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = (s21_is_bad_matrix(A) || s21_is_bad_matrix(B));

  if (status == 0 && (status = A->columns != B->rows ? 2 : 0) == 0) {
    if ((status = s21_create_matrix(A->rows, B->columns, result)) == 0) {
      for (int x = 0; x < A->rows; x += 1) {
        for (int y = 0; y < B->columns; y += 1) {
          for (int z = 0; z < B->rows; z += 1)
            result->matrix[x][y] += A->matrix[x][z] * B->matrix[z][y];
        }
      }
    }
  }

  return status;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int status = s21_is_bad_matrix(A);

  if (status == 0) {
    if ((status = s21_create_matrix(A->rows, A->columns, result)) == 0) {
      for (int x = 0; x < A->rows; x += 1) {
        for (int y = 0; y < A->columns; y += 1)
          result->matrix[x][y] = A->matrix[x][y] * number;
      }
    }
  }

  return status;
}

int simpleArithmetics(matrix_t *A, matrix_t *B, matrix_t *result, int znak) {
  int status = s21_is_bad_eq_matrix(A, B);

  if (status == 0) {
    if ((status = s21_create_matrix(A->rows, A->columns, result)) == 0) {
      for (int x = 0; x < A->rows; x += 1) {
        for (int y = 0; y < A->columns; y += 1) {
          if (znak == 1)
            result->matrix[x][y] = A->matrix[x][y] + B->matrix[x][y];
          else if (znak == 2)
            result->matrix[x][y] = A->matrix[x][y] - B->matrix[x][y];
        }
      }
    }
  }

  return status;
}