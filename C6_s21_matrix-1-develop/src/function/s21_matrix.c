#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int status = incorrect_matix;

  if (rows > 0 && columns > 0) {
    if ((result->matrix = (double **)calloc(rows, sizeof(double *)))) {
      result->columns = columns;
      result->rows = rows;

      for (int x = 0; x < rows; x += 1) {
        if (!(result->matrix[x] = (double *)calloc(columns, sizeof(double)))) {
          for (int q = 0; q < x; q += 1) free(result->matrix[q]);
          free(result->matrix);
          status = alloc_fail;
        }
      }

      if (status == incorrect_matix) {
        for (int x = 0; x < rows; x += 1) {
          for (int y = 0; y < columns; y += 1) {
            result->matrix[x][y] = 0;
          }
        }
        status = OK;
      }
    } else {
      status = alloc_fail;
    }
  }

  return status;
}

void s21_remove_matrix(matrix_t *A) {
  if (A) {
    for (int x = 0; x < A->rows; x += 1) {
      free(A->matrix[x]);
    }
    free(A->matrix);
    A->matrix = NULL;
    A->columns = 0;
    A->rows = 0;
  }
}