#include "s21_matrix.h"

int s21_mat_for_minor(matrix_t *A, int row, int col, matrix_t *result) {
  int return_result = OK;
  int num_rows = A->rows;
  int num_columns = A->columns;
  int res_rows = num_rows - 1;
  int res_columns = num_columns - 1;
  if ((row >= A->rows || col >= A->columns) || num_rows < 2 ||
      num_columns < 2) {
    return_result = CALC_ERROR;
  } else {
    if (s21_create_matrix(res_rows, res_columns, result) == OK) {
      for (int k = 0, i = 0; i < num_columns && k < res_columns; i++) {
        if (i == row) continue;
        for (int m = 0, j = 0; j < num_rows && m < res_rows; j++) {
          if (j == col) continue;
          result->matrix[k][m] = A->matrix[i][j];
          m++;
        }
        k++;
      }
    }
  }
  return return_result;
}

void s21_copy_mat_value(matrix_t A, matrix_t *mat) {
  int i, j;
  for (i = 0; i < A.rows; i++) {
    for (j = 0; j < A.columns; j++) {
      mat->matrix[i][j] = A.matrix[i][j];
    }
  }
}

void s21_swapping(matrix_t *A, int k) {
  int j;
  double temp;
  for (j = 0; j < A->columns; j++) {
    temp = A->matrix[k][j];
    A->matrix[k][j] = A->matrix[k + 1][j];
    A->matrix[k + 1][j] = temp;
  }
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int num_rows = A->rows;
  int num_columns = A->columns;
  int return_result = CALC_ERROR;
  if (A == NULL || A->matrix == NULL) {
    return_result = MATRIX_UNCOR;
  } else if (num_rows == num_columns) {
    s21_create_matrix(A->rows, A->columns, result);
    return_result = OK;
    if (num_rows == 1) {
      result->matrix[0][0] = 1.0;
    } else {
      int break_point = 0;
      int break_point1 = 0;
      for (int i = 0; i < num_rows && !break_point1; i++) {
        for (int j = 0; j < num_columns && !break_point; j++) {
          double minor_determinant = 0;
          matrix_t minor = {0};
          if (s21_mat_for_minor(A, i, j, &minor) != OK) {
            return_result = MATRIX_UNCOR;
            s21_remove_matrix(&minor);
            break_point = 1;
          }
          if (s21_determinant(&minor, &minor_determinant) != OK) {
            return_result = MATRIX_UNCOR;
            s21_remove_matrix(&minor);
            break_point = 1;
          }
          s21_remove_matrix(&minor);
          double complement = pow(-1, i + j) * minor_determinant;
          result->matrix[i][j] = complement;
        }
        if (return_result != OK) {
          break_point1 = 1;
        }
      }
    }
  }
  return return_result;
}

int s21_determinant(matrix_t *A, double *result) {
  int i = 0, return_result = OK;
  *result = 1;
  if (A->matrix == NULL || 0 < A->rows || 0 < A->columns) {
    if (A->rows != A->columns) {
      return_result = CALC_ERROR;
    } else {
      matrix_t mat = {0};
      double elem;
      return_result = s21_create_matrix(A->rows, A->columns, &mat);
      for (i = 1; i < A->rows; i++) {
        for (int k = 0; k < i; k++) {
          if (A->matrix[k][k] == 0) {
            s21_swapping(A, k);
            *result *= -1;
          }
          if (A->matrix[i][k] != 0) {
            s21_copy_mat_value(*A, &mat);
            elem = (-(A->matrix[i][k]) / A->matrix[k][k]);
            for (int j = 0; j < A->columns; j++) {
              mat.matrix[k][j] *= elem;
            }
            for (int j = 0; j < A->columns; j++) {
              A->matrix[i][j] += mat.matrix[k][j];
            }
          }
        }
      }
      for (i = 0; i < A->rows; i++) {
        *result *= A->matrix[i][i];
      }
      if (*result == 0) {
        *result = fabs(*result);
      }
      s21_remove_matrix(&mat);
    }
  } else {
    return_result = MATRIX_UNCOR;
  }
  return return_result;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int num_rows = A->rows;
  int num_columns = A->columns;
  int return_result = MATRIX_UNCOR;
  if (num_rows != num_columns) {
    return_result = CALC_ERROR;
  } else if (A != NULL && A->matrix != NULL && A->rows >= 0 &&
             A->columns >= 0) {
    double determinant = 0;
    if (s21_determinant(A, &determinant) != OK || fabs(determinant) < 1e-6) {
      return_result = CALC_ERROR;
    } else {
      matrix_t complements = {0}, transposed_complements = {0};
      return_result = OK;
      s21_calc_complements(A, &complements);
      s21_transpose(&complements, &transposed_complements);
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] =
              transposed_complements.matrix[i][j] / determinant;
        }
      }
      s21_remove_matrix(&complements);
      s21_remove_matrix(&transposed_complements);
    }
  }
  return return_result;
}
