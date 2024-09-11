#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>  
#include <chrono>     

using namespace std;

int main() {

    // Nombre del archivo a leer
    string filename = "random_1000000.txt"; // Cambia este nombre al archivo correspondiente

    // Vector para almacenar los números leídos del archivo
    vector<int> numbers;

    // Abrir el archivo para leer
    ifstream infile(filename);

    // Verificar si el archivo se abrió correctamente
    if (!infile.is_open()) {
        cerr << "Error al abrir el archivo " << filename << endl;
        return 1;
    }

    // Leer los números desde el archivo
    int num;
    while (infile >> num) {
        numbers.push_back(num);
    }

    infile.close();


    // Usar std::sort para ordenar el vector
    sort(numbers.begin(), numbers.end());


    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    return 0;
}