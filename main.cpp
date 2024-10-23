#include <iostream>

#include "App.h"
#include "MatrixModel.h"
#include "BruteForce.h"
#include "Helpers.h"
#include "Little.h"

using namespace std;
int main() {
    MatrixModel model;
    BruteForce bruteForce;
    Helpers helpers;
    App app;
    Little little;
    model.loadMatrixFromFile("C:\\Users\\Mateusz\\CLionProjects\\PEA-projekt-1\\little.txt");
    //model.displayMatrix();
    little.algorithm(model.matrix, model.n);
    //model.displayMatrix();
//     int *minRoute = new int[model.n + 1];
//     minRoute = bruteForce.algorithm(model.matrix, model.n);
//     helpers.displayArray(minRoute,model.n+1);
//     bruteForce.displayRoute(model.matrix,minRoute,model.n);
//     int shortestPath = bruteForce.countRoute(model.matrix,minRoute,model.n);
//     cout << "Shortest path: " << shortestPath << endl;
//    app.run();

    return 0;
}

//TODO finish little algorithm in Little class