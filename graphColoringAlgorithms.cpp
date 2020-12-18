#include "graphColoringAlgorithms.h"
#include "population.h"

#include <vector>
int * simpleAlgorithm(AdjacencyMatrix *graph) {
	std::vector<std::vector<int>> m = graph->get_matrix();
	int v_num = (*graph).get_vertices();
	// Tablica kolorowania wierzchołków
	// -1 -> brak koloru
	int * colors = new int[v_num + 1];
	for (int i = 0; i < v_num; i++)
		colors[i] = -1;

	for (int i = 0; i < v_num; i++) {
		// Tablica dostępnych kolorów
		// 0 -> dostępny
		// 1 -> niedostępny
		int * adjacent_colors = new int[v_num]();

		// Sprawdzamy czy i-ty wierzchołek jest incydentny z j-tym oraz czy j-ty jest pokolorowany
		for (int j = 0; j < v_num; j++) {
			if (m[i][j] == 1 && colors[j] > -1)
				// odznaczamy dostępność koloru j-tego wierzchołka
				adjacent_colors[colors[j]] = 1;
		}

		// Jeżeli j-ty kolor jest wolny przydziel go i-temu wierzchołkowi
		for (int j = 0; j < v_num; j++) {
			if (adjacent_colors[j] == 0) {
				colors[i] = j;
				break;
			}
		}
		delete[] adjacent_colors;
	}

	int max = colors[0];
	for (int i = 0; i < v_num; i++)
		if (colors[i] > max)
			max = colors[i];
	colors[v_num] = max + 1;
	
	return colors;
}

std::shared_ptr<Coloring> geneticAlgorithm(AdjacencyMatrix* graph) {
	double mutation_rate = 0.02;
	int population_size = 500;
	
	for (int i = 0; i < graph->get_vertices(); i++) {
		std::cout << "Finding k-coloring k = " << i + 1 << std::endl;
		Population pop(mutation_rate, population_size, graph, i + 1);
		while (!pop.getStatus()) {
			pop.calcFitnesses();
			pop.naturalSelection();
			pop.generateOFFspring();
			pop.checkIfFinished();
		}
		std::shared_ptr<Coloring> best = pop.getBest();
		best->calcFitness();
		
		if (1.0 - best->getFitness() <= 0.0001) {
			return best;
			break;
		}
	}
		
}