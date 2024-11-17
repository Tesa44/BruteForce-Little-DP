//
// Created by Mateusz on 12.11.2024.
//

#ifndef CONFIG_H
#define CONFIG_H

class Config
{
    public:
        int maxGeneratedPath = 30;
        int minGeneratedPath = 1;
        int numberOfCities[7] = {4,6,8,10,12,13,14};
        int arrLen = 7;
};

#endif //CONFIG_H
