#include <iostream>

using namespace std;

void transpose(int **matrix, int N) {
    // make the columns rows (basically)
    // instead of iterating by row
    // iterate by column
    // reversing the order of the rows --> rotated 90'
    for(int i = 0; i < N; i++) {
        for(int j = i + 1; j < N; j++) { // row 0, col 1, 2 // row 1, col, 2 // row 2
            swap(matrix[i][j], matrix[j][i]);
        }
    }
}

// Why transposing works
    // [0][0] -> [0][2]
    // [1][0] -> [0][1]
    // [2][0] -> [0][0]
    //
    // [0][1] -> [1][2]
    // [1][1] -> [1][1]
    // [2][1] -> [1][0]
    //
    // [0][2] -> [2][2]
    // [1][2] -> [2][1]
    // [2][2] -> [2][0]
    // 
// each of the columns becomes rows
// the row is then reversed

// rotates a matrix 90' clockwise
void rotate(int **matrix, int N) {
    transpose(matrix, N);
    for (int i = 0; i < N; i++) {
        // reverse each row
        // swap using middle as the pivot
        for(int j = 0; j < N/2; j++) {
            swap(matrix[i][j], matrix[i][N-j-1]);
        }
    }
}

void printMatrix(int** matrix, int N) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int N = 3;
    int** matrix = new int*[N];
    for(int i = 0; i < N; ++i) {
        matrix[i] = new int[N]; // allocate our rows
    }

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            matrix[i][j] = rand() % 10;
        }
    }

    cout << "=== original ===" << endl;

    printMatrix(matrix, N);

    cout << "=== rotated ===" << endl;

    rotate(matrix, N);
    printMatrix(matrix, N);
}