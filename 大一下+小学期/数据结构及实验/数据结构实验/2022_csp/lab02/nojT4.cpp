#include <iostream>
using namespace std;

const int MAX_SIZE = 1000;  

struct Triple {  
    int row, col;
    int value;
};

struct SparseMatrix {
    Triple data[MAX_SIZE + 1];
    int rows, cols, numNonZeroElements;
};

void initSparseMatrix(SparseMatrix* matrix) {
    matrix->rows = 0;
    matrix->cols = 0;
    matrix->numNonZeroElements = 0;
}

void createSparseMatrix(SparseMatrix* matrix) {
    for (int i = 1; i <= matrix->numNonZeroElements; i++) {
        cin >> matrix->data[i].row >> matrix->data[i].col >> matrix->data[i].value;
    }
}

void addSparseMatrices(const SparseMatrix& matrix1, const SparseMatrix& matrix2, SparseMatrix* resultMatrix) {
    int i = 1, j = 1, k = 0;
    while (i <= matrix1.numNonZeroElements && j <= matrix2.numNonZeroElements) {
        if (matrix1.data[i].row < matrix2.data[j].row) {
            resultMatrix->data[++k] = matrix1.data[i++];
        } else if (matrix1.data[i].row > matrix2.data[j].row) {
            resultMatrix->data[++k] = matrix2.data[j++];
        } else {
            if (matrix1.data[i].col < matrix2.data[j].col) {
                resultMatrix->data[++k] = matrix1.data[i++];
            } else if (matrix1.data[i].col > matrix2.data[j].col) {
                resultMatrix->data[++k] = matrix2.data[j++];
            } else {
                resultMatrix->data[++k].row = matrix1.data[i].row;
                resultMatrix->data[k].col = matrix1.data[i].col;
                resultMatrix->data[k].value = matrix1.data[i].value + matrix2.data[j].value;
                i++;
                j++;
            }
        }
    }
    while (i <= matrix1.numNonZeroElements) {
        resultMatrix->data[++k] = matrix1.data[i++];
    }
    while (j <= matrix2.numNonZeroElements) {
        resultMatrix->data[++k] = matrix2.data[j++];
    }
    resultMatrix->numNonZeroElements = k;
}

void printSparseMatrix(const SparseMatrix& matrix) {
    for (int i = 1; i <= matrix.numNonZeroElements; i++) {
        cout << matrix.data[i].row << " " << matrix.data[i].col << " " << matrix.data[i].value << endl;
    }
}

int main() {
    SparseMatrix matrix1, matrix2, resultMatrix;
    initSparseMatrix(&matrix1);
    initSparseMatrix(&matrix2);
    initSparseMatrix(&resultMatrix);
    cin >> matrix1.rows >> matrix1.cols >> matrix1.numNonZeroElements >> matrix2.numNonZeroElements;
    createSparseMatrix(&matrix1);
    matrix2.rows = matrix1.rows;
    matrix2.cols = matrix1.cols;
    createSparseMatrix(&matrix2);
    addSparseMatrices(matrix1, matrix2, &resultMatrix);
    printSparseMatrix(resultMatrix);
    return 0;
}
