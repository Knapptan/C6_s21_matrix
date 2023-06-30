#include "s21_matrix.h"

void s21_full_matrix(double number, matrix_t *result) {
  for (int i = 0; i < result->rows; i++) {
    for (int j = 0; j < result->columns; j++) {
      result->matrix[i][j] = number;
      number++;
    }
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int return_result = FAILURE;
  if (A->columns == B->columns && A->rows == B->rows) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) < 1e-07)
          return_result = SUCCESS;
        else
          return_result = FAILURE;
      }
    }
  }
  return return_result;
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int return_flag = CALC_ERROR;
  if (rows > 0 && columns > 0) {
    if ((result->matrix = (double **)malloc(rows * sizeof(double *)))) {
      result->rows = rows;
      result->columns = columns;
      for (int i = 0; i < rows; i++) {
        if (!(result->matrix[i] = (double *)malloc(columns * sizeof(double)))) {
          for (int k = 0; k < i; k++) free(result->matrix[k]);
          free(result->matrix);
          return_flag = MATRIX_UNCOR;
        }
      }
    }
    if (return_flag == CALC_ERROR) {
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
          result->matrix[i][j] = 0;
        }
      }
      return_flag = OK;
    }
  } else {
    return_flag = MATRIX_UNCOR;
  }
  return return_flag;
}

void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    free(A->matrix[i]);
  }
  free(A->matrix);
  A->rows = 0;
  A->columns = 0;
}

// void s21_print_matrix(matrix_t result) {
//   for (int i = 0; i < result.rows; i++) {
//     for (int j = 0; j < result.columns; j++) {
//       printf(" %3lf", result.matrix[i][j]);
//     }
//     printf("\n");
//   }
// }
