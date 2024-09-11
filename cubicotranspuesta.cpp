#include <iostream>
#include <vector>
#include <fstream>
#include <string>


using namespace std;


void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int value : row) {
            cout << value << " ";
        }
        cout << endl;
    }
}

// Función para transponer una matriz
vector<vector<int>> transpose(const vector<vector<int>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    vector<vector<int>> transposed(cols, vector<int>(rows));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            transposed[j][i] = matrix[i][j];
        }
    }
    return transposed;
}


// Función para cargar una matriz desde un archivo
vector<vector<int>> loadMatrixFromFile(const string& filename) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error al abrir el archivo: " << filename << endl;
        exit(1);
    }
    
    int m, n;
    infile >> m >> n;
    vector<vector<int>> matrix(m, vector<int>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            infile >> matrix[i][j];
        }
    }
    infile.close();
    return matrix;
}

// Función para multiplicar matrices usando el método cúbico optimizado con transposición
vector<vector<int>> multiplyOptimized(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();        // Filas de A
    int m = A[0].size();     // Columnas de A / Filas de B
    int p = B[0].size();     // Columnas de B
    vector<vector<int>> C(n, vector<int>(p, 0)); // Matriz resultado

    // Transponer la segunda matriz para mejorar la localidad de datos
    vector<vector<int>> B_transposed = transpose(B);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < p; ++j) {
            for (int k = 0; k < m; ++k) {
                C[i][j] += A[i][k] * B_transposed[j][k];
            }
        }
    }
    return C;
}

int main() {
    auto A = loadMatrixFromFile("square_10x10.txt");
    auto B = loadMatrixFromFile("square_10x10.txt");


    auto result = multiplyOptimized(A, B);

    printMatrix(result);

    return 0;
}