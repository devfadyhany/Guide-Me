#include <iostream>
#include "Graph.h"
#include "Menu.h"

using namespace std;

int main() {
	Graph* mainGraph = new Graph();
	Menu menu;

	mainGraph->ReadGraphFromFile("Data/graph.txt");
	menu.MainMenu(mainGraph);
	mainGraph->WriteGraphInFile("Data/graph.txt");
	
	return 0;
}