//
// Created by mateu on 09.10.2024.
//

#ifndef MENU_H
#define MENU_H
#include <iostream>
using namespace std;

class Menu {
public:
    char mainChoice;
    char algorithmChoice;
    char displayChoice;
    char exitConfirmChoice;
    char speedTestChoice;
    void mainMenu();
    void algorithmsMenu();
    void speedTestMenu();
    int inputLen();
    int inputStart(int v);
    int inputNumberOfTests();
    int n;
    bool checkChoices(char choice, char choiceQuantity);
    string inputPath();
    void exitConfirmMenu();

};


#endif //GRAPHAPP_MENU_H
