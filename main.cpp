#include <iostream>
#include "Graph.h"

using namespace std;

int main() {
	Graph* g = new Graph();

	g->ReadGraphFromFile("Data/graph.txt");
	g->BFS(g->FindCity("Cairo"));
	g->WriteGraphInFile("Data/newGraph.txt");
	
	return 0;
}