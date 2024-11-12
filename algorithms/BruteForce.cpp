//
// Created by Mateusz on 10.10.2024.
//

#include <algorithm>
#include <iostream>
#include <string>
#include <typeinfo>
#include "BruteForce.h"

using namespace std;

bool BruteForce::nextPermutation(int *elements, int n) {
    //Szukamy największego indeksu, dla którego elementy są ustawione rosnąco
    //Szukamy od prawej strony, jeśli znajdziemy taki indeks, to możemy jeszcze otrzymać kolejną permutację
    int i = n - 2;
    while (i >= 0 && elements[i] >= elements[i+1]) i--;

    //Jeśli nie ma takiego indeksu, to znaczy, że nie ma już większej permutacji i wszystkie elementy są ustawione malejąco
    if (i < 0) return false;

    //Szukamy największego indeksu od prawej strony, który wskaże nam największy element w nieposortowanej częsci tabeli
    //Dzięki temu zamienimy go z elements[i] (który jest ostatnim elementem w posortowanej części) i powstanie nam minimalnie większa permutacja
    int j = n -1;
    while (elements[j] <= elements[i]) j--;

    //Zamiana elementów na pozycji i oraz j
    swap(elements[i],elements[j]);

    //Odwracamy elementy od elements[i + 1] do końca
    //Sprawi to, że część tablicy po i stanie się najmniejszą możliwą permutacją i cała tablica będzie najmniejszą kolejną permutacją
    int left = i + 1;
    int right = n - 1;
    while (left < right) {
        swap(elements[left],elements[right]);
        left++;
        right--;
    }
    //Zwracamy true, bo znaleźliśmy kolejną permutację
    return true;
}

int* BruteForce::algorithm(int **matrix, int n) {
    int minPath;
    int curCity;
    int nextCity;
    int startCity;
    int *minRoute = new int[n+1];
    int *cities = new int[n-1];

    for (int i = 1; i < n; i++) {
        cities[i-1] = i;
    }
    //Pierwsza permutacja
    int curPath = 0;
    for (int i = 0; i < n; i ++) {
        if (i < n - 1) {
            curPath += matrix[i][i+1];
        }
        else {
            //Powrót do miejsca startowego
            curPath += matrix[i][0];
        }
    }
    minPath = curPath;
    //Generowanie kolejnych permutacji
    while (nextPermutation(cities, n-1)) {
        int *curRoute = new int[n + 1]; //Tablica przechowująca bieżącą drogę
        curPath  = matrix[0][cities[0]];    //Droga z miasta początkowego ( 0 ) do pierwszego miasta z permutacji
        curRoute[0] = 0;
        for (int i = 0; i < n - 1 - 1; i ++) {
            curCity = cities[i];
            nextCity = cities[i + 1];
            curRoute[i+1] = curCity;
            curPath += matrix[curCity][nextCity];
        }
        //Dopisanie ostatniego miasta
        curRoute[n-1] = nextCity;

        //Droga z ostatniego miasta do miasta startowego ( 0 )
        startCity = 0;
        curCity = cities[n - 1 - 1];
        curPath += matrix[curCity][startCity];
        curRoute[n] = startCity;
        //Sprawdzanie, czy bieżąca droga może być drogą najkrótszą i ewentualne jej zapamiętanie
        if (curPath < minPath) {
            minPath = curPath;
            memcpy(minRoute, curRoute, (n+1) * sizeof(int));
        }
        delete[] curRoute;
    }
    return minRoute;
}


