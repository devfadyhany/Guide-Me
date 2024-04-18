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
		if (FindCity(cityName) != NULL) {
			return;
		}

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

		list<pair<City*, vector<TransportationMethod*>>>::iterator srcIt = source->connectedCities->begin();
		list<pair<City*, vector<TransportationMethod*>>>::iterator destIt = destination->connectedCities->begin();

		while (srcIt != source->connectedCities->end()) {
			if (srcIt->first == destination) {
				for (int i = 0; i < srcIt->second.size(); i++) {
					if (srcIt->second[i]->name == transportName) {
						return;
					}
				}
				srcIt->second.push_back(newTransport);
				break;
			}
			srcIt++;
		}

		while (destIt != destination->connectedCities->end()) {
			if (destIt->first == source) {
				for (int i = 0; i < destIt->second.size(); i++) {
					if (destIt->second[i]->name == transportName) {
						return;
					}
				}
				destIt->second.push_back(newTransport);
				return;
			}
			destIt++;
		}

		vector<TransportationMethod*> v;
		v.push_back(newTransport);

		source->connectedCities->push_back(make_pair(destination, v));
		destination->connectedCities->push_back(make_pair(source, v));
		
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
		list<pair<City*, vector<TransportationMethod*>>>::iterator srcIt = source->connectedCities->begin();
		list<pair<City*, vector<TransportationMethod*>>>::iterator destIt = destination->connectedCities->begin();

		while (srcIt != source->connectedCities->end()) {
			if (srcIt->first == destination) {
				vector<TransportationMethod*>::iterator it = srcIt->second.begin();

				while (it != srcIt->second.end()) {
					if (*it == transport) {
						srcIt->second.erase(it);
						break;
					}
					it++;
				}
				break;
			}
			srcIt++;
		}

		while (destIt != destination->connectedCities->end()) {
			if (destIt->first == source) {
				vector<TransportationMethod*>::iterator it = destIt->second.begin();

				while (it != destIt->second.end()) {
					if (*it == transport) {
						destIt->second.erase(it);
						break;
					}
					it++;
				}
				break;
			}
			destIt++;
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