#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Структура матрицы (динамическая с вычислением адреса)
typedef struct {
    double* data;    
    size_t w;        
    size_t h;        
} matrix;

// Базовые операции
matrix* matrix_alloc(size_t w, size_t h);
void matrix_free(matrix* m);
matrix* matrix_copy(const matrix* m);
double* matrix_ptr(matrix* m, size_t i, size_t j);
const double* matrix_cptr(const matrix* m, size_t i, size_t j);

// Инициализация
void matrix_set_zero(matrix* m);
void matrix_set_id(matrix* m);
matrix* matrix_alloc_zero(size_t w, size_t h);
matrix* matrix_alloc_id(size_t w, size_t h);
int matrix_assign(matrix* m1, const matrix* m2);

// Ввод/вывод
void matrix_print(const matrix* m);
matrix* matrix_input(size_t w, size_t h);

// Арифметические операции
int matrix_add(matrix* m1, const matrix* m2);
int matrix_sub(matrix* m1, const matrix* m2);
void matrix_smul(matrix* m, double d);
void matrix_sdiv(matrix* m, double d);
int matrix_add2(matrix* m, const matrix* m1, const matrix* m2);
int matrix_sub2(matrix* m, const matrix* m1, const matrix* m2);
int matrix_smul2(matrix* m, const matrix* m1, double d);
int matrix_sdiv2(matrix* m, const matrix* m1, double d);
int matrix_mul(matrix* m1, const matrix* m2);
int matrix_mul2(matrix* m, const matrix* m1, const matrix* m2);

// Манипуляции с матрицами
void matrix_transpose(matrix* m);
void matrix_swap_rows(matrix* m, size_t i1, size_t i2);
void matrix_swap_cols(matrix* m, size_t j1, size_t j2);
void matrix_row_mul(matrix* m, size_t i, double d);
void matrix_row_div(matrix* m, size_t i, double d);
void matrix_rows_add(matrix* m, size_t i1, size_t i2, double k);
double matrix_norm(const matrix* m);

// Специальные задачи
matrix* matrix_exp(const matrix* A, double eps);
matrix* matrix_solve_gauss(const matrix* A, const matrix* B);
