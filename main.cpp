// GraphColoring.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <algorithm>
#include "AdjacencyMatrix.h"
#include "graphColoringAlgorithms.h"
#include "Coloring.h"
using namespace std;

template <typename T>
void checkInput(T& x) {
	while (!(cin >> x)) {
		cout << "ERROR: Wrong type!\nTry again: ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
}

template <typename T>
void get_input(T& x) {
	do {
		checkInput(x);
		if (x <= 0)cout << "Nr less than 0!\nTry again: ";
	} while (x <= 0);
}

void menu() {
	system("cls");
	cout << "MENU" << endl;
	for (int i = 0; i < 30; i++)cout << "-";
	cout << "\n1. Make a graph\n";
	cout << "2. Read a graph\n";
	cout << "3. Exit\n";
	for (int i = 0; i < 30; i++)cout << "-";
	cout << endl;
}

int main()
{
	AdjacencyMatrix* graph = NULL;
	int* result;
	char choice;
	while (true) {
		menu();
		choice = _getch();
		switch (choice) {
			// Tworzenie grafu
		case '1': {
			int n, sat;
			cout << "Nr of vertices (>0): ";
			get_input(n);
			cout << "\nSaturation (>0): ";
			get_input(sat);
			cout << "\nCreating graph. Please wait...\n";
			graph = new AdjacencyMatrix(n, sat);
			break;
		}
		// Wczytywanie grafu
		case '2': {
			string name;
			cout << "Name of file: ";
			getline(cin, name);
			try {
				graph = new AdjacencyMatrix(name);
				cout << "Done!\n";
			}
			catch (FileLoadException& error) {
				cout << "File not found!\n";
				delete graph;
				graph = NULL;
			}
			break;
		}
		case '3':
			system("cls");
			return 0;
		default:
			continue;
		}
		if (graph) {
			system("cls");
			cout << "Choose algorithm:" << endl;
			for (int i = 0; i < 30; i++)cout << "-";
			cout << "\n1. Simple algorithm\n";
			cout << "2. Genetic algorithm\n";
			cout << "3. Exit\n";
			for (int i = 0; i < 30; i++)cout << "-";
			cout << endl;
			choice = _getch();

			switch (choice) {
			case '1':
				
				// Algorytm kolorowania grafu
				result = simpleAlgorithm(graph);

				// Wypisanie macierzy sasiedztwa
				cout << "\nWould you like to see the graph? [y/n]";
				do {
					choice = _getch();
				} while (choice != 'y' && choice != 'n');
				if (choice == 'y')
				{
					cout << "\nGraph:\n";
					graph->show();
				}

				// Wypisanie wyniku kolorowania grafu
				cout << "\nWould you like to see the result of coloring? [y/n]";
				do {
					choice = _getch();
				} while (choice != 'y' && choice != 'n');
				if (choice == 'y') {
					printf("\nResult of coloring: ");
					cout << "\nUsed colors: " << result[graph->get_vertices()+1] << endl;
					cout << "Colors: " << endl;
					for (int i = 0; i < graph->get_vertices(); i++) {
						printf("%d -> %d\n", i + 1, result[i]+1);
					}
					printf("\n");
				}

				//Usuwanie danych grafu
				delete[] result;
				delete graph;
				graph = NULL;
				break;
			case '2':
			{
				// Algorytm kolorowania grafu
				std::shared_ptr<Coloring> res = geneticAlgorithm(graph);

				// Wypisanie macierzy sasiedztwa
				cout << "\nWould you like to see the graph? [y/n]";
				do {
					choice = _getch();
				} while (choice != 'y' && choice != 'n');
				if (choice == 'y')
				{
					cout << "\nGraph:\n";
					graph->show();
				}

				// Wypisanie wyniku kolorowania grafu
				cout << "\nWould you like to see the result of coloring? [y/n]";
				do {
					choice = _getch();
				} while (choice != 'y' && choice != 'n');
				if (choice == 'y') {
					printf("\nResult of coloring: ");
					cout << "\nUsed colors: " << res->getChromaticNumber() << endl;
					cout << "Colors: " << endl;
					for (int i = 0; i < graph->get_vertices(); i++) {
						printf("%d -> %d\n", i + 1, res->getValues()[i]);
					}
					printf("\n");
					
				}
				
				//Usuwanie danych grafu

				delete graph;
				graph = NULL;
				break;
			}
			case '3': {
				system("cls");
				return 0; }
			default:
				continue;
			}

			
		}
		cout << endl << "Press any key to continue..." << endl;
		_getch();
	}
}