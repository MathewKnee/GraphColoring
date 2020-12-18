#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include "AdjacencyMatrix.h"

using namespace std;


AdjacencyMatrix::AdjacencyMatrix(int n, int saturation) {
	string path = "./graphs/N" + to_string(n) + "_E" + to_string(saturation) + ".txt";
	fstream f;
	f.open(path, fstream::out);
	f << n << endl;

	matrix = std::vector<std::vector<int>>(n, std::vector<int>(n));
	vertices = n;
	edges = 0;
	
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			int p = rand() % 101;
			if (i != j && p <= saturation) {
				matrix[j][i] = 1;
				matrix[i][j] = 1;
				f << i + 1 << " " << j + 1 << endl;
				edges++;
			}
		}
	}
	f.close(); 
}
/////////////////////////////////////////////////////////////////////////////////
template <class Container>
void split(const string& str, Container& cont, char delim = ' ')
{
	stringstream ss(str);
	string token;
	while (getline(ss, token, delim)) {
		cont.push_back(token);
	}
}

AdjacencyMatrix::AdjacencyMatrix(string filename) {
	ifstream input;
	try {
		input.open("./graphs/"+filename, ifstream::in);
		if (!input.is_open()) {
			throw FileLoadException(filename);
		}
	}
	catch (const std::ifstream::failure& e) {
		cout << e.what() << endl;
		throw FileLoadException(filename);
		return;
	}
	cout << "\nCreating graph. Please wait...\n";

	string line;
	getline(input, line);
	int n = stoi(line);
	vertices = n;
	edges = 0;
	matrix = std::vector<std::vector<int>>(n, std::vector<int>(n));
	
	while (getline(input, line)) {
		while (line[0] == ' ')
			line.erase(0, 1);
		std::vector<std::string> split_line;
		split(line, split_line, ' ');
		matrix[stoi(split_line[0]) - 1][stoi(split_line[1]) - 1] = 1;
		matrix[stoi(split_line[1]) - 1][stoi(split_line[0]) - 1] = 1;
		edges++;
	}
}

AdjacencyMatrix::~AdjacencyMatrix() {
	
}

void AdjacencyMatrix::show(){
	for (int i = 0; i < vertices + 2; i++) {
		if (i == 0)
			for (int j = 0; j < vertices + 2; j++)
				switch (j){
				case 0:
					printf(" ");
					break;
				case 1:
					printf("| ");
					break;
				default:
					printf("%d ", j - 1);
					break;
				}
		else if (i == 1)
			for (int j = 0; j < vertices * 2 + 2; j++)
				printf("-");
		else
			for (int j = 0; j < vertices+2; j++)
				switch (j) {
				case 0:
					printf("%d", i - 1);
					break;
				case 1:
					printf("| ");
					break;
				default:
					printf("%d ", matrix[i - 2][j - 2]);
					break;
				}
			printf("\n");
	}
}

std::vector<std::vector<int>> AdjacencyMatrix::get_matrix() {
	std::vector<std::vector<int>> matrix_copy(vertices,std::vector<int>(vertices));
	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			matrix_copy[i][j] = matrix[i][j];
		}
	}
	return matrix_copy;
}