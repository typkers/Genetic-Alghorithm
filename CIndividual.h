#pragma once
#include  <iostream>
#include "GroupingEvaluator.h"
#include "Point.h"
#include <utility>
#include <random>
#include <cfloat>

using namespace NGroupingChallenge;

class CIndividual
{
private:
    int mGenotypeLength;
    int mNumberOfGroups;
    vector<int> mGenotype;
    
public:
    static std::mt19937 generateRan() {
        std::random_device rd; 
        std::mt19937 gen(rd());
        return gen;
    }

    CIndividual();
    CIndividual(int genotypeLength, int numberOfGroups); 
    double evaluateFitness(CGroupingEvaluator& evaluator) const;
    pair<CIndividual, CIndividual> performCrossover(double crossProb, const CIndividual& otherIndividual) const;
    void performMutation(double mutProb); 
    const vector<int>& getGenotype() const ;

};
