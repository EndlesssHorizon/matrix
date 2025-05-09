#include "matrix_manip.h"
#include <stdlib.h>
#include <math.h>

struct matrix {
    double* data;
    size_t w;
    size_t h;
};

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