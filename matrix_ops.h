#pragma once

#include "matrix.h"

// Базовые операции
int matrix_add(matrix* m1, const matrix* m2);
int matrix_sub(matrix* m1, const matrix* m2);
void matrix_smul(matrix* m, double d);
void matrix_sdiv(matrix* m, double d);

// Операции с созданием новой матрицы
int matrix_add2(matrix* m, const matrix* m1, const matrix* m2);
int matrix_sub2(matrix* m, const matrix* m1, const matrix* m2);
int matrix_smul2(matrix* m, const matrix* m1, double d);
int matrix_sdiv2(matrix* m, const matrix* m1, double d);

// Умножение матриц
int matrix_mul(matrix* m1, const matrix* m2);
int matrix_mul2(matrix* m, const matrix* m1, const matrix* m2);
