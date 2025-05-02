#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

void print_menu() {
    printf("\n=== Matrix Operations Menu ===\n");
    printf("1. Create new matrix\n");
    printf("2. Input matrix values\n");
    printf("3. Print matrix\n");
    printf("4. Set matrix to zero\n");
    printf("5. Set matrix to identity\n");
    printf("6. Matrix addition\n");
    printf("7. Matrix subtraction\n");
    printf("8. Matrix multiplication\n");
    printf("9. Scalar multiplication\n");
    printf("10. Matrix transpose\n");
    printf("11. Matrix exponent\n");
    printf("12. Solve linear system (Gauss)\n");
    printf("13. Matrix norm\n");
    printf("0. Exit\n");
    printf("=============================\n");
    printf("Select operation: ");
}

void clear_input_buffer() {
    while (getchar() != '\n');
}

matrix* create_matrix_ui() {
    size_t w, h;
    printf("Enter matrix width: ");
    scanf("%zu", &w);
    printf("Enter matrix height: ");
    scanf("%zu", &h);
    clear_input_buffer();
    
    matrix* m = matrix_alloc(w, h);
    if (!m) {
        printf("Error: Failed to allocate matrix\n");
        return NULL;
    }
    return m;
}

void input_matrix_ui(matrix* m) {
    if (!m) {
        printf("Error: Matrix not initialized\n");
        return;
    }
    
    printf("Enter matrix elements row by row:\n");
    for (size_t i = 0; i < m->h; i++) {
        printf("Row %zu: ", i + 1);
        for (size_t j = 0; j < m->w; j++) {
            scanf("%lf", matrix_ptr(m, i, j));
        }
    }
    clear_input_buffer();
}

void print_matrix_ui(matrix* m) {
    if (!m) {
        printf("Error: Matrix not initialized\n");
        return;
    }
    printf("Matrix:\n");
    matrix_print(m);
}

void matrix_operations_ui() {
    matrix* m1 = NULL;
    matrix* m2 = NULL;
    matrix* result = NULL;
    int choice;
    double scalar;
    
    do {
        print_menu();
        scanf("%d", &choice);
        clear_input_buffer();
        
        switch (choice) {
            case 1:
                if (m1) matrix_free(m1);
                m1 = create_matrix_ui();
                break;
                
            case 2:
                input_matrix_ui(m1);
                break;
                
            case 3:
                print_matrix_ui(m1);
                break;
                
            case 4:
                matrix_set_zero(m1);
                printf("Matrix set to zero\n");
                break;
                
            case 5:
                if (m1 && m1->w == m1->h) {
                    matrix_set_id(m1);
                    printf("Matrix set to identity\n");
                } else {
                    printf("Error: Matrix must be square\n");
                }
                break;
                
            case 6:
                printf("Creating second matrix for addition\n");
                if (m2) matrix_free(m2);
                m2 = create_matrix_ui();
                input_matrix_ui(m2);
                
                if (matrix_add(m1, m2)) {
                    printf("Error: Matrices must have same dimensions\n");
                } else {
                    printf("Addition completed\n");
                }
                break;
                
            case 7:
                printf("Creating second matrix for subtraction\n");
                if (m2) matrix_free(m2);
                m2 = create_matrix_ui();
                input_matrix_ui(m2);
                
                if (matrix_sub(m1, m2)) {
                    printf("Error: Matrices must have same dimensions\n");
                } else {
                    printf("Subtraction completed\n");
                }
                break;
                
            case 8:
                printf("Creating second matrix for multiplication\n");
                if (m2) matrix_free(m2);
                m2 = create_matrix_ui();
                input_matrix_ui(m2);
                
                if (matrix_mul(m1, m2)) {
                    printf("Error: Matrix dimensions don't match for multiplication\n");
                } else {
                    printf("Multiplication completed\n");
                }
                break;
                
            case 9:
                printf("Enter scalar value: ");
                scanf("%lf", &scalar);
                clear_input_buffer();
                
                matrix_smul(m1, scalar);
                printf("Scalar multiplication completed\n");
                break;
                
            case 10:
                matrix_transpose(m1);
                printf("Matrix transposed\n");
                break;
                
            case 11:
                if (m1 && m1->w == m1->h) {
                    if (result) matrix_free(result);
                    result = matrix_exp(m1, 1e-10);
                    printf("Matrix exponent calculated:\n");
                    matrix_print(result);
                } else {
                    printf("Error: Matrix must be square\n");
                }
                break;
                
            case 12:
                if (m1 && m1->w == m1->h) {
                    printf("Creating right-hand side vector\n");
                    if (m2) matrix_free(m2);
                    m2 = matrix_alloc(1, m1->h);
                    input_matrix_ui(m2);
                    
                    if (result) matrix_free(result);
                    result = matrix_solve_gauss(m1, m2);
                    if (result) {
                        printf("Solution:\n");
                        matrix_print(result);
                    } else {
                        printf("Error: System has no unique solution\n");
                    }
                } else {
                    printf("Error: Coefficient matrix must be square\n");
                }
                break;
                
            case 13:
                printf("Matrix norm: %lf\n", matrix_norm(m1));
                break;
                
            case 0:
                printf("Exiting...\n");
                break;
                
            default:
                printf("Invalid choice. Try again.\n");
        }
        
    } while (choice != 0);
    
    if (m1) matrix_free(m1);
    if (m2) matrix_free(m2);
    if (result) matrix_free(result);
}

int main() {
    printf("=== Matrix Operations Program ===\n");
    matrix_operations_ui();
    return 0;
}