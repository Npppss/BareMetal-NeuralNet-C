#include <stdio.h>
#include <stdlib.h>
#include <math.h> // WAJIB untuk fungsi exp()
#include <time.h>

// --- [Asumsikan fungsi create_matrix, free_matrix, dot_product, add_bias, randomize_matrix dari Langkah 2 ada di sini] ---
typedef struct {
    int rows;
    int cols;
    double **data;
} Matrix;

Matrix* create_matrix(int rows, int cols) {
    Matrix *m = (Matrix*)malloc(sizeof(Matrix));
    m->rows = rows; m->cols = cols;
    m->data = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        m->data[i] = (double*)calloc(cols, sizeof(double));
    }
    return m;
}

void free_matrix(Matrix *m){
    if (m == NULL) return;
    for (int i = 0; i < m->rows; i++) {
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
Matrix* dot_product(Matrix *A, Matrix *B) {
    // ATURAN MUTLAK MATRIKS: Kolom A harus sama dengan Baris B
    if (A->cols != B->rows) {
        printf("FATAL ERROR: Dimensi tidak cocok untuk Dot Product! (%dx%d) dan (%dx%d)\n", 
            A->rows, A->cols, B->rows, B->cols);
        exit(1);
    }

    // Matriks hasil akan memiliki ukuran: Baris A x Kolom B
    Matrix *C = create_matrix(A->rows, B->cols);

    // Algoritma O(n^3) - Tiga perulangan bersarang
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->cols; j++) {
            double sum = 0.0;
            for (int k = 0; k < A->cols; k++) {
                sum += A->data[i][k] * B->data[k][j];
            }
            C->data[i][j] = sum;
        }
    }
    return C;
}

// Penambahan BIAS (Pengganti NumPy Broadcasting)
// Di NumPy, Z + b terjadi otomatis. Di C, kita harus menambakan bias (1 baris) 
// secara manual ke setiap baris dari matriks Z.
void add_bias(Matrix *m, Matrix *bias){
    if (m->cols != bias->cols || bias->rows != 1){
        printf("FATAL ERROR: Dimensi Bias salah!\n");
        exit(1);
    }
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            m->data[i][j] += bias->data[0][j];
        }
    }
}

// (Fungsi bantuan baru untuk menggandakan matriks, sangat berguna agar nilai Z asli tidak hilang)

Matrix* copy_matrix(Matrix *m){
    Matrix *copy= create_matrix(m->rows, m->cols);
    for (int i = 0; i < m->rows; i++){
        for (int j=0; j < m->cols; j++){
            copy->data[i][j] = m->data[i][j];
        }
    }
    return copy;
}

// Sturktur Dense Layer
typedef struct {
    int input_nodes;   // Matrix W
    int output_nodes;  // Matrix b
    Matrix *weights;   //Matriks W
    Matrix *biases;    //Matriks b
    Matrix *Z;        // Menyimpan nilai linear (X.W + b) sementara untuk Backprop
    Matrix *A;        // Menyimpan nilai aktivasi (sigmoid(Z)) sementara untuk Backprop
} DenseLayer;

// Inisialisasi Dense Layer
DenseLayer* create_dense_layer(int input_nodes, int output_nodes){
    DenseLayer *layer = (DenseLayer*)malloc(sizeof(DenseLayer));
    layer->input_nodes = input_nodes;
    layer->output_nodes = output_nodes;

    // Alokasi matriks bobot (Input x Output) dan inisialisasi acak
    layer->weights = create_matrix(input_nodes, output_nodes);
    randomize_matrix(layer->weights);

    // Alokasi matriks bias (1 x Output). Nilai awal otomatis 0.0 dari calloc
    layer->biases=create_matrix(1, output_nodes);

    //Z dan A diset NULL dulu karena baru akan terisi saat Forward Pass
    layer->Z=NULL;
    layer->A=NULL;

    return layer;
}

// Fungsi Aktivasi Sigmoid
// Fungsi ini mengubah isi matriks secara langsung (in-place)
void sigmoid_matrix(Matrix *m){
    for (int i = 0; i < m->rows; i++){
        for (int j = 0; j < m->cols; j++){
            // Rumus: 1 / (1 + e^-x)
            m->data[i][j] = 1.0 / (1.0 + exp(-m->data[i][j]));
        }
    }
}

// Forward Pass untuk Dense Layer
Matrix* forward_pass(DenseLayer *layer, Matrix *input){
    // Bersihkan sisa memori Z dan A dari proses sebelumnya (jika ada)
    if (layer->Z != NULL) free_matrix(layer->Z);
    if (layer->A != NULL) free_matrix(layer->A);

    // Langkah 1: Z = X . W
    layer->Z = dot_product(input, layer->weights);

    //langkah 2: Z = Z + b
    add_bias(layer->Z, layer->biases);

    // Langkah 3: A = Sigmoid(Z)
    // Kita gandakan Z ke A, lalu jalankan sigmoid pada A.
    // Tujuannya agar Z asli tetap utuh untuk keperluan kalkulus di Backpropagation nanti!
    layer->A = copy_matrix(layer->Z);
    sigmoid_matrix(layer->A);

    return layer->A;
}

// Fungsi Pembebas Memori Layer
void free_dense_layer(DenseLayer *layer) {
    if (layer == NULL) return;
    free_matrix(layer->weights);
    free_matrix(layer->biases);
    if (layer->Z != NULL) free_matrix(layer->Z);
    if (layer->A != NULL) free_matrix(layer->A);
    free(layer);
}