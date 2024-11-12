//
// Created by Mateusz on 04.11.2024.
//

#ifndef PEA_PROJEKT_1_DYNAMICPROG_H
#define PEA_PROJEKT_1_DYNAMICPROG_H


class DynamicProg {
public:
    int* algorithm(int** matrix, int n);
    void printPath(int mark, int position);
private:
    int TSP(int mark, int position);
    int **TSPmatrix;
    int **memoMatrix;
    int **pathMatrix;
    int size;
    void createTSPMatrix(int n);
    void createMemoMatrix(int n, int m);
    void createPathMatrix(int n, int m);

};


#endif //PEA_PROJEKT_1_DYNAMICPROG_H
