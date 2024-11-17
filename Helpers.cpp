//
// Created by mateu on 14.10.2024.
//

#include "Helpers.h"

#include "algorithms/Little.h"
using namespace std;
#include <iostream>

void Helpers::displayArray(int *arr,int n) {
    cout << "[ ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << "]" << endl;
}

void Helpers::displayMatrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){
            if (matrix[i][j] == INF) {printf("%-4s","INF");}
            else
            {
                printf("%-4d",matrix[i][j]);
            }
        }
        printf("\n");
    }
}

int Helpers::countRoute(int **matrix, int *routeArr, int n) {
    int route = 0;
    int routeLen = n + 1;
    int curCity, nextCity;
    for (int i = 0; i < routeLen - 1; i++) {
        curCity = routeArr[i];
        nextCity = routeArr[i+1];
        route += matrix[curCity][nextCity];
    }
    return route;
}


void Helpers::displayRoute(int **matrix, int *route, int n) {
    int curCity, nextCity, lastCity;
    int routeLen = n + 1;
    for (int i = 0; i < routeLen-1; i++) {
        curCity = route[i];
        nextCity = route[i+1];
        printf("%d -(%d)-> ",curCity,matrix[curCity][nextCity]);
    }
    lastCity = route[routeLen-1];
    printf("%d\n", lastCity);
}