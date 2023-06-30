#include "s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int return_result = SUCCESS;
  if (A->matrix != NULL && B->matrix != NULL && 0 < A->rows && 0 < B->rows &&
      0 < A->columns && 0 < B->columns) {
    if ((A->rows != B->rows) || (A->columns != B->columns)) {
      return_result = CALC_ERROR;
    } else {
      return_result = s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    }
  } else {
    return_result = MATRIX_UNCOR;
  }
  return return_result;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int return_result = SUCCESS;
  if (A->matrix != NULL && B->matrix != NULL && 0 < A->rows && 0 < B->rows &&
      0 < A->columns && 0 < B->columns) {
    if ((A->rows != B->rows) || (A->columns != B->columns)) {
      return_result = CALC_ERROR;
    } else {
      return_result = s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    }
  } else {
    return_result = MATRIX_UNCOR;
  }
  return return_result;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int return_result = CALC_ERROR;
  if (A->matrix == NULL || 0 > A->rows || 0 > A->columns) {
    return_result = MATRIX_UNCOR;
  } else {
    return_result = s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return return_result;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int return_result = OK;
  int summ = 0;
  if (A->matrix != NULL && B->matrix != NULL && 0 < A->rows && 0 < B->rows &&
      0 < A->columns && 0 < B->columns) {
    if (A->columns != B->rows) {
      return_result = CALC_ERROR;
    } else {
      return_result = s21_create_matrix(A->rows, B->columns, result);
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          for (int k = 0; k < A->columns; k++) {
            summ += A->matrix[i][k] * B->matrix[k][j];
          }
          result->matrix[i][j] = summ;
          summ = 0;
        }
      }
    }
  } else {
    return_result = MATRIX_UNCOR;
  }
  return return_result;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int return_result = OK;
  if (A->matrix == NULL || 0 > A->rows || 0 > A->columns) {
    return_result = MATRIX_UNCOR;
  } else {
    return_result = s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return return_result;
}
