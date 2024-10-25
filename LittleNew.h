//
// Created by Mateusz on 25.10.2024.
//

#ifndef PEA_PROJEKT_1_LITTLENEW_H
#define PEA_PROJEKT_1_LITTLENEW_H


#include <vector>
#include <limits>
#include <queue>

const int INF = std::numeric_limits<int>::max();

class LittleNew {
public:
    // Algorytm Little'a do rozwiązania problemu komiwojażera
    int algorithm(int** costMatrix, int size);

private:
    struct Node {
        int** reducedMatrix;
        int cost;
        int vertex;
        int level;
        std::vector<int> path;

        bool operator>(const Node& other) const {
            return cost > other.cost;
        }
    };

    // Metody pomocnicze
    int** createMatrix(int size);
    void deleteMatrix(int** matrix, int size);
    int** copyMatrix(int** matrix, int size);
    void replaceZeroesWithINF(int** matrix, int size);
    int reduceMatrix(int** matrix, int size);
    Node createNode(int** parentMatrix, int level, int i, int j, int parentCost, std::vector<int> path, int size);
};

#endif //PEA_PROJEKT_1_LITTLENEW_H
