#pragma once

#include <stddef.h>

// �������� ��� ��� ������������
struct matrix;
typedef struct matrix matrix;

// �������� � ������������ ������
matrix* matrix_alloc(size_t w, size_t h);
matrix* matrix_copy(const matrix* m);
void matrix_free(matrix* m);

// ������ � ���������
double* matrix_ptr(matrix* m, size_t i, size_t j);
const double* matrix_cptr(const matrix* m, size_t i, size_t j);

// �������������
void matrix_set_zero(matrix* m);
void matrix_set_id(matrix* m);
matrix* matrix_alloc_zero(size_t w, size_t h);
matrix* matrix_alloc_id(size_t w, size_t h);
int matrix_assign(matrix* m1, const matrix* m2);

// ����/�����
void matrix_print(const matrix* m);
matrix* matrix_input(size_t w, size_t h);
