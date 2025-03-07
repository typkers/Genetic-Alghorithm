#pragma once
#include "CIndividual.h"
#include <iostream>

class CBestIndividual
{
private:
    double mBestFitness;
    CIndividual mBestIndividual;

public:
    CBestIndividual();

    double getBestFitness() const;
    const CIndividual& getBestIndividual() const;
    void updateBest(const CIndividual& ourIndividual, double fitnessValue);

};
