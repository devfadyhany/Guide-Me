#pragma once
#include <iostream>
#include <string>
#include <list>
#include <map>
#include "TransportationMethod.h"

using namespace std;

class City {
public:
	string name;
	list<pair<City*, TransportationMethod*>>* connectedCities;

	City(string name) {
		this->name = name;
		connectedCities = new list<pair<City*, TransportationMethod*>>;
	}

	void DisplayConnections() {
		cout << name << "->";

		list<pair<City*, TransportationMethod*>>::iterator it = connectedCities->begin();

		while (it != connectedCities->end()) {
			cout << "" << it->first->name << "[" << it->second->name << "/" << it->second->price << "]->";			
			it++;
		}
	}

	TransportationMethod* FindTransportationMethod(City* dest, string transportName) {
		list<pair<City*, TransportationMethod*>>::iterator it = connectedCities->begin();

		while (it != connectedCities->end()) {
			if (it->first == dest && it->second->name == transportName) {
				return it->second;
			}
			it++;
		}

		return NULL;
	}
};