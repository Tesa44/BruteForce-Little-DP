//
// Created by Mateusz on 10.10.2024.
//

#include "MatrixModel.h"
#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>

using namespace std;

//Funkcja tworząca dynamiczną macierz
//Wymagane jest wcześniejsze załadowanie rozmiaru macierzy do globalnej zmiennej n
//Macierz jest tworzona jako dynamiczna tablica, do której dodaje się n tablic dynamicznych
void MatrixModel::initMatrix() {
    matrix = new int*[n];
    for (int i = 0; i < n; i++){
        matrix[i] = new int[n];
    }
    //Wypełnanie macierzy zerami
    for (int i = 0 ; i < n ; i++ )
    {
        for (int j = 0 ; j < n ; j++ ) {
            matrix[i][j] = 0;
        }
    }
}


void MatrixModel::loadMatrixFromFile(std::string path) {
    fstream file;
    file.open(path, ios_base::in);
    file >> n; //Zczytanie pierwszej linii jako rozmiar macierzy
    //cout  << "n = "<< n << endl;
    initMatrix(); //Tworzenie nowej, pustej macierzy
    int number;
    //Wartości są odczytywane pojedynczo, koniec linii nie wpływa na odczyt
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> number;
            matrix[i][j] = number;
        }
    }
}

void MatrixModel::displayMatrix() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){
            printf("%-4d",matrix[i][j]);
        }
        printf("\n");
    }
}

void MatrixModel::generateMatrix(int matrixSize) {
    //Ustawienie globalnego rozmiaru macierzy
    n = matrixSize;

    initMatrix();
    //TODO init CONFIG class and add maxPath, minPath
    int maxPath = 15;
    int minPath = 1;
    int path;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) matrix[i][j] = 0;
            else {
                path = minPath + (rand() % ( maxPath - minPath + 1 ));
                matrix[i][j] = path;
            }
        }
    }







}
