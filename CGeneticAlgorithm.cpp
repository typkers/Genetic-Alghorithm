#include "CGeneticAlgorithm.h"
#include <algorithm>
using namespace NGroupingChallenge;

CGeneticAlgorithm::CGeneticAlgorithm(CGroupingEvaluator& evaluator, double crossProb, double mutProb, int popSize, int genotypeLength, int numberOfGroups)
    : mEvaluator(evaluator), mCrossProb(crossProb), mMutProb(mutProb), mPopSize(popSize), mGenotypeLength(genotypeLength), mNumberOfGroups(numberOfGroups){}

void CGeneticAlgorithm::createInitialPopulation() {
    mPopulation.clear();
    mPopulation.reserve(mPopSize);
    double currentFitness;
    for (int i = 0; i < mPopSize; i++) {
        mPopulation.push_back(CIndividual(mGenotypeLength, mNumberOfGroups));
        currentFitness = mPopulation[i].evaluateFitness(mEvaluator);
        mBest.updateBest(mPopulation[i], currentFitness);
    }
}

const CIndividual& CGeneticAlgorithm::findParent() {
    std::mt19937 engine = CIndividual::generateRan(); 
    std::uniform_int_distribution<> distribution(0, mPopSize-1);

    const CIndividual& individual1 = mPopulation[distribution(engine)];
    const CIndividual& individual2 = mPopulation[distribution(engine)];
    
    return (individual1.evaluateFitness(mEvaluator) >= individual2.evaluateFitness(mEvaluator)) ? individual1 : individual2;
};

void CGeneticAlgorithm::executeSingleIteration() {
    std::vector<CIndividual> nextGeneration;
    nextGeneration.reserve(mPopSize);

    while (nextGeneration.size() < mPopSize){
        const CIndividual& firstParent = findParent();
        const CIndividual& secondParent = findParent();
        pair<CIndividual, CIndividual> descendants = firstParent.performCrossover(mCrossProb, secondParent); 
        nextGeneration.push_back(std::move(descendants.first));
        if (nextGeneration.size() < mPopSize) {
            nextGeneration.push_back(std::move(descendants.second));
        }
    }

    double currentFitness;
    for (CIndividual& individual : nextGeneration) {
        individual.performMutation(mMutProb);
        currentFitness = individual.evaluateFitness(mEvaluator);
        mBest.updateBest(individual, currentFitness);
    }

    mPopulation = std::move(nextGeneration);
}

const CBestIndividual& CGeneticAlgorithm::getBest() const {
    return mBest;
}

void CGeneticAlgorithm::executeAllIterations(std::chrono::seconds timeLimit) {
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now(); // starting the timer
    createInitialPopulation();

    while (true) {
        executeSingleIteration();
        std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
        std::chrono::seconds elapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime); // checking how much time has passed

        if (elapsed >= timeLimit) {
            break;
        }
        /*std::cout << "Current Best Fitness: " << mBest.getBestFitness() << std::endl;*/
    }
}




