//
// Created by Mateusz on 25.10.2024.
//

#include "Little.h"
#include "../Config.h"
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>


// Funkcja do dynamicznego alokowania macierzy 2D
int** Little::createMatrix(int size) {
    int** matrix = new int*[size];
    for (int i = 0; i < size; ++i) {
        matrix[i] = new int[size];
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = INF;
        }
    }
    return matrix;
}

// Funkcja do zwalniania pamięci dynamicznej macierzy 2D
void Little::deleteMatrix(int** matrix, int size) {
    for (int i = 0; i < size; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Funkcja do kopiowania macierzy 2D
int** Little::copyMatrix(int** matrix, int size) {
    int** newMatrix = createMatrix(size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            newMatrix[i][j] = matrix[i][j];
        }
    }
    return newMatrix;
}

// Funkcja zamieniająca wszystkie 0 na INF w macierzy pierwotnej
void Little::replaceZeroesWithINF(int** matrix, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i == j) {
                matrix[i][j] = INF;
            }
        }
    }
}

// Funkcja do redukcji macierzy kosztów
int Little::reduceMatrix(int** matrix, int size) {
    int reductionCost = 0;

    // Redukcja wierszy
    for (int i = 0; i < size; ++i) {
        int minRow = INF;
        //Szuakmy najmniejszego elementu w każdym wierszu
        for (int j = 0; j < size; ++j) {
            if (matrix[i][j] < minRow) {
                minRow = matrix[i][j];
            }
        }
        if (minRow != INF && minRow != 0) {
            //Dodajemy go do kosztu redukcji i odejmujemy od wszystkich elementów w danym wierszu
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
        //Szukamy najmniejszego elementu w każdej kolumnie
        for (int i = 0; i < size; ++i) {
            if (matrix[i][j] < minCol) {
                minCol = matrix[i][j];
            }
        }
        if (minCol != INF && minCol != 0) {
            //Dodajemy go do kosztu redukcji i odejmujemy od wszystkich elementów w danej kolumnie
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

// Tworzenie nowego węzła w drzewie decyzyjnym.
Little::Node Little::createNode(int** parentMatrix, int level, int i, int j, int parentCost, std::vector<int> path, int size) {
    Node node;
    node.reducedMatrix = copyMatrix(parentMatrix, size);
    node.path = path;

    //Dodajemy wierzchołek (miasto), do którego właśnie przeszliśmy na koniec naszej całej ścieżki
    if (level != 0) {
        node.path.push_back(j);
    }
    //usuwamy wybrany wiersz i oraz kolumne j
    for (int k = 0; k < size; k++) {
        node.reducedMatrix[i][k] = INF;
        node.reducedMatrix[k][j] = INF;
    }
    //Blokujemy drogę powrotną z węzła do samego siebie
    node.reducedMatrix[j][0] = INF;

    //Redukujemy nową macierz
    node.cost = parentCost + parentMatrix[i][j];
    node.cost += reduceMatrix(node.reducedMatrix, size);    //Całkowity zaktualizowany koszt ścieżki

    node.vertex = j;    //Docelowy wierzchołek j, do którego właśnie przechodzimy
    node.level = level;     //Poziom w drzewie

    return node;
}

// Algorytm Little'a do rozwiązania problemu komiwojażera
int* Little::algorithm(int **costMatrix, int size) {
    // Tworzymy kopię oryginalnej macierzy, aby jej nie modyfikować
    int** matrix = copyMatrix(costMatrix, size);

    // Zamieniamy wszystkie 0 na INF
    replaceZeroesWithINF(matrix, size);

    //Tworzenie kolejki priorytetowej do zarządzania węzłami
    //greater<Node> - funkcja porównawcza, która mówi kolejce, aby sortowała elementy rosnąco na podstawie operatora porównania
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    std::vector<int> initialPath = {0};     //Zaczynamy od węzła (miasta) 0

    //Sprawdzanie stopnia symetrii macierzy kosztów
    double symmetry = calculateSymmetry(costMatrix, size);
    bool useDuplicateRemoval = false;
    if (symmetry >= SYMMETRY_THRESHOLD) {
        useDuplicateRemoval = true;
        std::cout << "Stopien symetrii macierzy: " << symmetry * 100 << "%" << std::endl;
        std::cout << "Mozliwy wynik moze nie byc optymalnym rozwiazaniem! " << std::endl;
    }

    //Tworzenie root'a grafu i pierwsza redukcja macierzy
    Node root;
    root.reducedMatrix = copyMatrix(matrix, size);
    root.cost = reduceMatrix(root.reducedMatrix, size);
    root.vertex = 0;
    root.level = 0;
    root.path = initialPath;

    //Umieszaczmy węzęł początkowy w kolejce
    pq.push(root);

    int minCost = INF;
    std::unordered_map<int, int> costPerLevel; // Mapa: poziom -> minimalny koszt
    Node bestNode;

    //Przeszukiwanie drzewa
    while (!pq.empty()) {
        //Pobieramy wierzchołek z kolejki
        Node current = pq.top();
        pq.pop();

        //Jeżeli osiągnęliśmy poziom N-1, to znaczy, że mamy pełną ścieżkę
        if (current.level == size - 1) {
            current.path.push_back(0);  //Dodajemy powrót
            int totalCost = 0;
            //Liczymy jaką długość do tej pory przeszliśmy
            for (int k = 0; k < current.path.size() - 1; ++k) {
                totalCost += costMatrix[current.path[k]][current.path[k + 1]];
            }
            //Jeżeli ta długość jest najmniejsza to mamy szansę na otrzymanie najkrótszej ścieżki
            if (totalCost < minCost) {
                minCost = totalCost;
                bestNode = current;
            }
        }

        // Tworzenie poddrzew dla każdego możliwego wierzchołka
        for (int j = 0; j < size; j++) {
            if (current.reducedMatrix[current.vertex][j] != INF) {
                Node child = createNode(current.reducedMatrix, current.level + 1, current.vertex, j, current.cost, current.path, size);
                // Sprawdzamy, czy istnieje już węzeł o takim samym lub niższym koszcie na tym poziomie
                if (useDuplicateRemoval) {
                    if (costPerLevel.find(child.level) == costPerLevel.end() || child.cost < costPerLevel[child.level]) {
                        costPerLevel[child.level] = child.cost; // Aktualizacja mapy
                        pq.push(child);
                    }
                }
                else if (child.cost < minCost) {
                    pq.push(child);
                }
            }
        }
    }

    // Zwalniamy pamięć dla kopii macierzy
    deleteMatrix(matrix, size);

    int * bestPathArr = new int[size + 1];
    int i = 0;
    // std::cout << "Najkrótsza trasa: ";
    for (int v : bestNode.path) {
        // std::cout << v << " ";
        bestPathArr[i++] = v;
    }
    // std::cout << "\nMinimalny koszt: " << minCost << std::endl;

    return bestPathArr;
}

double Little::calculateSymmetry(int** matrix, int size) {
    int totalElements = 0, symmetricElements = 0;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i != j) { // Ignorujemy przekątną
                totalElements++;
                if (matrix[i][j] == matrix[j][i]) {
                    symmetricElements++;
                }
            }
        }
    }

    return static_cast<double>(symmetricElements) / totalElements;
}

