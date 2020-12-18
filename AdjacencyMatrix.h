#pragma once
#include <iostream>
#include <vector>
using namespace std;

class AdjacencyMatrix {
private:
	std::vector<std::vector<int>> matrix;
	int vertices;
	int edges = 0;
public:
	AdjacencyMatrix(int, int);
	AdjacencyMatrix(string);
	~AdjacencyMatrix();
	void show();
	int get_vertices() { return vertices; }
	int get_edges() { return edges; }
	std::vector<std::vector<int>> get_matrix();
};

struct FileLoadException : public exception {
	string path;
	FileLoadException(string& p) : path(p) {}
	const char* what() const throw() {
		string ret = "Error opening a file\nPath: " + path;
		cout << ret.c_str() << endl;
		return "ERROR - Couldn't open a file";
	}
};
