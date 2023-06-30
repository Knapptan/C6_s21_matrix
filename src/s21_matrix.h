#ifndef S21_MATRIX_H
#define S21_MATRIX_H
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define MATRIX_UNCOR 1
#define CALC_ERROR 2

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

#define SUCCESS 1
#define FAILURE 0

// создание
int s21_create_matrix(int rows, int columns, matrix_t *result);
// очистка и уничтожение
void s21_remove_matrix(matrix_t *A);
// сравнение
int s21_eq_matrix(matrix_t *A, matrix_t *B);
// сложение
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// вычитание
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// умножение на число
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
// умножение
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// транспонирование
int s21_transpose(matrix_t *A, matrix_t *result);
// вычисление матрицы алгебраических дополнений
int s21_calc_complements(matrix_t *A, matrix_t *result);
// вычисление определителя
int s21_determinant(matrix_t *A, double *result);
// поиск обратной матрицы
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
// заполнение матрицы - для примера
void s21_full_matrix(double number, matrix_t *result);
// минор
int s21_mat_for_minor(matrix_t *A, int row, int col, matrix_t *result);

#endif  // S21_MATRIX_H
