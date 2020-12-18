#include <iostream>
#include <vector>
#include "Coloring.h"
#include "AdjacencyMatrix.h"

class Population {
	int populationSize;
	float mutationPossibility;
	std::vector<std::shared_ptr<Coloring>> popul;
	std::vector<std::shared_ptr<Coloring>> matingPool;
	int generations;
	int generations_without_change;
	bool status;
	AdjacencyMatrix* matrix;
	double maxFit;
public:

	Population(float, int, AdjacencyMatrix*,int);
	~Population();
	void calcFitnesses();
	void naturalSelection();
	void generateOFFspring();
	void checkIfFinished();
	bool getStatus() { return status; }
	int getGenerations() { return generations; }
	std::shared_ptr<Coloring> getBest();
};