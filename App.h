//
// Created by mateu on 14.10.2024.
//

#ifndef APP_H
#define APP_H
#include "Model.h"
#include "Menu.h"
#include "algorithms/BruteForce.h"
#include "Helpers.h"
#include "algorithms/DynamicProg.h"
#include "algorithms/LittleNew.h"


class App {
    public:
        void run();

    private:
        Menu menu;
        Model model;
        BruteForce bruteForce;
        LittleNew little;
        DynamicProg dynamicProg;
        Helpers helpers;
        Config config;

        double durationTime = 0;
        int numberOfTests = 0;
        void runAlgorithms();
        void runTests();
};



#endif //APP_H
