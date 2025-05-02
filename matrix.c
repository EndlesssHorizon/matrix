#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// ==================== Базовые операции ====================

matrix* matrix_alloc(size_t w, size_t h) {
    matrix* m = (matrix*)malloc(sizeof(matrix));
    if (!m) return NULL;
    
    m->w = w;
    m->h = h;
    m->data = (double*)malloc(w * h * sizeof(double));
    if (!m->data) {
        free(m);
        return NULL;
    }
    
    return m;
}

void matrix_free(matrix* m) {
    if (m) {
        free(m->data);
        free(m);
    }
}

matrix* matrix_copy(const matrix* m) {
    if (!m) return NULL;
    
    matrix* copy = matrix_alloc(m->w, m->h);
    if (!copy) return NULL;
    
    memcpy(copy->data, m->data, m->w * m->h * sizeof(double));
    return copy;
}

double* matrix_ptr(matrix* m, size_t i, size_t j) {
    return &m->data[i * m->w + j];
}

const double* matrix_cptr(const matrix* m, size_t i, size_t j) {
    return &m->data[i * m->w + j];
}

// ==================== Инициализация ====================

void matrix_set_zero(matrix* m) {
    if (!m) return;
    memset(m->data, 0, m->w * m->h * sizeof(double));
}

void matrix_set_id(matrix* m) {
    if (!m) return;
    matrix_set_zero(m);
    size_t min_dim = m->w < m->h ? m->w : m->h;
    for (size_t i = 0; i < min_dim; i++) {
        *matrix_ptr(m, i, i) = 1.0;
    }
}

matrix* matrix_alloc_zero(size_t w, size_t h) {
    matrix* m = matrix_alloc(w, h);
    if (m) matrix_set_zero(m);
    return m;
}

matrix* matrix_alloc_id(size_t w, size_t h) {
    matrix* m = matrix_alloc(w, h);
    if (m) matrix_set_id(m);
    return m;
}

int matrix_assign(matrix* m1, const matrix* m2) {
    if (!m1 || !m2 || m1->w != m2->w || m1->h != m2->h)
        return -1;
    
    memcpy(m1->data, m2->data, m1->w * m1->h * sizeof(double));
    return 0;
}

// ==================== Ввод/вывод ====================

void matrix_print(const matrix* m) {
    if (!m) return;
    
    for (size_t i = 0; i < m->h; i++) {
        for (size_t j = 0; j < m->w; j++) {
            printf("%8.4f ", *matrix_cptr(m, i, j));
        }
        printf("\n");
    }
}

matrix* matrix_input(size_t w, size_t h) {
    matrix* m = matrix_alloc(w, h);
    if (!m) return NULL;
    
    printf("Enter matrix %zux%zu:\n", h, w);
    for (size_t i = 0; i < h; i++) {
        for (size_t j = 0; j < w; j++) {
            scanf("%lf", matrix_ptr(m, i, j));
        }
    }
    
    return m;
}

// ==================== Арифметические операции ====================

int matrix_add(matrix* m1, const matrix* m2) {
    if (!m1 || !m2 || m1->w != m2->w || m1->h != m2->h)
        return -1;
    
    for (size_t i = 0; i < m1->h; i++) {
        for (size_t j = 0; j < m1->w; j++) {
            *matrix_ptr(m1, i, j) += *matrix_cptr(m2, i, j);
        }
    }
    return 0;
}

int matrix_sub(matrix* m1, const matrix* m2) {
    if (!m1 || !m2 || m1->w != m2->w || m1->h != m2->h)
        return -1;
    
    for (size_t i = 0; i < m1->h; i++) {
        for (size_t j = 0; j < m1->w; j++) {
            *matrix_ptr(m1, i, j) -= *matrix_cptr(m2, i, j);
        }
    }
    return 0;
}

void matrix_smul(matrix* m, double d) {
    if (!m) return;
    
    for (size_t i = 0; i < m->h; i++) {
        for (size_t j = 0; j < m->w; j++) {
            *matrix_ptr(m, i, j) *= d;
        }
    }
}

void matrix_sdiv(matrix* m, double d) {
    if (!m || d == 0.0) return;
    matrix_smul(m, 1.0 / d);
}

