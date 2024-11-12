//
// Created by Mateusz on 04.11.2024.
//



//
// Created by Mateusz on 04.11.2024.
//

#define MAX 999999;
#include "DynamicProg.h"
#include <cmath>
#include <cstdio>

int* DynamicProg::algorithm(int** matrix, int n)
{
    createTSPMatrix(n);
    createMemoMatrix(pow(2,n), n);
    createPathMatrix(pow(2,n), n);
    size = n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            TSPmatrix[i][j] = matrix[i][j];
        }
    }

    int result = TSP(1,0);

    int* finalPath = new int[size+1];
    finalPath[0] = 0; //Pierwsze miasto
    int citiesVisited = 1;
    int position = 0;
    for (int i = 0; i < size - 1; i++)
    {
        // Odwiedzamy n-1 pozostałych miast
        position = pathMatrix[citiesVisited][position]; // Znajdujemy następne miasto na ścieżce
        citiesVisited |= (1 << position); // Aktualizujemy stan wizyt
        finalPath[i+1] = position;
    }
    return finalPath;
}



void DynamicProg::createTSPMatrix(int n)
{
    TSPmatrix = new int*[n];
    for (int i = 0; i < n; i++)
    {
        TSPmatrix[i] = new int[n];
    }
}

void DynamicProg::createMemoMatrix(int n, int m)
{
    memoMatrix = new int*[n];
    for (int i = 0; i < n; i++)
    {
        memoMatrix[i] = new int[m];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            memoMatrix[i][j] = -1;
        }
    }
}

void DynamicProg::createPathMatrix(int n, int m)
{
    pathMatrix = new int*[n];
    for (int i = 0; i < n; i++)
    {
        pathMatrix[i] = new int[m];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            pathMatrix[i][j] = -1;
        }
    }
}
void DynamicProg::printPath(int mark, int position) {
    int citiesVisited = mark; // Zachowujemy stan wizyt
    printf("Path: 0 "); // Zaczynamy od miasta 0
    for (int i = 0; i < size - 1; i++) { // Odwiedzamy n-1 pozostałych miast
        position = pathMatrix[citiesVisited][position]; // Znajdujemy następne miasto na ścieżce
        citiesVisited |= (1 << position); // Aktualizujemy stan wizyt
        printf("-> %d ", position); // Drukujemy miasto
    }
    printf("-> 0\n"); // Powrót do miasta startowego
}



int DynamicProg::TSP(int mark, int position)
{
    int completed_visit = (1 << size) - 1;
    if (mark == completed_visit) {
        return TSPmatrix[position][0];
    }
    if (memoMatrix[mark][position] != -1) {
        return memoMatrix[mark][position];
    }
    int answer = MAX;
    for (int city = 0; city < size; city++) {
        if ((mark & (1 << city)) == 0) {
            int newAnswer = TSPmatrix[position][city] + TSP(mark | (1 << city), city);
            if (answer > newAnswer) {
                answer = newAnswer; // Aktualizacja kosztu
                pathMatrix[mark][position] = city; // Zapisywanie poprzedniego miasta na ścieżce
            }
        }
    }
    return memoMatrix[mark][position] = answer;
}



