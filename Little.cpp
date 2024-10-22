//
// Created by Mateusz on 16.10.2024.
//

#include <cstring>
#include "Little.h"
#include "MatrixModel.h"
#include "Helpers.h"
#include <iostream>

using namespace std;
void Little::algorithm(int **matrix, int n) {
    Helpers helpers;
    //Macierz, która będzie redukowana
    int** matrixToReduce = new int*[n+1];
    for (int i = 0; i < n+1; i++){
        matrixToReduce[i] = new int[n+1];
    }
    //Kopiujemy wartości z macierzy, aby nie pracować na oryginalnej oraz zmieniamy wartości 0 na inf
    //Dodajemy numery wierszy i kolumn
    for (int i = 0; i< n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 0) matrixToReduce[i+1][j+1] = 99;
            else matrixToReduce[i+1][j+1] = matrix[i][j];

        }
    }
    for (int i = 0; i < n+1 ; i++ ) {
        matrixToReduce[0][i] = i;
        matrixToReduce[i][0] = i;
    }
    n = n+1;

    for (int i = 0; i< n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrixToReduce[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    int r = reduceMatrix(matrixToReduce,n);

    for (int i = 0; i< n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrixToReduce[i][j] << " ";
        }
        cout << endl;
    }
    cout << "r: " << r << endl;

    int mp = countZeros(matrixToReduce, n);
    path* paths = new path[mp];
    paths = getMinPaths(matrixToReduce,n,mp);
    displayArrPath(paths);




}

int Little::findMin(int *arr, int n) {
   int min = arr[1];
   for (int i = 2 ; i < n ; i++) {
       if (arr[i] < min) min = arr[i];
   }
   return min;
}

int Little::reduceMatrix(int **matrix, int n) {
    int r = 0; //Wielkość redukcji (dolne ograniczenie)

    //Szukamy wartości minimalnych w każdym wierszu
    int* minRows = new int[n];
    for (int i = 1; i < n ; i++) {
        minRows[i] = findMin(matrix[i], n);
        r += minRows[i];
    }
    //helpers.displayArray(minRows,n);

    //Odejmujemy minimalne wartości od każdego elementu w wierszu
    for (int i = 1; i< n; i++) {
        for (int j = 1; j < n; j++) {
            if (matrix[i][j] != 99) matrix[i][j] = matrix[i][j] - minRows[i];
        }
    }

    //Szukamy wartości minimalnych w każdej kolumnie
    int* minCols = new int[n];
    for (int i = 1; i < n ; i++) {
        int *curCol = new int[n];
        for (int j = 0; j < n; j++) curCol[j] = matrix[j][i];
        minCols[i] = findMin(curCol, n);
        r += minCols[i];
        delete[] curCol;
    }
    //helpers.displayArray(minCols,n);

    //Odejmujemy minimalne wartości od każdego elementu w kolumnie
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (matrix[j][i] != 99) matrix[j][i] = matrix[j][i] - minCols[i];
        }
    }
    delete[] minRows;
    delete[] minCols;
    return r;
}

Little::path* Little::getMinPaths(int **matrix, int n, int mpSize) {
    path* minPaths = new path[mpSize + 1];
    int pathCounter = 0;
    for (int i = 1; i < n ; i++) {
        for (int j = 1 ; j < n; j++) {
            if (matrix[i][j] == 0) {
                path p;
                p.row = i;
                p.column = j;
                //Szukamy najmniejszego elementu w wierszu i w kolumnie nie licząc elementu ij
                int minR = 99;
                int minC = 99;
                for (int r = 1; r < n ; r++) {
                    if (r != j && matrix[i][r] < minR)  minR = matrix[i][r];
                    if (r != i && matrix[r][j] < minC) minC = matrix[r][j];
                }
                p.cost = minR + minC;
                minPaths[pathCounter] = p;
                pathCounter ++;
            }
        }
    }
    minPaths[mpSize] = arrPathEnd;
    return minPaths;
}

int Little::countZeros(int **matrix, int n) {
    int zeroCounter = 0;
    for (int i = 1; i < n ; i++) {
        for (int j = 1; j < n; j++) {
            if (matrix[i][j] == 0) zeroCounter ++;
        }
    }
    return zeroCounter;
}

bool Little::pathIsEmpty(Little::path *arrPath, int index) {
    if (arrPath[index].row == -1) return true;
    return false;
}

void Little::displayArrPath(Little::path *arrPath) {
    int i = 0;
    while (!pathIsEmpty(arrPath,i)) {
        cout << "( " << arrPath[i].row << " , " << arrPath[i].column << " )" << " = " << arrPath[i].cost << endl;
        i ++;
    }
}