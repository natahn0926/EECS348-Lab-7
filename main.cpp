#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

const int SIZE = 4; // matrix is 4x4 for this lab template

class Matrix {
private:
    int data[SIZE][SIZE];

public:
    Matrix() {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                data[i][j] = 0;
            }
        }
    }

    // Keep template function for debugging if needed
    void readFromStdin() {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                cin >> data[i][j];
            }
        }
    }

    void setValue(int row, int col, int value) {
        data[row][col] = value;
    }

    int getValue(int row, int col) const {
        return data[row][col];
    }

    void display() const {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                cout << setw(5) << data[i][j];
            }
            cout << '\n';
        }
    }

    Matrix operator+(const Matrix& other) const {
        Matrix result;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        Matrix result;
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                result.data[i][j] = 0;
                for (int k = 0; k < SIZE; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    int sumOfDiagonals() const {
        int sum = 0;
        for (int i = 0; i < SIZE; ++i) {
            sum += data[i][i];                  // main diagonal
            sum += data[i][SIZE - 1 - i];       // secondary diagonal
        }
        return sum;
    }

    void swapRows(int row1, int row2) {
        if (row1 < 0 || row1 >= SIZE || row2 < 0 || row2 >= SIZE) {
            cout << "Invalid row indices. Rows were not swapped." << endl;
            return;
        }

        for (int j = 0; j < SIZE; ++j) {
            int temp = data[row1][j];
            data[row1][j] = data[row2][j];
            data[row2][j] = temp;
        }
    }
};

vector<int> readAllIntegersFromFile(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        throw runtime_error("Failed to open file: " + filePath);
    }

    vector<int> values;
    int value;
    while (file >> value) {
        values.push_back(value);
    }

    return values;
}

void loadMatricesFromFile(const string& filePath, Matrix& mat1, Matrix& mat2) {
    vector<int> values = readAllIntegersFromFile(filePath);

    const int expectedWithoutSize = 2 * SIZE * SIZE;
    const int expectedWithSize = 1 + 2 * SIZE * SIZE;

    int startIndex = 0;

    if (static_cast<int>(values.size()) == expectedWithSize) {
        if (values[0] != SIZE) {
            throw runtime_error("Matrix size in file does not match SIZE = 4.");
        }
        startIndex = 1;
    } else if (static_cast<int>(values.size()) != expectedWithoutSize) {
        ostringstream oss;
        oss << "Input file must contain either " << expectedWithoutSize
            << " integers (two 4x4 matrices) or " << expectedWithSize
            << " integers (size + two 4x4 matrices).";
        throw runtime_error(oss.str());
    }

    int index = startIndex;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            mat1.setValue(i, j, values[index++]);
        }
    }

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            mat2.setValue(i, j, values[index++]);
        }
    }
}

int main() {
    const string filePath = "matrix-data.txt";

    Matrix mat1;
    Matrix mat2;

    try {
        loadMatricesFromFile(filePath, mat1, mat2);
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }

    cout << "Matrix 1:" << endl;
    mat1.display();
    cout << endl;

    cout << "Matrix 2:" << endl;
    mat2.display();
    cout << endl;

    Matrix sum = mat1 + mat2;
    cout << "Sum of matrices:" << endl;
    sum.display();
    cout << endl;

    Matrix product = mat1 * mat2;
    cout << "Product of matrices:" << endl;
    product.display();
    cout << endl;

    cout << "Sum of diagonal elements of Matrix 1: " << mat1.sumOfDiagonals() << endl;
    cout << endl;

    mat1.swapRows(0, 2);
    cout << "Matrix 1 after swapping row 0 and row 2:" << endl;
    mat1.display();

    return 0;
}