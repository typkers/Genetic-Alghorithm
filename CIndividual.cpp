#include "CIndividual.h"
#include "CGeneticAlgorithm.h"
#include <vector>
using namespace NGroupingChallenge;

CIndividual::CIndividual() : mGenotypeLength(1), mNumberOfGroups(0) {
    mGenotype.resize(mGenotypeLength, 0);
}

CIndividual::CIndividual(int genotypeLength, int numberOfGroups) : mGenotypeLength(genotypeLength), mNumberOfGroups(numberOfGroups) {
    std::mt19937 engine = generateRan();
    std::uniform_int_distribution<> distribution(1, mNumberOfGroups);
    mGenotype.reserve(mGenotypeLength);

    for (int i = 0; i < mGenotypeLength; i++) {
        mGenotype.push_back(distribution(engine));
    }
}

double CIndividual::evaluateFitness(CGroupingEvaluator& evaluator) const {
    return evaluator.dEvaluate(mGenotype);
}

pair<CIndividual, CIndividual> CIndividual::performCrossover(double crossProb, const CIndividual& otherIndividual) const {
    std::mt19937 engine = generateRan(); 
    std::uniform_real_distribution<> distribution(0, 1);
    if (distribution(engine) < crossProb) {
        std::uniform_int_distribution<> distribution(1, mGenotypeLength-1);
        int crossOverPoint = distribution(engine);

        CIndividual descendant1 = *this; 
        CIndividual descendant2 = otherIndividual; 
        std::swap_ranges(descendant1.mGenotype.begin(), descendant1.mGenotype.begin() + crossOverPoint, descendant2.mGenotype.begin());

        return {std::move(descendant1), std::move(descendant2)};
    }
    else {return {*this, otherIndividual};}
}

void CIndividual::performMutation(double mutProb) {
    std::mt19937 engine = generateRan();
    std::uniform_real_distribution<> distribution(0, 1);
    std::uniform_int_distribution<> mutationDist(1, mNumberOfGroups);

    for (int& gene : mGenotype) {
        if (distribution(engine) < mutProb) {
            gene = mutationDist(engine);
        }
    }
}

const vector<int>& CIndividual::getGenotype() const {
    return mGenotype;
}
