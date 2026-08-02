#include <stdio.h>
#include <stdlib.h> // Library wajib untuk malloc, calloc, dan free

// Struktur data untuk merepresentasikan matriks
typedef struct {
    int rows; // jumlah baris
    int cols; // jumlah kolom
    double **data; // pointer ke array 2D
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
    for(int i=0; i<rows; i++){
        // Kita menggunakan calloc, bukan malloc di sini.
        // calloc otomatis mengisi memori dengan angka 0.0 (sangat berguna untuk inisialisasi Bias)
        m->data[i]=(double*)calloc(cols,sizeof(double));
    }

    return m;
}

// fungsi untuk membebaskan memori matriks
void free_matrix(Matrix *m){
    // Jika matriks kosong, tidak perlu melakukan apa-apa
    if(m==NULL) return;

    // Bebaskan memori dari dalam ke luar!
    // 1. Bebaskan memori setiap baris (kolom)
    for(int i=0; i<m->rows; i++){
        free(m->data[i]);
    }

    // 2. Bebaskan array penunjuk baris
    free(m->data);

    //3. Terakhir, bebaskan kerangka struct utama
    free(m);
}

int main(){
    printf("Ujicoba alokasi memori untuk matriks\n");

    // Membuat matriks ukuran 2 Baris x 3 Kolom
    Matrix *my_matrix=createMatrix(2,3);

    // Mengisi data secara manual untuk uji coba
    my_matrix->data[0][0] = 1.5;
    my_matrix->data[0][1] = 2.0;
    my_matrix->data[0][2] = 3.1;
    
    //Mencetak isi matriks
    printf("Isi matriks:\n");
    for (int i=0; i<my_matrix->rows; i++){
        for(int j=0; j<my_matrix->cols; j++){
            printf("%.2f ", my_matrix->data[i][j]);
        }
        printf("\n");
    }

    // WAJIB: Kembalikan memori ke OS!
    free_matrix(my_matrix);
    printf("\nMemori berhasil dibebaskan. Tidak ada Memory Leak!\n");
    
    return 0;
}