int matrix_add2(matrix* m, const matrix* m1, const matrix* m2) {
    if (!m || !m1 || !m2 || m1->w != m2->w || m1->h != m2->h || 
        m->w != m1->w || m->h != m1->h)
        return -1;
    
    matrix_assign(m, m1);
    return matrix_add(m, m2);
}

int matrix_sub2(matrix* m, const matrix* m1, const matrix* m2) {
    if (!m || !m1 || !m2 || m1->w != m2->w || m1->h != m2->h || 
        m->w != m1->w || m->h != m1->h)
        return -1;
    
    matrix_assign(m, m1);
    return matrix_sub(m, m2);
}

int matrix_smul2(matrix* m, const matrix* m1, double d) {
    if (!m || !m1 || m->w != m1->w || m->h != m1->h)
        return -1;
    
    matrix_assign(m, m1);
    matrix_smul(m, d);
    return 0;
}

int matrix_sdiv2(matrix* m, const matrix* m1, double d) {
    if (!m || !m1 || m->w != m1->w || m->h != m1->h || d == 0.0)
        return -1;
    
    matrix_assign(m, m1);
    matrix_sdiv(m, d);
    return 0;
}

int matrix_mul(matrix* m1, const matrix* m2) {
    if (!m1 || !m2 || m1->w != m2->h)
        return -1;
    
    matrix* temp = matrix_alloc(m2->w, m1->h);
    if (!temp) return -1;
    
    for (size_t i = 0; i < m1->h; i++) {
        for (size_t j = 0; j < m2->w; j++) {
            double sum = 0.0;
            for (size_t k = 0; k < m1->w; k++) {
                sum += *matrix_cptr(m1, i, k) * *matrix_cptr(m2, k, j);
            }
            *matrix_ptr(temp, i, j) = sum;
        }
    }
    
    free(m1->data);
    m1->w = m2->w;
    m1->data = temp->data;
    
    free(temp);
    return 0;
}

int matrix_mul2(matrix* m, const matrix* m1, const matrix* m2) {
    if (!m || !m1 || !m2 || m1->w != m2->h || 
        (m != m1 && m != m2 && (m->w != m2->w || m->h != m1->h)))
        return -1;
    
    if (m == m1 || m == m2) {
        matrix* temp = matrix_alloc(m2->w, m1->h);
        if (!temp) return -1;
        
        int result = matrix_mul2(temp, m1, m2);
        if (result == 0) {
            matrix_assign(m, temp);
        }
        matrix_free(temp);
        return result;
    } else {
        for (size_t i = 0; i < m1->h; i++) {
            for (size_t j = 0; j < m2->w; j++) {
                double sum = 0.0;
                for (size_t k = 0; k < m1->w; k++) {
                    sum += *matrix_cptr(m1, i, k) * *matrix_cptr(m2, k, j);
                }
                *matrix_ptr(m, i, j) = sum;
            }
        }
        return 0;
    }
}

// ==================== Манипуляции с матрицами ====================

void matrix_transpose(matrix* m) {
    if (!m) return;
    
    matrix* temp = matrix_alloc(m->h, m->w);
    if (!temp) return;
    
    for (size_t i = 0; i < m->h; i++) {
        for (size_t j = 0; j < m->w; j++) {
            *matrix_ptr(temp, j, i) = *matrix_cptr(m, i, j);
        }
    }
    
    size_t tmp = m->w;
    m->w = m->h;
    m->h = tmp;
    
    free(m->data);
    m->data = temp->data;
    free(temp);
}

void matrix_swap_rows(matrix* m, size_t i1, size_t i2) {
    if (!m || i1 >= m->h || i2 >= m->h) return;
    
    for (size_t j = 0; j < m->w; j++) {
        double tmp = *matrix_ptr(m, i1, j);
        *matrix_ptr(m, i1, j) = *matrix_ptr(m, i2, j);
        *matrix_ptr(m, i2, j) = tmp;
    }
}

void matrix_swap_cols(matrix* m, size_t j1, size_t j2) {
    if (!m || j1 >= m->w || j2 >= m->w) return;
    
    for (size_t i = 0; i < m->h; i++) {
        double tmp = *matrix_ptr(m, i, j1);
        *matrix_ptr(m, i, j1) = *matrix_ptr(m, i, j2);
        *matrix_ptr(m, i, j2) = tmp;
    }
}

