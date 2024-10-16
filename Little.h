//
// Created by Mateusz on 16.10.2024.
//

#ifndef PEA_PROJEKT_1_LITTLE_H
#define PEA_PROJEKT_1_LITTLE_H


class Little {
public:
    void algorithm(int** matrix, int n);
    int findMin(int* arr, int n);
private:
    int reduceMatrix(int** matrix, int n);
    struct path {
        int row;
        int column;
        int cost;  //Koszt optymistycznego wyłączenia
    };
    path arrPathEnd = {-1,-1,-1};
    path* getMinPaths(int** matrix,int n, int mpSize);
    int countZeros(int **matrix, int n);
    bool pathIsEmpty(path* arrPath, int index);
    void displayArrPath(path* arrPath);



};


#endif //PEA_PROJEKT_1_LITTLE_H
