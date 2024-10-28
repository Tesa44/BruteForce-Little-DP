//
// Created by Mateusz on 16.10.2024.
//

#include <cstring>
#include "Little.h"
#include "../MatrixModel.h"
#include "../Helpers.h"
#include <iostream>

using namespace std;
Little::path* Little::algorithm(int **matrix, int n) {
    path* finalPath = new path[n+1];
    finalPath[n] = arrPathEnd;
    //Macierz, która będzie redukowana (większy rozmiar, ponieważ dodajemy wiersz i kolumnę z numeracją)
    int **matrixToReduce = new int *[n + 1];
    for (int i = 0; i < n + 1; i++) {
        matrixToReduce[i] = new int[n + 1];
    }
    //Kopiujemy wartości z macierzy, aby nie pracować na oryginalnej oraz zmieniamy wartości 0 na inf
    //Dodajemy numery wierszy i kolumn
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 0) matrixToReduce[i + 1][j + 1] = 99999;
            else matrixToReduce[i + 1][j + 1] = matrix[i][j];

        }
    }
    //Numerujemy wiersze i kolumny
    for (int i = 0; i < n + 1; i++) {
        matrixToReduce[0][i] = i;
        matrixToReduce[i][0] = i;
    }
    //Zmieniamy rozmiar macierzy, ponieważ dodaliśmy numerację
    n = n + 1;

    //Pierwsza redukcja macierzy do C0
    int w0 = reduceMatrix(matrixToReduce, n);
    int i = 0;
    //Kolejne redukcje  i zmniejszenia macierzy
    while (n > 1) {
        //Liczymy, ile zer występuje w macierzy, aby wiedzieć jaki ustawić rozmiar listy ze ścieżkami
        int mp = countZeros(matrixToReduce, n);
        //Szukamy odcinków (i-j), dla których Cij = 0 (koszt włączenia jest najmniejszy)
        path *paths = getMinPaths(matrixToReduce, n, mp);
        //Do sprawdzania ścieżek
//        cout << "Sciezki: ";
//        displayArrPath(paths);
//        cout << endl;

        //Wybieramy ścieżkę, która ma największy koszt wyłączenia i dodajemy ją do wynikowej ścieżki
        path maxCostPath = findMaxCost(paths);
        finalPath[i] = maxCostPath;
        i++;
        //cout << maxCostPath.row << " -> " << maxCostPath.column << endl;

        //Z macierzy usuwamy i-ty wiersz i j-tą kolumnę na podstawie wybranego odcinka (i-j). Cji ustawiamy jako inf, aby zablokować drogę powrotną
        matrixToReduce = deleteRowAndCol(matrixToReduce, n, maxCostPath.row, maxCostPath.column);
        //Zmniejszamy rozmiar macierzy, ponieważ usunęliśmy jeden wiersz i kolumnę
        n--;
        //Redukujemy macierz, szukając najmniejszego elementu w każdym wierszu i kolumnie i odejmując go od wszytkich elementów w danym wierszu lub kolumnie
        w0 += reduceMatrix(matrixToReduce, n);
    }
    //cout << "R = " << w0 << endl;  //Długość całej drogi
    return finalPath;
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

int Little::findMin(int *arr, int n) {
   int min = arr[1];
   for (int i = 2 ; i < n ; i++) {
       if (arr[i] < min) min = arr[i];
   }
   return min;
}

Little::path Little::findMaxCost(Little::path *arrPath) {
        int maxCost = -1;
        path maxCostPath;
        int i = 0;
        while(!pathIsEmpty(arrPath,i)) {
            if (arrPath[i].cost > maxCost) {
                maxCost = arrPath[i].cost;
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

    //Odejmujemy minimalne wartości od każdego elementu w wierszu
    for (int i = 1; i< n; i++) {
        for (int j = 1; j < n; j++) {
            if (matrix[i][j] < 90000) matrix[i][j] = matrix[i][j] - minRows[i];
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

    //Odejmujemy minimalne wartości od każdego elementu w kolumnie
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (matrix[j][i] < 90000) matrix[j][i] = matrix[j][i] - minCols[i];
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
                int minR = 99999;
                int minC = 99999;
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
    if (checkRow and checkCol) {
        newMatrix[curCol][curRow] = 99999;
    }

    return newMatrix;
}

int* Little::convertPathToArr(Little::path *arrPath, int n) {
    int *arr = new int[n+1];
    // Znajdujemy pierwszy element ścieżki
    int obecnyPoczatek = arrPath[0].row;
    arr[0] = obecnyPoczatek;

    // Zmienna do śledzenia aktualnego miejsca w wynikowej tablicy
    int index = 1;

    // Iterujemy przez odcinki, aż utworzymy całą ścieżkę
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (arrPath[j].row == obecnyPoczatek) {
                // -1, ponieważ miasta były iterowane od 1 (na poczet algorytmu), a chcemy, żeby były od 0.
                arr[index++] = arrPath[j].column-1;
                obecnyPoczatek = arrPath[j].column-1;
                break;
            }
        }
    }
    //Odcinek powrotny
    arr[n] = arr[0];
    return arr;
}