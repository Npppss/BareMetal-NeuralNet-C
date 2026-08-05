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


// Inisialisasi matriks dengan nilai acak (Pengganti np.random.randn)
void randomize_matrix(Matrix *m){
    for (int i = 0; i < m->rows; i++){
        for (int j = 0; j < m->cols; j++){
            // rand() menghasilkan angka positif besar.
            // Kita ubah agar rentangnya menjadi antara -1.0 hingga 1.0
            double random_value = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
            m->data[i][j] = random_value;
        }
    }
}

// perkalian matriks / Dot Product (Pengganti np.dot)
Matrix* dot_product(Matrix *A, Matrix *B){
    // ATURAN MUTLAK MATRIKS: Kolom A harus sama dengan Baris B
    if (A->cols != B->rows){
        printf("FATAL ERROR: Dimensi tidak cocok untuk Dot Product! (%dx%d) dan (%dx%d)\n", 
            A->rows, A->cols, B->rows, B->cols);
        exit(1);
    }

     // Matriks hasil akan memiliki ukuran: Baris A x Kolom B
    Matrix *C = create_matrix(A->rows, B->cols);
}