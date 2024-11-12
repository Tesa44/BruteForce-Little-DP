//
// Created by mateu on 14.10.2024.
//

#ifndef HELPERS_H
#define HELPERS_H



class Helpers {
public:
    void displayArray(int *arr, int n);
    void displayMatrix(int **matrix, int n);
    void displayRoute(int **matrix,int *route, int n);
    int countRoute(int **matrix, int *routeArr, int n);
};



#endif //HELPERS_H
