#pragma once


#include "matrix.h"

// ��������� ����������
matrix* matrix_exp(const matrix* A, double eps);

// ������� ���� ������� ������
matrix* matrix_solve_gauss(const matrix* A, const matrix* B);
