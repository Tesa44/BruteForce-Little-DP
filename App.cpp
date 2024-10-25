//
// Created by mateu on 14.10.2024.
//

#include "App.h"

void App::run() {
    while (menu.exitConfirmChoice != '2') {
        menu.mainMenu();
        switch (menu.mainChoice) {
            case '1':
                cout << "Twoja macierz to: " << endl;
                model.displayMatrix();
                runAlgorithms();
                break;
            case '2':
                cout << "Generowanie macierzy ..." << endl;
                model.generateMatrix(menu.inputLen());
                model.displayMatrix();
                runAlgorithms();
                break;
            case '3':
                model.loadMatrixFromFile(menu.inputPath());
                cout << "Twoja macierz to: " << endl;
                model.displayMatrix();
                runAlgorithms();
            case '4':
                //TODO consider this option
            default:
                break;
        }
        menu.exitConfirmMenu();
    }
}

void App::runAlgorithms() {
    menu.algorithmsMenu();
    int *result = new int[model.n + 1];
    int bruteShortestPath;
    int littleShortestPath;


    switch (menu.algorithmChoice) {
        case '1':
            result = bruteForce.algorithm(model.matrix, model.n);
            bruteForce.displayRoute(model.matrix, result, model.n);
            bruteShortestPath = bruteForce.countRoute(model.matrix, result, model.n);
            cout << "Shortest path: " << bruteShortestPath << endl;
            break;
        case '2':
            result = little.algorithm(model.matrix,model.n);
            bruteForce.displayRoute(model.matrix, result, model.n);
            littleShortestPath = bruteForce.countRoute(model.matrix, result, model.n);
            cout << "Shortest path: " << littleShortestPath << endl;
            break;
        default:
            break;
    }
}