//
// Created by mateu on 14.10.2024.
//

#include "App.h"
#include <chrono>

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
    //Zmienne do liczenia czasu
    auto begin = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();;
    auto diff = duration_cast<std::chrono::nanoseconds>(begin - end); // Różnica czasu między begin i end
    double durationTime;
    //Zmienne do zapisywania wynikow
    int *result = new int[model.n + 1];
    int bruteShortestPath;
    int littleShortestPath;
    int dynamicShortestPath;

    switch (menu.algorithmChoice) {
        case '1':
            begin = std::chrono::steady_clock::now();
            result = bruteForce.algorithm(model.matrix, model.n);
            end = std::chrono::steady_clock::now();
            diff = duration_cast<std::chrono::nanoseconds>(end - begin);
            durationTime = (double)diff.count() / 1000000;
            bruteForce.displayRoute(model.matrix, result, model.n);
            bruteShortestPath = bruteForce.countRoute(model.matrix, result, model.n);
            cout << "Najkrotsza sciezka: " << bruteShortestPath << endl;
            cout << "Czas trwania: " << durationTime << "[ms]" << endl;
            break;
        case '2':
            begin = std::chrono::steady_clock::now();
            result = little.algorithm(model.matrix,model.n);
            end = std::chrono::steady_clock::now();
            diff = duration_cast<std::chrono::nanoseconds>(end - begin);
            durationTime = (double)diff.count() / 1000000;
            bruteForce.displayRoute(model.matrix, result, model.n);
            littleShortestPath = bruteForce.countRoute(model.matrix, result, model.n);
            cout << "Najkrotsza sciezka: " << littleShortestPath << endl;
            cout << "Czas trwania: " << durationTime << "[ms]" << endl;
            break;
        case '3':
            begin = std::chrono::steady_clock::now();
            result = dynamicProg.algorithmPath(model.matrix, model.n);
            end = std::chrono::steady_clock::now();
            diff = duration_cast<std::chrono::nanoseconds>(end - begin);
            durationTime = (double)diff.count() / 1000000;
            bruteForce.displayRoute(model.matrix, result, model.n);
            dynamicShortestPath = bruteForce.countRoute(model.matrix, result, model.n);
            cout << "Najkrotsza sciezka: " << dynamicShortestPath << endl;
            cout << "Czas trwania: " << durationTime << "[ms]" << endl;
            break;
        default:
            break;
    }
    delete[] result;
}