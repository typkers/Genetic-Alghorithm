#include "GaussianGroupingEvaluatorFactory.h"
#include "GroupingEvaluator.h"
#include "Optimizer.h"
#include "CIndividual.h"
#include "CGeneticAlgorithm.h"
using namespace NGroupingChallenge;

int main()
{
    const int popSize = 30; 
    const int numberOfGroups = 6;
    const int genotypeLength = 15;
    const double crossProb = 0.9;
    const double mutProb = 0.95;

    CGaussianGroupingEvaluatorFactory c_evaluator_factory(numberOfGroups, genotypeLength);

    c_evaluator_factory
        .cAddDimension(-100, 100, 1.0, 1.0)
        .cAddDimension(-100, 100, 1.0, 1.0)
        .cAddDimension(-100, 100, 1.0, 1.0)
        .cAddDimension(-100, 100, 1.0, 1.0)
        .cAddDimension(-100, 100, 1.0, 1.0)
        .cAddDimension(-100, 100, 1.0, 1.0)
        .cAddDimension(-100, 100, 1.0, 1.0)
        .cAddDimension(-100, 100, 1.0, 1.0)
        .cAddDimension(-100, 100, 1.0, 1.0)
        .cAddDimension(-100, 100, 1.0, 1.0);

    CGroupingEvaluator* pc_evaluator = c_evaluator_factory.pcCreateEvaluator(0);

    CGeneticAlgorithm geneticAlgorithm(*pc_evaluator, crossProb, mutProb, popSize, genotypeLength, numberOfGroups);

    std::chrono::seconds timeLimit(10);

    geneticAlgorithm.executeAllIterations(timeLimit);

    const CBestIndividual& bestSolution = geneticAlgorithm.getBest();
    const CIndividual& bestIndividual = bestSolution.getBestIndividual();

    for (int gene : bestIndividual.getGenotype()) {
        std::cout << gene;
    }
    std::cout << std::endl;

    std::cout << bestSolution.getBestFitness() << std::endl;

    delete pc_evaluator;

    return 0;
}