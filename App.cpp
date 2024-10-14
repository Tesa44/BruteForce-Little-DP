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
                matrixModel.displayMatrix();
                break;
            case '2':
                cout << "Generowanie macierzy ..." << endl;
                matrixModel.generateMatrix(menu.inputLen());
                matrixModel.displayMatrix();
                break;
            case '3':
                matrixModel.loadMatrixFromFile(menu.inputPath());
            case '4':
                //TODO consider this option
            default:
                break;
        }
        menu.exitConfirmMenu();
    }
}
