//
// Created by Mateusz on 16.10.2024.
//

#ifndef PEA_PROJEKT_1_LITTLE_H
#define PEA_PROJEKT_1_LITTLE_H


class Little {
public:
    struct path {
        int row;
        int column;
        int cost;  //Koszt optymistycznego wyłączenia
    };
    path* algorithm(int** matrix, int n);
    void displayArrPath(path* arrPath);
    int* convertPathToArr(path* arrPath, int n);
private:
    int findMin(int* arr, int n);
    int** createMatrix(int n);
    int reduceMatrix(int** matrix, int n);

    int** deleteRowAndCol(int **matrix, int n, int rowToDelete, int colToDelete);
    path arrPathEnd = {-1,-1,-1};
    path* getMinPaths(int** matrix,int n, int mpSize);
    path findMaxCost(path* arrPath);
    int countZeros(int **matrix, int n);
    bool pathIsEmpty(path* arrPath, int index);
};


#endif //PEA_PROJEKT_1_LITTLE_H
