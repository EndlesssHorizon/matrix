#pragma once


#include "matrix.h"

// Матричная экспонента
matrix* matrix_exp(const matrix* A, double eps);

// Решение СЛАУ методом Гаусса
matrix* matrix_solve_gauss(const matrix* A, const matrix* B);
