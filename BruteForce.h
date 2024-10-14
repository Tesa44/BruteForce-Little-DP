//
// Created by Mateusz on 10.10.2024.
//

#ifndef PEA_PROJEKT_1_BRUTEFORCE_H
#define PEA_PROJEKT_1_BRUTEFORCE_H


class BruteForce {
public:
        int* algorithm(int **matrix, int n);
        void displayRoute(int **matrix,int *route, int n);
        int countRoute(int **matrix, int *routeArr, int n);
private:
        bool nextPermutation(int *elements, int n);

};


#endif //PEA_PROJEKT_1_BRUTEFORCE_H
