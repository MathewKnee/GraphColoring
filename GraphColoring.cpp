// GraphColoring.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "AdjacencyMatrix.h"
#include "graphColoringAlgorithms.h"

int main()
{
	// Tworzenie grafu
	int n = 10;
	int sat = 50;
	AdjacencyMatrix test(n, sat);
	test.show();

	// Algorytm kolorowania grafu
	int * result = simpleAlgorithm(&test);
	
	// Wypisanie wyniku kolorowania grafu
	printf("\nResult: ");
	for (int i = 0; i < n; i++) {
		printf("%d, ", result[i]);
	}
	printf("\n");
	delete[] result;
}
