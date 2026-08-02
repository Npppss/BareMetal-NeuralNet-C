#include <stdio.h>
#include <stdlib.h> // Library wajib untuk malloc, calloc, dan free

// Struktur data untuk merepresentasikan matriks
typedef struct {
    int rows; // jumlah baris
    int cols; // jumlah kolom
    int **data; // pointer ke array 2D
}Matrix;

// fungsi alokasi memori untuk matriks
Matrix* createMatrix(int rows, int cols){
    // Pesan ruang di memori untuk kerangka struct Matrix
    Matrix *m=(Matrix*)malloc(sizeof(Matrix));
    m->rows=rows;
    m->cols=cols;

    // Pesan ruang untuk menampung baris (array of pointers)
    m->data=(double**)malloc(rows*sizeof(double*));

    // Pesan ruang untuk kolom di setiap baris
    for(int i=0, i<rows; i++){
        // Kita menggunakan calloc, bukan malloc di sini.
        // calloc otomatis mengisi memori dengan angka 0.0 (sangat berguna untuk inisialisasi Bias)
        m->data[i]=(double*)calloc(cols,sizeof(double));
    }

    return m;
}