#include <iostream>
#include "MatrixModel.h"
#include "BruteForce.h"

using namespace std;
int main() {
    MatrixModel model;
    BruteForce bruteForce;

    model.loadMatrixFromFile("C:\\Users\\Mateusz\\CLionProjects\\PEA-projekt-1\\small.txt");
    model.displayMatrix();
    int *minRoute = new int[model.n + 1];
    minRoute = bruteForce.algorithm(model.matrix, model.n);
    bruteForce.displayRoute(model.matrix,minRoute,model.n);
    //int shortestPath = bruteForce.countRoute(model.matrix,minRoute,model.n);
    //cout << "Shortest path: " << shortestPath << endl;

    return 0;
}
