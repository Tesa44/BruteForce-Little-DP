//
// Created by mateu on 14.10.2024.
//

#ifndef APP_H
#define APP_H
#include "MatrixModel.h"
#include "Menu.h"
#include "Little.h"
#include "BruteForce.h"
#include "Helpers.h"
#include "LittleNew.h"


class App {
public:
    void run();
    private:
    Menu menu;
    MatrixModel model;
    BruteForce bruteForce;
    LittleNew little;
    Helpers helpers;
    void runAlgorithms();
};



#endif //APP_H
