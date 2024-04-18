#pragma once
#include <iostream>
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

public:
	Graph() {
		size = 0;
		adjacencyList = new list<City*>;
	}

	void AddCity(string cityName) {
		City* newCity = new City(cityName);

		adjacencyList->push_back(newCity);
		size++;
	}

	City* FindCity(string cityName) {
		list<City*>::iterator it = adjacencyList->begin();

		while (it != adjacencyList->end()) {
			if ((*it)->name == cityName) {
				return (*it);
			}
			it++;
		}

		return NULL;
	}

	void AddTransportationMethod(City* source, City* destination, string transportName, int price) {
		TransportationMethod* newTransport = new TransportationMethod(transportName, price);

		source->connectedCities->push_back(make_pair(destination, newTransport));
		destination->connectedCities->push_back(make_pair(source, newTransport));
		
	}

	void UpdateTransportationMethod(TransportationMethod* transport, string newName, int newPrice) {
		transport->name = newName;
		transport->price = newPrice;
	}

	void UpdateTransportationMethod(TransportationMethod* transport, string newName) {
		transport->name = newName;
	}

	void UpdateTransportationMethod(TransportationMethod* transport, int newPrice) {
		transport->price = newPrice;
	}

	void DeleteTransportationMethod(City* source, City* destination, TransportationMethod* transport) {
		list<pair<City*, TransportationMethod*>>::iterator sourceIterator = source->connectedCities->begin();
		list<pair<City*, TransportationMethod*>>::iterator destinationIterator = destination->connectedCities->begin();

		while (sourceIterator != source->connectedCities->end()) {
			if (sourceIterator->second == transport) {
				source->connectedCities->remove(*sourceIterator);
				break;
			}
			sourceIterator++;
		}

		while (destinationIterator != destination->connectedCities->end()) {
			if (destinationIterator->second == transport) {
				destination->connectedCities->remove(*destinationIterator);
				break;
			}
			destinationIterator++;
		}
		
		delete transport;
	}

	void DisplayGraph() {
		list<City*>::iterator it = adjacencyList->begin();

		while (it != adjacencyList->end()) {
			(*it)->DisplayConnections();
			cout << endl;
			it++;
		}
	}

	~Graph() {
		delete[] adjacencyList;
	}
};