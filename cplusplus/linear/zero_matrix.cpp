#include <iostream>
#include <cstring>
#include <vector>

using namespace std; ///BAD

// if an element in a M x N is 0, make the entire row and column is 0
void zeroed(int** matrix, int M, int N) {
    if(!matrix)return;

    vector<int> toZeroCol;
    for(int i = 0; i < M; i++) {
        bool toZero = false;
        if(!matrix[i]) continue; 
        for(int j = 0; j < N; j++) {
            if(matrix[i][j] == 0) {
                // keep the M to 0 out column
                toZero = true;
                toZeroCol.emplace_back(j);
            }
        }
        // done with this row, so we can 0 it
        if(toZero) {
            memset(matrix[i], 0, N * sizeof(matrix[i][0]));
        }
    }

    // zero out the column
    for (auto c : toZeroCol) {
        for(int i = 0; i < M; i++) {
            matrix[i][c] = 0;
        }
    }
}

void printMatrix(int** matrix, int M, int N) {
    for(int i = 0; i < M; i++) {
        for(int j = 0; j < N; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}


int main() {
    int M = 4;  // 4 rows by 3 columns
    int N = 3;
    int** matrix = new int*[M];
    for(int i = 0; i < M; ++i) {
        matrix[i] = new int[N]; // allocate our rows
    }

    for(int i = 0; i < M; ++i) {
        for(int j = 0; j < N; ++j) {
            matrix[i][j] = rand() % 10;
        }
    }

    cout << "=== original ===" << endl;

    printMatrix(matrix, M, N);

    cout << "=== zeroed ===" << endl;

    zeroed(matrix, M, N);
    printMatrix(matrix, M, N);

    for(int i = 0; i < M; ++i) {
        for(int j = 0; j < N; ++j) {
            matrix[i][j] = rand() % 10;
        }
    }

    
    // make the column all 0's
    for(int i = 0; i < N; i++) {
        matrix[2][i] = 0;
    }

    cout << "=== original ===" << endl;

    printMatrix(matrix, M, N);

    cout << "=== zeroed ===" << endl;

    zeroed(matrix, M, N);
    printMatrix(matrix, M, N);

    for(int i = 0; i < M; ++i) {
        for(int j = 0; j < N; ++j) {
            matrix[i][j] = rand() % 10;
        }
    }

    // make the row all 0's
    memset(matrix[0], 0, sizeof(matrix[0][0]));

    cout << "=== original ===" << endl;

    printMatrix(matrix, M, N);

    cout << "=== zeroed ===" << endl;

    zeroed(matrix, M, N);
    printMatrix(matrix, M, N);
}