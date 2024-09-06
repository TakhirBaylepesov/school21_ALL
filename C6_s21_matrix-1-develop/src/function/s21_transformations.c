#include "../s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int status = s21_is_bad_matrix(A);

  if (status == 0) {
    if ((status = s21_create_matrix(A->columns, A->rows, result)) == 0) {
      for (int x = 0; x < A->rows; x += 1) {
        for (int y = 0; y < A->columns; y += 1) {
          result->matrix[y][x] = A->matrix[x][y];
        }
      }
    }
  }

  return status;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (s21_is_bad_matrix(A) == SUCCESS) return incorrect_matix;
  if (A->columns != A->rows) return calculation_error;

  double det = 0;
  int status = s21_determinant(A, &det);
  if (fabs(det) < 1e-6 || status != OK) return calculation_error;
  matrix_t aux = {0}, aux_transpose = {0};

  s21_calc_complements(A, &aux);
  s21_transpose(&aux, &aux_transpose);
  s21_create_matrix(A->rows, A->rows, result);

  for (int x = 0; x < A->rows; x += 1) {
    for (int y = 0; y < A->rows; y += 1) {
      result->matrix[x][y] = aux_transpose.matrix[x][y] / det;
    }
  }

  s21_remove_matrix(&aux_transpose);
  s21_remove_matrix(&aux);
  return OK;
}