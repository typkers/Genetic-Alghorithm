#pragma once
#include  <iostream>
#include "CIndividual.h"
#include "GroupingEvaluator.h"
#include "CBestIndividual.h"
#include <random>
#include <utility>
#include <chrono>

using namespace NGroupingChallenge;

class CGeneticAlgorithm
{
private:
    // directly reffereing to the same object, ensures the GA instance always has a valid CGroupingEvaluator
    CGroupingEvaluator& mEvaluator;
    int mPopSize;
    int mGenotypeLength;
    int mNumberOfGroups;
    double mCrossProb;
    double mMutProb;
    std::vector<CIndividual> mPopulation;
    CBestIndividual mBest;

    void createInitialPopulation();
    const CIndividual& findParent();
    void executeSingleIteration();
    
public:
    CGeneticAlgorithm(CGroupingEvaluator& evaluator, double crossProb, double mutProb, int popSize, int genotypeLength, int numberOfGroups);

    void executeAllIterations(std::chrono::seconds timeLimit);
    const CBestIndividual& getBest() const; 
};