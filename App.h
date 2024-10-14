//
// Created by mateu on 14.10.2024.
//

#ifndef APP_H
#define APP_H
#include "MatrixModel.h"
#include "Menu.h"


class App {
public:
    void run();
    private:
    Menu menu;
    MatrixModel matrixModel;
};



#endif //APP_H
