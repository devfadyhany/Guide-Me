#pragma once
#include <list>
#include <iterator>
#include <string>
#include "City.h"
#include "TransportationMethod.h"

using namespace std;

class Graph {
private:
	int size;
	list<City*>* adjacencyList;
	list<TransportationMethod>* transportList;

public:
	Graph() {
		size = 0;
	}

	void AddCity(string cityName) {
		City* newCity = new City(cityName);

		adjacencyList[size].push_back(newCity);
		size++;
	}

	void AddTransportationMethod(City* source, City* destination, string transportName, int price) {
		TransportationMethod* newTransport = new TransportationMethod(transportName, price);

		adjacencyList[source->name].push_back(destination);
		transportList[source->name].push_back(newTransport);
	}

	void DeleteEdge(City* source, City* destination) {
		int sourceIndex = -1;

		for (int i = 0; i < size; i++) {
			if (adjacencyList[i].front()->name == source->name) {
				sourceIndex = i;
				break;
			}
		}

		if (sourceIndex == -1) {
			return;
		}

		auto it = adjacencyList[sourceIndex].begin();
		while (it != adjacencyList[sourceIndex].end()) {
			if ((*it)->name == destination->name) {
				break;
			}
			++it;
		}

		if (it == adjacencyList[sourceIndex].end()) {
			return;
		}

		adjacencyList[sourceIndex].erase(it);

		if (transportList) {
			transportList[sourceIndex].erase(std::remove_if(transportList[sourceIndex].begin(), transportList[sourceIndex].end(),[destination](TransportationMethod& t) { return t.name == (*it)->name; }),transportList[sourceIndex].end());
		}
	}

	~Graph() {
		delete[] adjacencyList;
	}
};