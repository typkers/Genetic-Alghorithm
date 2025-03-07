#include "CBestIndividual.h"

CBestIndividual::CBestIndividual() : mBestFitness(DBL_MAX), mBestIndividual(CIndividual()) {}

double CBestIndividual::getBestFitness() const { 
    return mBestFitness;
}

const CIndividual& CBestIndividual::getBestIndividual() const { 
    return mBestIndividual;
}

void CBestIndividual::updateBest(const CIndividual& ourIndividual, double fitnessValue) {
    if (fitnessValue < mBestFitness) {
        mBestFitness = fitnessValue;
        mBestIndividual = ourIndividual;
    }
}