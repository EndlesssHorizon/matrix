#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct matrix {
    double* data;
    size_t w;
    size_t h;
};

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

matrix* matrix_copy(const matrix* m) {
    if (!m) return NULL;
    
    matrix* copy = matrix_alloc(m->w, m->h);
    if (!copy) return NULL;
    
    memcpy(copy->data, m->data, m->w * m->h * sizeof(double));
    return copy;
}

void matrix_free(matrix* m) {
    if (m) {
        free(m->data);
        free(m);
    }
}

double* matrix_ptr(matrix* m, size_t i, size_t j) {
    return &m->data[i * m->w + j];
}

const double* matrix_cptr(const matrix* m, size_t i, size_t j) {
    return &m->data[i * m->w + j];
}

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