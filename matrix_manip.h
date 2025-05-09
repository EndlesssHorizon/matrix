#pragma once

#include "matrix.h"

// Манипуляции с матрицами
void matrix_transpose(matrix* m);
void matrix_swap_rows(matrix* m, size_t i1, size_t i2);
void matrix_swap_cols(matrix* m, size_t j1, size_t j2);
void matrix_row_mul(matrix* m, size_t i, double d);
void matrix_row_div(matrix* m, size_t i, double d);
void matrix_rows_add(matrix* m, size_t i1, size_t i2, double k);
double matrix_norm(const matrix* m);
