#include <stdio.h>
#include <stdlib.h>
#include <math.h> // WAJIB untuk fungsi exp()
#include <time.h> // Dibutuhkan untuk membuat seed random (acak)

typedef struct {
    int rows;
    int cols;
    double **data;
} Matrix;

Matrix* create_matrix(int rows, int cols){
    Matrix *m = (Matrix*)malloc(sizeof(Matrix));
    m->rows = rows; m->cols = cols;
    m->data = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++){
        m->data[i] = (double*)calloc(cols, sizeof(double));
    }
    return m;
}

void free_matrix(Matrix *m){
    if (m == NULL) return;
    for (int i = 0; i < m->rows; i++){
        free(m->data[i]);
    }
    free(m->data);
    free(m);
}