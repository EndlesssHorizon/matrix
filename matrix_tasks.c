#include "matrix_tasks.h"
#include "matrix_ops.h"
#include "matrix_manip.h"
#include <math.h>

struct matrix {
    double* data;
    size_t w;
    size_t h;
};

matrix* matrix_exp(const matrix* A, double eps) {
    if (!A || A->w != A->h) return NULL;
    
    size_t n = A->w;
    matrix* result = matrix_alloc_id(n, n); 
    matrix* term = matrix_copy(A);         
    
    if (!result || !term) {
        matrix_free(result);
        matrix_free(term);
        return NULL;
    }
    
    int k = 1;
    
    while (matrix_norm(term) >= eps) {
        matrix_add(result, term);
        
        matrix* new_term = matrix_alloc(n, n);
        if (!new_term) {
            matrix_free(result);
            matrix_free(term);
            return NULL;
        }
        
        matrix_mul2(new_term, term, A);
        matrix_free(term);
        term = new_term;
        
        k++;
        matrix_sdiv(term, k);
    }
    
    matrix_free(term);
    return result;
}

matrix* matrix_solve_gauss(const matrix* A, const matrix* B) {
    if (!A || !B || A->w != A->h || A->h != B->h || B->w != 1)
        return NULL;

    const size_t n = A->h;
    
    matrix* A_copy = matrix_copy(A);
    matrix* B_copy = matrix_copy(B);
    if (!A_copy || !B_copy) {
        matrix_free(A_copy);
        matrix_free(B_copy);
        return NULL;
    }

    for (size_t k = 0; k < n; k++) {
        size_t max_row = k;
        double max_val = fabs(*matrix_cptr(A_copy, k, k));
        
        for (size_t i = k + 1; i < n; i++) {
            double val = fabs(*matrix_cptr(A_copy, i, k));
            if (val > max_val) {
                max_val = val;
                max_row = i;
            }
        }
        if (max_val < 1e-12) {
            matrix_free(A_copy);
            matrix_free(B_copy);
            return NULL;
        }

        if (max_row != k) {
            matrix_swap_rows(A_copy, k, max_row);
            matrix_swap_rows(B_copy, k, max_row);
        }

        double pivot = *matrix_cptr(A_copy, k, k);
        for (size_t j = k; j < n; j++) {
            *matrix_ptr(A_copy, k, j) /= pivot;
        }
        *matrix_ptr(B_copy, k, 0) /= pivot;

        for (size_t i = 0; i < n; i++) {
            if (i != k) {
                double factor = *matrix_cptr(A_copy, i, k);
                for (size_t j = k; j < n; j++) {
                    *matrix_ptr(A_copy, i, j) -= factor * *matrix_cptr(A_copy, k, j);
                }
                *matrix_ptr(B_copy, i, 0) -= factor * *matrix_cptr(B_copy, k, 0);
            }
        }
    }

    matrix* X = matrix_copy(B_copy);
    matrix_free(A_copy);
    matrix_free(B_copy);

    return X;
}