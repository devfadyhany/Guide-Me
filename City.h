#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include "TransportationMethod.h"

using namespace std;

class City {
public:
	string name;
	unordered_map<City*, vector<TransportationMethod*>*> connectedCities;

	City(string name) {
		this->name = name;
		//connectedCities = new unordered_map<City*, vector<TransportationMethod*>>;
	}

	void DisplayConnections() {
		cout << name << "->";

		unordered_map<City*, vector<TransportationMethod*>*>::iterator it = connectedCities.begin();

		while (it != connectedCities.end()) {
			cout << "" << it->first->name;
			for (TransportationMethod* t : *it->second) {
				cout << "[" << t->name << "/" << t->price << "]";
			}
			cout << "->";
			it++;
		}
	}

	TransportationMethod* FindTransportationMethod(City* dest, string transportName) {
		vector<TransportationMethod*>::iterator it = connectedCities[dest]->begin();

		
		while (it != connectedCities[dest]->end()) {
			if ((*it)->name == transportName) {
				return (*it);
			}
			it++;
		}

		return NULL;
		
	}
};