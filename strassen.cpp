#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int value : row) {
            cout << value << " ";
        }
        cout << endl;
    }
}

// Función para sumar dos matrices
vector<vector<int>> add(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    int m = A[0].size();
    vector<vector<int>> C(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

// Función para restar dos matrices
vector<vector<int>> subtract(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    int m = A[0].size();
    vector<vector<int>> C(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

// Función para dividir una matriz en submatrices
void split(const vector<vector<int>>& matrix, vector<vector<int>>& A, vector<vector<int>>& B, vector<vector<int>>& C, vector<vector<int>>& D) {
    int n = matrix.size();
    int mid = n / 2;
    for (int i = 0; i < mid; ++i) {
        for (int j = 0; j < mid; ++j) {
            A[i][j] = matrix[i][j];
            B[i][j] = matrix[i][j + mid];
            C[i][j] = matrix[i + mid][j];
            D[i][j] = matrix[i + mid][j + mid];
        }
    }
}

// Función de Strassen para multiplicar matrices
vector<vector<int>> strassen(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    if (n == 1) {
        return vector<vector<int>>{{A[0][0] * B[0][0]}};
    }

    int mid = n / 2;
    vector<vector<int>> A11(mid, vector<int>(mid));
    vector<vector<int>> A12(mid, vector<int>(mid));
    vector<vector<int>> A21(mid, vector<int>(mid));
    vector<vector<int>> A22(mid, vector<int>(mid));
    vector<vector<int>> B11(mid, vector<int>(mid));
    vector<vector<int>> B12(mid, vector<int>(mid));
    vector<vector<int>> B21(mid, vector<int>(mid));
    vector<vector<int>> B22(mid, vector<int>(mid));

    split(A, A11, A12, A21, A22);
    split(B, B11, B12, B21, B22);

    vector<vector<int>> M1 = strassen(add(A11, A22), add(B11, B22));
    vector<vector<int>> M2 = strassen(add(A21, A22), B11);
    vector<vector<int>> M3 = strassen(A11, subtract(B12, B22));
    vector<vector<int>> M4 = strassen(A22, subtract(B21, B11));
    vector<vector<int>> M5 = strassen(add(A11, A12), B22);
    vector<vector<int>> M6 = strassen(subtract(A21, A11), add(B11, B12));
    vector<vector<int>> M7 = strassen(subtract(A12, A22), add(B21, B22));

    vector<vector<int>> C11 = add(subtract(add(M1, M4), M5), M7);
    vector<vector<int>> C12 = add(M3, M5);
    vector<vector<int>> C21 = add(M2, M4);
    vector<vector<int>> C22 = add(subtract(add(M1, M3), M2), M6);

    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < mid; ++i) {
        for (int j = 0; j < mid; ++j) {
            C[i][j] = C11[i][j];
            C[i][j + mid] = C12[i][j];
            C[i + mid][j] = C21[i][j];
            C[i + mid][j + mid] = C22[i][j];
        }
    }
    return C;
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

int main() {
    
    auto A = loadMatrixFromFile("square_1000x1000.txt");
    auto B = loadMatrixFromFile("square_1000x1000.txt");

    auto result = strassen(A, B);

    printMatrix(result);

    return 0;
}