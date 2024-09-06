#include "../s21_matrix.h"

void calcMinor(double **A, double **aux, int skipRow, int skipCol, int size) {
  for (int row = 0, x = 0; row < size; row += 1) {
    for (int col = 0, y = 0; col < size; col += 1) {
      if (row != skipRow && col != skipCol) {
        aux[x][y++] = A[row][col];
        if (y == size - 1) {
          y = 0;
          x++;
        }
      }
    }
  }
}

double calcDeterminant(matrix_t *A, int size) {
  if (size == 1) return A->matrix[0][0];

  matrix_t aux = {0};
  double result = 0;

  s21_create_matrix(size, size, &aux);
  for (int sign = 1, x = 0; x < size; x += 1, sign *= (-1)) {
    calcMinor(A->matrix, aux.matrix, 0, x, size);
    result += sign * A->matrix[0][x] * calcDeterminant(&aux, size - 1);
  }

  s21_remove_matrix(&aux);
  return result;
}

int s21_determinant(matrix_t *A, double *result) {
  if (s21_is_bad_matrix(A) == SUCCESS) return incorrect_matix;
  if (A->columns != A->rows) return calculation_error;

  if (A->rows == 1)
    *result = A->matrix[0][0];
  else
    *result = calcDeterminant(A, A->rows);

  return OK;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (s21_is_bad_matrix(A) == SUCCESS) return incorrect_matix;
  if (A->columns != A->rows) return calculation_error;

  s21_create_matrix(A->columns, A->rows, result);
  if (A->rows != 1) {
    matrix_t aux = {0};

    s21_create_matrix(A->rows, A->rows, &aux);
    for (int sign = 0, x = 0; x < A->rows; x += 1) {
      for (int y = 0; y < A->columns; y += 1) {
        calcMinor(A->matrix, aux.matrix, x, y, A->rows);
        sign = ((x + y) % 2 == 0) ? 1 : (-1);
        result->matrix[x][y] = sign * calcDeterminant(&aux, A->rows - 1);
      }
    }

    s21_remove_matrix(&aux);
  } else {
    result->matrix[0][0] = 1;
  }

  return OK;
}

int s21_is_bad_eq_matrix(matrix_t *A, matrix_t *B) {
  int status = 1;

  if (s21_is_bad_matrix(A) == 0) {
    if (s21_is_bad_matrix(B) == 0)
      status = (A->rows == B->rows && A->columns == B->columns) ? 0 : 2;
  }

  return status;
}

int s21_is_bad_matrix(matrix_t *A) {
  return (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0);
}