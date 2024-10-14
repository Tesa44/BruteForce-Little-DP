//
// Created by mateu on 14.10.2024.
//

#include "Helpers.h"
using namespace std;
#include <iostream>

void Helpers::displayArray(int *arr,int n) {
    cout << "[ ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << "]" << endl;
}
