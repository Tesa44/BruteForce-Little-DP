//
// Created by Mateusz on 25.10.2024.
//

#include "LittleNew.h"

#include "LittleNew.h"
#include <iostream>
#include <vector>
#include <queue>

// Funkcja do dynamicznego alokowania macierzy 2D
int** LittleNew::createMatrix(int size) {
    int** matrix = new int*[size];
    for (int i = 0; i < size; ++i) {
        matrix[i] = new int[size];
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = INF; // Inicjalizowanie INF, jeśli chcemy domyślnie
        }
    }
    return matrix;
}

// Funkcja do zwalniania pamięci dynamicznej macierzy 2D
void LittleNew::deleteMatrix(int** matrix, int size) {
    for (int i = 0; i < size; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Funkcja do kopiowania macierzy 2D
int** LittleNew::copyMatrix(int** matrix, int size) {
    int** newMatrix = createMatrix(size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            newMatrix[i][j] = matrix[i][j];
        }
    }
    return newMatrix;
}

// Funkcja zamieniająca wszystkie 0 na INF w macierzy kosztów
void LittleNew::replaceZeroesWithINF(int** matrix, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (matrix[i][j] == 0 && i != j) { // Nie zamieniamy 0 na przekątnej (czyli z wierzchołka do samego siebie)
                matrix[i][j] = INF;
            }
        }
    }
}

// Funkcja do redukcji macierzy kosztów
int LittleNew::reduceMatrix(int** matrix, int size) {
    int reductionCost = 0;

    // Redukcja wierszy
    for (int i = 0; i < size; ++i) {
        int minRow = INF;
        for (int j = 0; j < size; ++j) {
            if (matrix[i][j] < minRow) {
                minRow = matrix[i][j];
            }
        }
        if (minRow != INF && minRow != 0) {
            reductionCost += minRow;
            for (int j = 0; j < size; ++j) {
                if (matrix[i][j] != INF) {
                    matrix[i][j] -= minRow;
                }
            }
        }
    }

    // Redukcja kolumn
    for (int j = 0; j < size; ++j) {
        int minCol = INF;
        for (int i = 0; i < size; ++i) {
            if (matrix[i][j] < minCol) {
                minCol = matrix[i][j];
            }
        }
        if (minCol != INF && minCol != 0) {
            reductionCost += minCol;
            for (int i = 0; i < size; ++i) {
                if (matrix[i][j] != INF) {
                    matrix[i][j] -= minCol;
                }
            }
        }
    }

    return reductionCost;
}

// Tworzenie nowego węzła w drzewie decyzyjnym
LittleNew::Node LittleNew::createNode(int** parentMatrix, int level, int i, int j, int parentCost, std::vector<int> path, int size) {
    Node node;
    node.reducedMatrix = copyMatrix(parentMatrix, size);
    node.path = path;

    if (level != 0) {
        node.path.push_back(j);
    }

    for (int k = 0; k < size; k++) {
        node.reducedMatrix[i][k] = INF;
        node.reducedMatrix[k][j] = INF;
    }
    node.reducedMatrix[j][0] = INF;

    node.cost = parentCost + parentMatrix[i][j];
    node.cost += reduceMatrix(node.reducedMatrix, size);

    node.vertex = j;
    node.level = level;

    return node;
}

// Algorytm Little'a do rozwiązania problemu komiwojażera
int* LittleNew::algorithm(int **costMatrix, int size) {
    // Tworzymy kopię oryginalnej macierzy, aby jej nie modyfikować
    int** matrix = copyMatrix(costMatrix, size);

    // Zamieniamy wszystkie 0 na INF, jeśli są poza przekątną
    replaceZeroesWithINF(matrix, size);

    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    std::vector<int> initialPath = {0};

    Node root;
    root.reducedMatrix = copyMatrix(matrix, size);
    root.cost = reduceMatrix(root.reducedMatrix, size);
    root.vertex = 0;
    root.level = 0;
    root.path = initialPath;

    pq.push(root);

    int minCost = INF;
    Node bestNode;

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (current.level == size - 1) {
            current.path.push_back(0);
            int totalCost = 0;

            for (int k = 0; k < current.path.size() - 1; ++k) {
                totalCost += costMatrix[current.path[k]][current.path[k + 1]];
            }

            if (totalCost < minCost) {
                minCost = totalCost;
                bestNode = current;
            }
            continue;
        }

        for (int j = 0; j < size; j++) {
            if (current.reducedMatrix[current.vertex][j] != INF) {
                Node child = createNode(current.reducedMatrix, current.level + 1, current.vertex, j, current.cost, current.path, size);
                pq.push(child);
            }
        }
    }

    // Zwalniamy pamięć dla kopii macierzy
    deleteMatrix(matrix, size);

    int * bestPathArr = new int[size + 1];
    int i = 0;
//    std::cout << "Najkrótsza trasa: ";
    for (int v : bestNode.path) {
        //std::cout << v << " ";
        bestPathArr[i++] = v;
    }
//    std::cout << "\nMinimalny koszt: " << minCost << std::endl;

    return bestPathArr;
}
