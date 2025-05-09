#include <stdio.h>
#include "matrix.h"
#include "matrix_ops.h"
#include "matrix_manip.h"
#include "matrix_tasks.h"

int main() {
    // Пример матричной экспоненты
    matrix* A = matrix_alloc_zero(3, 3);
    *matrix_ptr(A, 0, 0) = 1.0;
    *matrix_ptr(A, 1, 1) = 2.0;
    *matrix_ptr(A, 2, 2) = -1.0;
    
    printf("Matrix A:\n");
    matrix_print(A);
    
    matrix* expA = matrix_exp(A, 1e-10);
    printf("\nMatrix exp(A):\n");
    matrix_print(expA);
    
    matrix_free(A);
    matrix_free(expA);
    
    // Пример решения СЛАУ
    matrix* B = matrix_alloc(3, 3);
    *matrix_ptr(B, 0, 0) = 2.0; *matrix_ptr(B, 0, 1) = 1.0; *matrix_ptr(B, 0, 2) = -1.0;
    *matrix_ptr(B, 1, 0) = -3.0; *matrix_ptr(B, 1, 1) = -1.0; *matrix_ptr(B, 1, 2) = 2.0;
    *matrix_ptr(B, 2, 0) = -2.0; *matrix_ptr(B, 2, 1) = 1.0; *matrix_ptr(B, 2, 2) = 2.0;
    
    matrix* C = matrix_alloc(1, 3);
    *matrix_ptr(C, 0, 0) = 8.0;
    *matrix_ptr(C, 1, 0) = -11.0;
    *matrix_ptr(C, 2, 0) = -3.0;
    
    printf("\nSystem of equations:\n");
    printf("Coefficient matrix:\n");
    matrix_print(B);
    printf("Right-hand side:\n");
    matrix_print(C);
    
    matrix* X = matrix_solve_gauss(B, C);
    printf("\nSolution:\n");
    matrix_print(X);
    
    matrix_free(B);
    matrix_free(C);
    matrix_free(X);
    
    return 0;
}