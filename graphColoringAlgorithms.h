#pragma once
#include "AdjacencyMatrix.h"
#include "Coloring.h"
int* simpleAlgorithm(AdjacencyMatrix *graph);
std::shared_ptr<Coloring> geneticAlgorithm(AdjacencyMatrix* graph);