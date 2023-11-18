#pragma once

#include <random>

struct RNG
{
    std::mt19937 generator;

    RNG(int seed)
        : generator(seed)
    {}

    int randInt(int to)
    {
        return randInt(0, to);
    }

    int randInt(int from, int to)
    {
        std::uniform_int_distribution<int> distr(from, to - 1);
        return distr(generator);
    }

    double randReal(double from, double to)
    {
        std::uniform_real_distribution<double> distr(from, to);
        return distr(generator);
    }
};
