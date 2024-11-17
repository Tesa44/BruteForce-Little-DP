//
// Created by mateu on 14.10.2024.
//

#include "App.h"
#include <chrono>

void App::run() {
    bool isMatrix = false;
    while (menu.exitConfirmChoice != '2') {
        menu.mainMenu();
        switch (menu.mainChoice) {
            case '1':
                if (isMatrix)
                {
                    cout << "Twoja macierz to: " << endl;
                    helpers.displayMatrix(model.matrix,model.n);
                    runAlgorithms();
                } else {cout << "Nie masz zadnej zapisanej macierzy!" << endl;}
                break;
            case '2':
                if (isMatrix) model.freeMatrix();
                cout << "Generowanie macierzy ..." << endl;
                isMatrix = true;
                model.generateMatrix(menu.inputLen());
                helpers.displayMatrix(model.matrix,model.n);
                runAlgorithms();
                break;
            case '3':
                if (isMatrix) model.freeMatrix();
                model.loadMatrixFromFile(menu.inputPath());
                cout << "Twoja macierz to: " << endl;
                helpers.displayMatrix(model.matrix,model.n);
                runAlgorithms();
                break;
            case '4':
                runTests();
                break;
            default:
                cout << "Niepoprawny wybór" << endl;
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
    auto diff = duration_cast<std::chrono::nanoseconds>(end - begin); // Różnica czasu między begin i end
    double durationTime;
    //Zmienne do zapisywania wynikow
    int *result = new int[model.n + 1];
    int bruteShortestPath = 0;
    int littleShortestPath = 0;
    int dynamicShortestPath = 0;

    switch (menu.algorithmChoice) {
        case '1':
            begin = std::chrono::steady_clock::now();
            result = bruteForce.algorithm(model.matrix, model.n);
            end = std::chrono::steady_clock::now();
            diff = duration_cast<std::chrono::nanoseconds>(end - begin);
            durationTime = (double)diff.count() / 1000000;
            helpers.displayRoute(model.matrix, result, model.n);
            bruteShortestPath = helpers.countRoute(model.matrix, result, model.n);
            cout << "Najkrotsza sciezka: " << bruteShortestPath << endl;
            cout << "Czas trwania: " << durationTime << "[ms]" << endl;
            break;
        case '2':
            begin = std::chrono::steady_clock::now();
            result = little.algorithm(model.matrix,model.n);
            end = std::chrono::steady_clock::now();
            diff = duration_cast<std::chrono::nanoseconds>(end - begin);
            durationTime = (double)diff.count() / 1000000;
            helpers.displayRoute(model.matrix, result, model.n);
            littleShortestPath = helpers.countRoute(model.matrix, result, model.n);
            cout << "Najkrotsza sciezka: " << littleShortestPath << endl;
            cout << "Czas trwania: " << durationTime << "[ms]" << endl;
            break;
        case '3':
            begin = std::chrono::steady_clock::now();
            result = dynamicProg.algorithm(model.matrix, model.n);
            end = std::chrono::steady_clock::now();
            diff = duration_cast<std::chrono::nanoseconds>(end - begin);
            durationTime = (double)diff.count() / 1000000;
            helpers.displayRoute(model.matrix, result, model.n);
            dynamicShortestPath = helpers.countRoute(model.matrix, result, model.n);
            cout << "Najkrotsza sciezka: " << dynamicShortestPath << endl;
            cout << "Czas trwania: " << durationTime << "[ms]" << endl;
            break;
        default:
            break;
    }
    delete[] result;
}

void App::runTests()
{
    menu.algorithmsMenu();  //Wybierz algorytm do testowania
    numberOfTests = menu.inputNumberOfTests();
    auto begin = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    auto diff = duration_cast<chrono::nanoseconds>(end - begin);
    double *avgResults = new double[config.arrLen];   //Tablica do przechowywania śrenidch wyników z każdej ilości miast do testowania
    string name = "";
    srand(time(NULL));
    for (int i = 0; i <config.arrLen; i++) {
        model.n = config.numberOfCities[i];
        double totalDurTime = 0;
        double avgDurTime = 0;
        int* result = new int[model.n + 1];
        for (int j = 0; j < numberOfTests; j++)
        {
            model.generateMatrix(model.n);

            switch (menu.algorithmChoice)
            {
            case '1':
                name = "Brute Force";
                begin = std::chrono::steady_clock::now();
                result = bruteForce.algorithm(model.matrix, model.n);
                end = std::chrono::steady_clock::now();
                diff = duration_cast<std::chrono::nanoseconds>(end - begin);
                totalDurTime += (double)diff.count() / 1000000;
                break;

            case '2':
                name = "Little'a";
                begin = std::chrono::steady_clock::now();
                result = little.algorithm(model.matrix, model.n);
                end = std::chrono::steady_clock::now();
                diff = duration_cast<std::chrono::nanoseconds>(end - begin);
                totalDurTime += (double)diff.count() / 1000000;
                    break;
            case '3':
                name = "Dynamic Programming";
                begin = std::chrono::steady_clock::now();
                result = dynamicProg.algorithm(model.matrix, model.n);
                end = std::chrono::steady_clock::now();
                diff = duration_cast<std::chrono::nanoseconds>(end - begin);
                totalDurTime += (double)diff.count() / 1000000;
                break;
            };

        cout << "Test" << j << "wykonany ";
        cout << " w czasie  " << (double)diff.count() / 1000000 << "[ms]" << endl;    //Informacja o czasie algorytmu dla danego testu
        model.freeMatrix();   //Zwolnij pamięć dynamicznej macierzy
            delete[] result; //Zwolnij pamięć wyniku algorytmu
    }
    avgDurTime = totalDurTime / numberOfTests;  //Obliczanie średniej z czasów algorytmu wszytkich testow dla danej ilości miast
    cout << "Ilosc miast: " << model.n << endl;
    cout <<  "Sredni czas algorytmu " << name <<" to: " <<avgDurTime << " [ms]" << endl << endl;
    avgResults[i] = avgDurTime;
    }
    cout << "------- Podsumowanie -------" << endl;
    for (int i = 0; i < config.arrLen; i ++){
        cout << "Sredni czas algorytmu dla " << config.numberOfCities[i] << " miast to " << avgResults[i] << " [ms]" << endl;
    }
    cout << endl;
}
