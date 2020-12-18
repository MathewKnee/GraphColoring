#pragma once
#include <vector>
#include "AdjacencyMatrix.h"
class Coloring
{
private:
	AdjacencyMatrix* matrix_ref;
	std::vector<int> values;
	std::vector<std::vector<int>> matrix;
	int vertices;
	double fitness = 0.0;
public:
	Coloring(AdjacencyMatrix*,int);
	Coloring(std::vector<int>,AdjacencyMatrix*);
	~Coloring();
	std::vector<std::shared_ptr<Coloring>>  crossover(std::shared_ptr<Coloring>  partner);
	void mutate(double mutation_rate);
	void calcFitness();
	double getFitness();
	std::vector<int> getValues();
	int getChromaticNumber();
	bool conflicts(int vertice);
	void setColor(int vertice,int color);
};

