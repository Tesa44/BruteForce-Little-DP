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
    char exitConfirmChoice;
    void mainMenu();
    void algorithmsMenu();
    int inputLen();
    int n;
    bool checkChoices(char choice, char choiceQuantity);
    string inputPath();
    int inputNumberOfTests();
    void exitConfirmMenu();

};


#endif //GRAPHAPP_MENU_H
