#include <iostream>
#include "Graph.h"

using namespace std;

int main() {
	Graph* g = new Graph();

	g->AddCity("Cairo");
	g->AddCity("Giza");
	g->AddCity("Dahab");

	City* src = g->FindCity("Cairo");
	City* dest = g->FindCity("Giza");

	g->AddTransportationMethod(src, dest, "Metro", 30);
	dest = g->FindCity("Dahab");
	g->AddTransportationMethod(src, dest, "Bus", 15);
	dest = g->FindCity("Giza");
	g->AddTransportationMethod(src, dest, "Bus", 15);

	g->DisplayGraph();

	/*
	TransportationMethod* t = src->FindTransportationMethod(dest, "Metro");
	g->DeleteTransportationMethod(src, dest, t);

	g->DisplayGraph();
	*/
	return 0;
}