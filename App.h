//
// Created by mateu on 14.10.2024.
//

#ifndef APP_H
#define APP_H
#include "MatrixModel.h"
#include "Menu.h"
#include "algorithms/Little.h"
#include "algorithms/BruteForce.h"
#include "Helpers.h"
#include "algorithms/DynamicProg.h"
#include "algorithms/LittleNew.h"


class App {
public:
    void run();
    private:
    Menu menu;
    MatrixModel model;
    BruteForce bruteForce;
    LittleNew little;
    DynamicProg dynamicProg;
    Helpers helpers;

    double durationTime = 0;
    int numberOfTests = 0;
    void runAlgorithms();
    void runTests();
};



#endif //APP_H
