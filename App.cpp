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
                model.freeMatrix();
                model.generateMatrix(menu.inputLen());
                model.displayMatrix();
                runAlgorithms();
                break;
            case '3':
                model.freeMatrix();
                model.loadMatrixFromFile(menu.inputPath());
                cout << "Twoja macierz to: " << endl;
                model.displayMatrix();
                runAlgorithms();
            case '4':
                runTests();
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

void App::runTests()
{
    menu.algorithmsMenu();  //Wybierz algorytm do testowania
    numberOfTests = menu.inputNumberOfTests();
    auto begin = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    auto diff = duration_cast<chrono::nanoseconds>(end - begin);
    int numbersOfCities[7] = {4,6,8,10,12,14,15};
    double *avgResults = new double[7];   //Tablica do przechowywania śrenidch wyników z każdej ilości miast do testowania
    string name = "";
    srand(time(NULL));
    for (int i = 0; i <7; i++) {
        model.n = numbersOfCities[i];
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
                //TODO fix return value from dynamic programming algorithm
                //result = dynamicProg.algorithm(model.matrix, model.n);
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
    for (int i = 0; i < 7; i ++){
        cout << "Sredni czas algorytmu dla " << numbersOfCities[i] << " miast to " << avgResults[i] << " [ms]" << endl;
    }
    cout << endl;
}
