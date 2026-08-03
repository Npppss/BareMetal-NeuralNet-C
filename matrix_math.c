#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Dibutuhkan untuk membuat seed random (acak)


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

// Fungsi Bantuan untuk Mencetak Matriks
void print_matrix(Matrix *m, const char *name) {
    printf("Matriks %s (%dx%d):\n", name, m->rows, m->cols);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            printf("%8.4f ", m->data[i][j]);
        }
        printf("\n");
    }
    printf("\n");

}

//Uji coba Matematika Forward Pass
int main() {
    // Wajib dipanggil sekali di awal program agar angka random benar-benar acak berdasarkan waktu
    srand(time(NULL)); 

    printf("Simulasi Linear Layer (Z = X.W + b) di C\n\n");

    // 1. Buat Matriks Input X (Anggap saja 2 Data, masing-masing 3 Fitur) -> (2x3)
    Matrix *X = create_matrix(2, 3);
    X->data[0][0] = 0.5; X->data[0][1] = 0.8; X->data[0][2] = 0.2;
    X->data[1][0] = 0.1; X->data[1][1] = 0.9; X->data[1][2] = 0.6;
    print_matrix(X, "X (Input)");

    // 2. Buat Matriks Bobot W (3 Fitur Input -> 2 Neuron Output) -> (3x2)
    Matrix *W = create_matrix(3, 2);
    randomize_matrix(W); // Isi dengan bobot acak antara -1 dan 1
    print_matrix(W, "W (Weights)");

    // 3. Buat Matriks Bias b (1 Baris, 2 Neuron Output) -> (1x2)
    Matrix *b = create_matrix(1, 2);
    // Karena kita pakai calloc sebelumnya, nilai awal bias sudah pasti 0.0
    // Kita isi manual agar terlihat bedanya
    b->data[0][0] = 0.1; b->data[0][1] = -0.1;
    print_matrix(b, "b (Bias)");

    // 4. OPERASI UTAMA: Z = X . W
    Matrix *Z = dot_product(X, W);
    
    // 5. OPERASI UTAMA: Z = Z + b
    add_bias(Z, b);

    // Hasil Akhir Linear Pass
    print_matrix(Z, "Z (Output Linear: X.W + b)");

    // WAJIB: Cegah Memory Leak!
    free_matrix(X);
    free_matrix(W);
    free_matrix(b);
    free_matrix(Z);

    return 0;
}