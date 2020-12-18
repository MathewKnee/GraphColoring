#include "Coloring.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>
int myrandom(int i) { return std::rand() % i; }
Coloring::Coloring(AdjacencyMatrix* m,int max_colors) {
	matrix_ref = m;
	matrix = m->get_matrix();
	vertices = m->get_vertices();
	//srand(time(NULL));
	for (int i = 0; i < (*m).get_vertices(); i++) {
		values.push_back(i % max_colors + 1);
	}
	std::random_shuffle(values.begin(), values.end(), myrandom);

}
Coloring::Coloring(std::vector<int> vals, AdjacencyMatrix* m) {
	matrix_ref = m;
	matrix = m->get_matrix();
	vertices = m->get_vertices();
	for (int i = 0; i < (*m).get_vertices(); i++) {
		values.push_back(vals[i]);
	}
}
Coloring::~Coloring() {
	
}
int Coloring::getChromaticNumber() {
	std::vector<int> used_colors;
	for (int i = 0; i < this->vertices; i++) {
		bool addColor = true;
		for (int j = 0; j < used_colors.size(); j++) {
			if (used_colors[j] == this->values[i]) {
				addColor = false;
				break;
			}
		}
		if (addColor) used_colors.push_back(this->values[i]);
	}
	return used_colors.size();
}
double Coloring::getFitness() {
	return this->fitness;
}
std::vector<int> Coloring::getValues() {
	return this->values;
}
void Coloring::calcFitness() {
	int sum = 1;
	for (int i = 0; i < this->vertices; i++) {
		for (int j = 0; j < i; j++) {
			if (this->matrix[i][j] == 1 && values[i] == values[j]) sum += 2;
		}
	}
	this->fitness = 1 / (double)sum;
}
bool Coloring::conflicts(int vertice) {
	for (int i = 0; i < this->vertices; i++) {
		for (int j = 0; j < i; j++) {
			if (this->matrix[i][j] == 1 && values[i] == values[j]) return true;
		}
	}
	return false;
}
void Coloring::setColor(int vertice, int color) {
	this->values[vertice] = color;
}
std::vector<std::shared_ptr<Coloring>> Coloring::crossover(std::shared_ptr<Coloring> partner) {
	//CEX Crossover
	std::vector<std::shared_ptr<Coloring>> ret;
	ret.push_back(std::shared_ptr<Coloring>(new Coloring(partner->getValues(), this->matrix_ref)));
	ret.push_back(std::shared_ptr<Coloring>(new Coloring(this->getValues(), this->matrix_ref)));
	for (int i = 0; i < this->vertices; i++) {
		if (!this->conflicts(i)) ret[0]->setColor(i, this->getValues()[i]);
		if (!partner->conflicts(i)) ret[1]->setColor(i, partner->getValues()[i]);
	}
	return ret;

}
void Coloring::mutate(double mutation_rate) {
	if ((double)rand() / (double)RAND_MAX <= mutation_rate) {
		int x = rand() % values.size();
		int y = rand() % values.size();
		int temp = this->values[x];
		this->values[x] = this->values[y];
		this->values[y] = temp;
	}
}