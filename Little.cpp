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
    int **matrixToReduce = new int *[n + 1];
    for (int i = 0; i < n + 1; i++) {
        matrixToReduce[i] = new int[n + 1];
    }
    //Kopiujemy wartości z macierzy, aby nie pracować na oryginalnej oraz zmieniamy wartości 0 na inf
    //Dodajemy numery wierszy i kolumn
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 0) matrixToReduce[i + 1][j + 1] = 99;
            else matrixToReduce[i + 1][j + 1] = matrix[i][j];

        }
    }
    for (int i = 0; i < n + 1; i++) {
        matrixToReduce[0][i] = i;
        matrixToReduce[i][0] = i;
    }
    n = n + 1;

//    for (int i = 0; i< n; i++) {
//        for (int j = 0; j < n; j++) {
//            cout << matrixToReduce[i][j] << " ";
//        }
//        cout << endl;
//    }
//    cout << endl;
    //Redukcja macierzy do C0
    int w0 = reduceMatrix(matrixToReduce, n);

//    for (int i = 0; i< n; i++) {
//        for (int j = 0; j < n; j++) {
//            cout << matrixToReduce[i][j] << " ";
//        }
//        cout << endl;
//    }
//    cout << "r: " << r << endl;
//    cout << endl;
//    int mp = countZeros(matrixToReduce, n);
//    path* paths = new path[mp];
//    //Szukanie optymalnych Kosztów wyłączeń
//    paths = getMinPaths(matrixToReduce,n,mp);
//    //displayArrPath(paths);
//
//    //Szukanie pierwszej ścieżki z największym kosztem wyłączeń
//    path maxCostPath = findMaxCost(paths);
//
//    //Tworzenie macierzy C1 (usuwanie wiersza i kolumny)
//
//    int** c1 = deleteRowAndCol(matrixToReduce,n,maxCostPath.row,maxCostPath.column);
//
//    for (int i = 0; i< n-1; i++) {
//        for (int j = 0; j < n-1; j++) {
//            cout << c1[i][j] << " ";
//        }
//        cout << endl;
//    }
//    rec1(matrixToReduce, n, w0);
    while (n > 1) {
        int mp = countZeros(matrixToReduce, n);
        path *paths = getMinPaths(matrixToReduce, n, mp);
        //cout << "Sciezki: ";
        //displayArrPath(paths);
        //cout << endl;

        path maxCostPath = findMaxCost(paths);
        cout << maxCostPath.row << " -> " << maxCostPath.column << endl;
        matrixToReduce = deleteRowAndCol(matrixToReduce, n, maxCostPath.row, maxCostPath.column);

        n--;
        w0 += reduceMatrix(matrixToReduce, n);
//            for (int i = 0; i< n; i++) {
//                for (int j = 0; j < n; j++) {
//                    cout << matrixToReduce[i][j] << " ";
//                }
//                cout << endl;
//            }
//            cout << endl;
    }
    cout << "total: " << w0 << endl;
}






int Little::rec1(int **matrix, int n, int kres_dolny) {
    if (n == 1) {
        int mp = countZeros(matrix, n);
        path* paths = getMinPaths(matrix,n,mp);
        path maxCostPath = findMaxCost(paths);
        cout << maxCostPath.row << " -> " << maxCostPath.column << endl;
        return 0;
    }
    else {
        int mp = countZeros(matrix, n);
        path *paths = getMinPaths(matrix, n, mp);
        path maxCostPath = findMaxCost(paths);
        int **c1 = deleteRowAndCol(matrix, n, maxCostPath.row, maxCostPath.column);
        int r = reduceMatrix(matrix, n - 1);
        return rec1(matrix, n - 1, kres_dolny + r);
    }
}




int** Little::createMatrix(int n) {
    // Alokowanie pamięci dla wskaźnika do wierszy
    int** matrix = new int*[n];

    // Alokowanie pamięci dla każdej kolumny w każdym wierszu
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
    }
    return matrix;
}

void Little::deleteMatrix(int** matrix, int n) {
    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}


int Little::findMin(int *arr, int n) {
   int min = arr[1];
   for (int i = 2 ; i < n ; i++) {
       if (arr[i] < min) min = arr[i];
   }
   return min;
}

Little::path Little::findMaxCost(Little::path *arrPath) {
        int maxCost = -1;
        int maxCostId = -1;
        path maxCostPath;
        int i = 0;
        while(!pathIsEmpty(arrPath,i)) {
            if (arrPath[i].cost > maxCost) {
                maxCost = arrPath[i].cost;
                maxCostId = i;
                maxCostPath = arrPath[i];
            }
            i++;
        }
        return maxCostPath;
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
                p.row = matrix[i][0];
                p.column = matrix[0][j];
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

int** Little::deleteRowAndCol(int **matrix, int n, int rowToDelete, int colToDelete) {

    int** newMatrix = createMatrix(n-1);
    int rowIdToDelete = 0;
    int colIdToDelete = 0;

    //Szukamy id wiersza i kolumny, który należy usunąć (liczymy od zera)
    while (matrix[rowIdToDelete][0] != rowToDelete) {
        rowIdToDelete++;
    };
    while (matrix[0][colIdToDelete] != colToDelete) {
        colIdToDelete ++;
    };

    //cout << "Id wiersza: " << rowIdToDelete << " Id kolumny: " << colIdToDelete << endl;
    //Przepisujemy wartości ze starej macierzy pomijając id wiersza i kolumny, którą należało usunąć
    int curRow = 0;
    int curCol = 0;
    for (int i = 0; i < n ; i++) {
        if (i == rowIdToDelete) continue;

        curCol = 0;
        for (int j = 0; j < n; j++) {
            if (j == colIdToDelete) continue;

            //Przepisujemy wartości do nowej macierzy
            newMatrix[curRow][curCol] = matrix[i][j];
            curCol++;
        }
        curRow++;
    }
    //Ustawiamy drogę powrotną na inf o ile istnieje
    bool checkRow = false;
    curRow = 0;
    bool checkCol = false;
    curCol = 0;
    for (int i = 1; i < n-1; i++) {
        //Sprawdzamy, czy istnieje wiersz, w którym może być droga powrotna
        if (newMatrix[0][i] == rowToDelete) {
            checkRow = true;
            curRow = i;
        }
        //Tak samo z kolumną
        if (newMatrix[i][0] == colToDelete) {
            checkCol = true;
            curCol = i;
        }
    }
    //Jeżeli jest taki wiersz i kolumna to ustawiamy inf jako droga powrotna
    if (checkRow and checkCol) newMatrix[curRow][curCol] = 99;


//    for (int i = 0; i< n-1; i++) {
//        for (int j = 0; j < n-1; j++) {
//            cout << newMatrix[i][j] << " ";
//        }
//        cout << endl;
//    }
//    cout << endl;
    return newMatrix;
}