void matrix_row_mul(matrix* m, size_t i, double d) {
    if (!m || i >= m->h) return;
    
    for (size_t j = 0; j < m->w; j++) {
        *matrix_ptr(m, i, j) *= d;
    }
}

void matrix_row_div(matrix* m, size_t i, double d) {
    if (!m || i >= m->h || d == 0.0) return;
    matrix_row_mul(m, i, 1.0 / d);
}

void matrix_rows_add(matrix* m, size_t i1, size_t i2, double k) {
    if (!m || i1 >= m->h || i2 >= m->h) return;
    
    for (size_t j = 0; j < m->w; j++) {
        *matrix_ptr(m, i1, j) += k * *matrix_ptr(m, i2, j);
    }
}

double matrix_norm(const matrix* m) {
    if (!m) return 0.0;
    
    double max = 0.0;
    for (size_t i = 0; i < m->h; i++) {
        double row_sum = 0.0;
        for (size_t j = 0; j < m->w; j++) {
            row_sum += fabs(*matrix_cptr(m, i, j));
        }
        if (row_sum > max) max = row_sum;
    }
    return max;
}

// ==================== Специальные задачи ====================

matrix* matrix_exp(const matrix* A, double eps) {
    if (!A || A->w != A->h) return NULL;
    
    size_t n = A->w;
    matrix* result = matrix_alloc_id(n, n);
    matrix* term = matrix_copy(A);
    matrix* temp = NULL;
    
    if (!result || !term) {
        matrix_free(result);
        matrix_free(term);
        return NULL;
    }
    
    double factorial = 1.0;
    int k = 1;
    
    while (matrix_norm(term) >= eps) {
        matrix_add(result, term);
        
        temp = matrix_alloc(n, n);
        if (!temp) {
            matrix_free(result);
            matrix_free(term);
            return NULL;
        }
        
        matrix_mul2(temp, A, term);
        matrix_free(term);
        term = temp;
        
        k++;
        factorial *= k;
        matrix_sdiv(term, factorial);
    }
    
    matrix_free(term);
    return result;
}

matrix* matrix_solve_gauss(const matrix* A, const matrix* B) {
    if (!A || !B || A->w != A->h || A->h != B->h || B->w != 1)
        return NULL;
    
    size_t n = A->w;
    matrix* AB = matrix_alloc(n, n + 1);
    if (!AB) return NULL;
    
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            *matrix_ptr(AB, i, j) = *matrix_cptr(A, i, j);
        }
        *matrix_ptr(AB, i, n) = *matrix_cptr(B, i, 0);
    }
    
    for (size_t k = 0; k < n; k++) {
        size_t max_row = k;
        double max_val = fabs(*matrix_cptr(AB, k, k));
        
        for (size_t i = k + 1; i < n; i++) {
            double val = fabs(*matrix_cptr(AB, i, k));
            if (val > max_val) {
                max_val = val;
                max_row = i;
            }
        }
        
        if (max_row != k) {
            matrix_swap_rows(AB, k, max_row);
        }
        
        if (fabs(*matrix_cptr(AB, k, k)) < 1e-10) {
            matrix_free(AB);
            return NULL;
        }
        
        double pivot = *matrix_cptr(AB, k, k);
        for (size_t j = k; j < n + 1; j++) {
            *matrix_ptr(AB, k, j) /= pivot;
        }
        
        for (size_t i = 0; i < n; i++) {
            if (i != k) {
                double factor = *matrix_cptr(AB, i, k);
                for (size_t j = k; j < n + 1; j++) {
                    *matrix_ptr(AB, i, j) -= factor * *matrix_cptr(AB, k, j);
                }
            }
        }
    }
    
    matrix* X = matrix_alloc(1, n);
    if (!X) {
        matrix_free(AB);
        return NULL;
    }
    
    for (size_t i = 0; i < n; i++) {
        *matrix_ptr(X, i, 0) = *matrix_cptr(AB, i, n);
    }
    
    matrix_free(AB);
    return X;
}