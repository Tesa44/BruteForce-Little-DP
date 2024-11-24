//
// Created by Mateusz on 10.10.2024.
//

#ifndef PEA_PROJEKT_1_MATRIXMODEL_H
#define PEA_PROJEKT_1_MATRIXMODEL_H
#include <string>

#include "Config.h"

class Model {
private:
    void initMatrix();  //Utworzenie macierzy o rozmiarze n wypełnionej zerami
public:
    int **matrix;
    int n = 0; //Rozmiar macierzy
    void freeMatrix();
    void loadMatrixFromFile(std::string path);
    void generateMatrix(int matrixSize);

};


#endif //PEA_PROJEKT_1_MATRIXMODEL_H
