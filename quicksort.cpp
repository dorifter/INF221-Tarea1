#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int partition(vector<int>& arr, int low, int high) {

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {

    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {

    // Nombre del archivo a leer
    string filename = "sorted_1000000.txt"; // Cambia este nombre al archivo correspondiente

    // Vector para almacenar los números leídos del archivo
    vector<int> numbers;

    // Abrir el archivo para leer
    ifstream infile(filename);
    if (!infile) {
        cerr << "No se pudo abrir el archivo " << filename << std::endl;
        return 1;
    }

    // Leer los números desde el archivo
    int num;
    while (infile >> num) {
        numbers.push_back(num);
    }
    infile.close();

    int size = numbers.size();


    quickSort(numbers, 0, size - 1);


    for (const int& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    
    return 0;
}