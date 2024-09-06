#include "../s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int status = s21_is_bad_eq_matrix(A, B) == 0;

  for (int x = 0; status == 1 && x < A->rows; x += 1) {
    for (int y = 0; status == 1 && y < A->columns; y += 1) {
      if (fabs(A->matrix[x][y] - B->matrix[x][y]) > 1e-07) status = FAILURE;
    }
  }

  return status;
}