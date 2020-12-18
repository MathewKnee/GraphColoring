#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "population.h"


Population::Population(float mp, int ps, AdjacencyMatrix* m,int max) {
    matrix = m;
	mutationPossibility = mp;
    populationSize = ps;
    srand(time(NULL));
    for (int i = 0; i < ps; i++) popul.push_back(std::shared_ptr<Coloring>(new Coloring(m,max)));
	calcFitnesses();
	matingPool = std::vector<std::shared_ptr<Coloring>>();
	status = false;
    generations = 0;
    generations_without_change = 0;
    maxFit = 0;
}

Population::~Population() {
    popul.clear();
    matingPool.clear();
}
void Population::calcFitnesses() {
    for (int i = 0; i < populationSize; i++)
        popul[i]->calcFitness();
}
double map(double val, double in_low, double in_high, double out_low, double out_high) {
    return out_low + ((out_high - out_low) / (in_high - in_low)) * (val - in_low);
}
void Population::naturalSelection() {
    matingPool.clear();

    double maxFitness = 0;
    for (int i = 0; i < populationSize; i++) {
        if (popul[i]->getFitness() > maxFitness) {
            maxFitness = popul[i]->getFitness();
        }
    }
    if (abs(maxFit - maxFitness) < 0.00001) {
        generations_without_change += 1;
    }
    else {
        generations_without_change = 0;
    }
    maxFit = maxFitness;
    for (int i = 0; i < populationSize; i++) {
        double fitness = map(popul[i]->getFitness(),0,maxFitness,0,1);
        int n = (int)(fitness * 100);
        for (int j = 0; j < n; j++) {
            matingPool.push_back(popul[i]);
        }
    }
}

void Population::generateOFFspring() {
    srand(time(NULL));
    for (int i = 0; i < populationSize-1; i+=2) {
        std::shared_ptr<Coloring> A = matingPool.at(rand() % matingPool.size());
        std::shared_ptr<Coloring> B = matingPool.at(rand() % matingPool.size());
        std::vector<std::shared_ptr<Coloring>> children = A->crossover(B);
        popul.insert(popul.begin() + i,children[0]);
        popul.insert(popul.begin() + i+1, children[1]);
        popul[i]->mutate(mutationPossibility);
        popul[i+1]->mutate(mutationPossibility);
    }
    generations++;
}

std::shared_ptr<Coloring> Population::getBest() {
    double best_fitness = 0.0;
    int index = 0;
    for (int i = 0; i < populationSize; i++) {
        if (popul[i]->getFitness() > best_fitness) {
            index = i;
            best_fitness = popul[i]->getFitness();
        }
    }
    return popul[index];
}

void Population::checkIfFinished() {
    std::cout << "Generation: " << generations << " Max Fitness: " << maxFit << std::endl;
    if (generations == 50) {
        status = true;
    }
    else if (generations_without_change == 7) {
        status = true;
    }

}

