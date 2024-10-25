//
// Created by mateu on 09.10.2024.
//

#include "Menu.h"
#include <iostream>
using namespace std;


void Menu::mainMenu() {
    while (true) {
        cout << "Witaj w menu programu" << endl;
        cout << "1. Uzyj ostatnio utworzona macierz" << endl;
        cout << "2. Wygeneruj macierz losowo" << endl;
        cout << "3. Wczytaj macierz z pliku o zadanej nazwie" << endl;
        cout << "4. Tryb do testowania szybkosci algorytmow" << endl;
        cin >> mainChoice;
        if (checkChoices(mainChoice, '4'))
            return;
    }
}
void Menu::speedTestMenu() {
    while (true) {
        cout << "Witaj w trybie testowania szybkosci algorytmow" << endl;
        cout << "Wybierz reprezentacje grafu do testowania" << endl;
        cout << "1. Macierz incydencji" << endl;
        cout << "2. Lista sasiedztwa" << endl;
        cin >> speedTestChoice;
        if (checkChoices(speedTestChoice, '2'))
            return;
    }
}

string Menu::inputPath() {
    string path;
    cout << "Podaj sciezke do pliku tekstowego " << endl;
    cin >> path;
    return path;
}

int Menu::inputLen() {
    string input;
    bool guard;
    while (true) {
        guard = true;
        cout << "Podaj rozmiar macierzy kwadratowej" << endl;
        cin >> input;
        for (int i = 0; i < input.length(); i++) {
            if (isdigit(input[i] == false))
                guard = false;
        }
        if (guard) {
            int n = stoi(input);
            return n;
        }
        cout << "To nie jest liczba" << endl;
    }
}


//Metoda służy do sprawdzania czy wybór wpisany przez użytkownika jest zgodny z jakimkolwiek wyborem
//char choice - znak podany przez użytkownika określający wybór
//char choiceQuantity - ile posiadamy wyborów w menu
bool Menu::checkChoices(char choice, char choiceQuantity) {
    if (choice >= '1' && choice <= choiceQuantity)
        return true;
    cout << "Niepoprawny wybor!" << endl;
    return false;
}


void Menu::exitConfirmMenu() {
    while (true) {
        cout << "Czy chcesz wyjsc z programu?" << endl;
        cout << "1. Wroc do algorytmow" << endl;
        cout << "2. Zamknij program" << endl;
        cin >> exitConfirmChoice;
        if (checkChoices(exitConfirmChoice, '2'))
            return;
    }
}

void Menu::algorithmsMenu() {
    while (true) {
        cout << "Wybierz algorytm dla ostatnio utworzonej lub wczytanej macierzy" << endl;
        cout << "1. Algorytm Brute Force" << endl;
        cout << "2. Algorytm Little'a" << endl;
        cout << "3. Algorytm Programowanie Dynamiczne" << endl;
        cin >> algorithmChoice;
        if (checkChoices(algorithmChoice, '3'))
            return;
    }
}

int Menu::inputStart(int v) {
    string input;
    bool guard;
    while (true) {
        guard = true;
        cout << "Podaj wierzcholek startowy" << endl;
        cin >> input;
        for (int i = 0; i < input.length(); i++) {
            if (isdigit(input[i] == false))
                guard = false;
        }
        if (guard) {
            int n = stoi(input);
            if (n >= v) return 0;
            return n;
        }
        cout << "To nie jest liczba" << endl;
    }
}

int Menu::inputNumberOfTests() {
    string input;
    bool guard;
    while (true) {
        guard = true;
        cout << "Podaj liczbe testow, z ktorych zostanie obliczony sredni czas wybranego sortowania" << endl;
        cin >> input;
        for (int i = 0; i < input.length(); i++) {
            if (isdigit(input[i] == false))     //Sprawdzanie czy każdy podany znak jest liczbą
                guard = false;
        }
        if (guard) {
            int numberOfTests = stoi(input);    //Konwertowanie string na int
            return numberOfTests;
        }
        cout << "To nie jest liczba" << endl;
    }
}
