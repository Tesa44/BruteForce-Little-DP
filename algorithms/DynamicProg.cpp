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
    //Tworzenie macierzy kosztów, pamięci (memo) i ścieżek
    createTSPMatrix(n);
    createMemoMatrix(pow(2,n), n);
    createPathMatrix(pow(2,n), n);
    size = n;   //Ustawienie rozmiaru problemu

    //Kopiowanie macierzy kosztów do wewnętrznej macierzy TSP
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            TSPmatrix[i][j] = matrix[i][j];
        }
    }

    //Wywołanie głównej funkcji TSP dla stanu początkowego
    //Zaczynamy od miasta 0 i stanu odwiedzin  = 1 (tylko miasto 0 jest odwiedzone)
    int result = TSP(1,0);

    //Odtworzenie optymalnej ścieżki na podstawie macierzy ścieżek (pathMatrix)
    int* finalPath = new int[size+1];
    finalPath[0] = 0; //Pierwsze miasto na ścieżce to zawsze 0
    int citiesVisited = 1;  //Początkowo odwiedzone tylko miasto 0
    int position = 0;   //Zaczynamy w mieście 0
    // Odwiedzamy n-1 pozostałych miast
    for (int i = 0; i < size - 1; i++)
    {
        //Znajdujemy następne miasto na podstawie macierzy ścieżek
        position = pathMatrix[citiesVisited][position];
        //Aktualizujemy stan odwiedzin, dodając nowe miasto
        citiesVisited |= (1 << position);
        //Dodajemy nowe miasto do końcowej ścieżki
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

int DynamicProg::TSP(int mark, int position)
{
    int completed_visit = (1 << size) - 1; //Wszystkie miasta odwiedzone, jest to stan końcowy
    //Jeśli wszystkie miasta zostały odwiedzone to zwróć koszt powrotu do miasta startowego
    if (mark == completed_visit) {
        return TSPmatrix[position][0];
    }
    //Jeżeli wynik dla danego mark i position jest już w memoMatrix, to zwróć go od razu
    if (memoMatrix[mark][position] != -1) {
        return memoMatrix[mark][position];
    }
    int answer = MAX;
    //Iterowanie po wszystkich miastach, które jeszcze nie zostały odwiedzone.
    for (int city = 0; city < size; city++) {
        //Jeśli miasto 'city' nie zostało odwiedzone to obliczamy koszt przejścia do miasta 'city' i dalszej podróży
        if ((mark & (1 << city)) == 0) {
            int newAnswer = TSPmatrix[position][city] + TSP(mark | (1 << city), city);
            //Jeśli znaleziono tańszą ścieżkę, aktualizujemy wynik
            if (answer > newAnswer) {
                answer = newAnswer; // Aktualizacja kosztu
                pathMatrix[mark][position] = city; // Zapamiętujemy, że z 'position' należy przejść do 'city'
            }
        }
    }
    //Zapisujemy wynik w pamięci (memo) i zwracamy
    return memoMatrix[mark][position] = answer;
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




