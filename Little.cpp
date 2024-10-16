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
    int** matrixReduced = new int*[n];
    for (int i = 0; i < n; i++){
        matrixReduced[i] = new int[n];
    }
    //Kopiujemy wartości z macierzy, aby nie pracować na oryginalnej oraz zmieniamy wartości 0 na inf
    for (int i = 0; i< n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 0) matrixReduced[i][j] = 99;
            else matrixReduced[i][j] = matrix[i][j];
        }
    }

    int r = reduceMatrix(matrixReduced,n);

    int mp = countZeros(matrixReduced, n);
    path* paths = new path[mp];
    paths = getMinPaths(matrixReduced,n,mp);
    //displayArrPath(paths);

//    for (int i = 0; i< n; i++) {
//        for (int j = 0; j < n; j++) {
//            cout << matrixReduced[i][j] << " ";
//        }
//        cout << endl;
//    }
}

int Little::findMin(int *arr, int n) {
   int min = arr[0];
   for (int i = 1 ; i < n ; i++) {
       if (arr[i] < min) min = arr[i];
   }
   return min;
}

int Little::reduceMatrix(int **matrix, int n) {
    int r = 0; //Wielkość redukcji (dolne ograniczenie)

    //Szukamy wartości minimalnych w każdym wierszu
    int* minRows = new int[n];
    for (int i = 0; i < n ; i++) {
        minRows[i] = findMin(matrix[i], n);
        r += minRows[i];
    }
    //helpers.displayArray(minRows,n);

    //Odejmujemy minimalne wartości od każdego elementu w wierszu
    for (int i = 0; i< n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] != 99) matrix[i][j] = matrix[i][j] - minRows[i];
        }
    }

    //Szukamy wartości minimalnych w każdej kolumnie
    int* minCols = new int[n];
    for (int i = 0; i < n ; i++) {
        int *curCol = new int[n];
        for (int j = 0; j < n; j++) curCol[j] = matrix[j][i];
        minCols[i] = findMin(curCol, n);
        r += minCols[i];
        delete[] curCol;
    }
    //helpers.displayArray(minCols,n);

    //Odejmujemy minimalne wartości od każdego elementu w kolumnie
    for (int i = 0; i< n; i++) {
        for (int j = 0; j < n; j++) {
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
    for (int i = 0; i < n ; i++) {
        for (int j = 0 ; j < n; j++) {
            if (matrix[i][j] == 0) {
                path p;
                p.row = i;
                p.column = j;
                //Szukamy najmniejszego elementu w wierszu i w kolumnie nie licząc elementu ij
                int minR = 99;
                int minC = 99;
                cout << "wiersz: ";
                for (int r = 0; r < n ; r++) {
                    if (r != j && matrix[i][r] < minR)  minR = matrix[i][r];
                    if (r != i && matrix[r][j] < minC) minC = matrix[r][j];
                }
                cout << endl;
                p.cost = minR + minC;
                minPaths[pathCounter] = p;
                pathCounter ++;
            }
        }
    }
    minPaths[mpSize] = arrPathEnd;
    displayArrPath(minPaths);
    return minPaths;
}

int Little::countZeros(int **matrix, int n) {
    int zeroCounter = 0;
    for (int i = 0; i < n ; i++) {
        for (int j = 0; j < n; j++) {
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