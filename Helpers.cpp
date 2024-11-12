//
// Created by mateu on 14.10.2024.
//

#include "Helpers.h"
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
            printf("%-4d",matrix[i][j]);
        }
        printf("\n");
    }
}

int Helpers::countRoute(int **matrix, int *routeArr, int n) {
    int route = 0;
    int routeLen = n + 1;
    int curCity, nextCity,lastCity,firstCity;
    for (int i = 0; i < routeLen - 1; i++) {
        curCity = routeArr[i];
        nextCity = routeArr[i+1];
        route += matrix[curCity][nextCity];
    }
    //Droga z ostatniego do pierwszego miasta
    lastCity = routeArr[routeLen-1];
    firstCity = routeArr[0];
    route += matrix[lastCity][firstCity];
    return route;

}


void Helpers::displayRoute(int **matrix, int *route, int n) {
    int curCity, nextCity, lastCity;
    int routeLen = n + 1;
    //cout << "routeLen: " << routeLen << endl;
    for (int i = 0; i < routeLen-1; i++) {
        curCity = route[i];
        nextCity = route[i+1];
        //cout << curCity << "   " << nextCity << endl;
        printf("%d -(%d)-> ",curCity,matrix[curCity][nextCity]);
    }
    lastCity = route[routeLen-1];
    printf("%d\n", lastCity);
}