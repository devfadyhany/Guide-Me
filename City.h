#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include "TransportationMethod.h"

using namespace std;

class City {
public:
	string name;
	list<pair<City*, vector<TransportationMethod*>>>* connectedCities;

	City(string name) {
		this->name = name;
		connectedCities = new list<pair<City*, vector<TransportationMethod*>>>;
	}

	void DisplayConnections() {
		cout << name << "->";

		list<pair<City*, vector<TransportationMethod*>>>::iterator it = connectedCities->begin();

		while (it != connectedCities->end()) {
			cout << "" << it->first->name;
			for (TransportationMethod* t : it->second) {
				cout << "[" << t->name << "/" << t->price << "]";
			}
			cout << "->";
			it++;
		}
	}

	TransportationMethod* FindTransportationMethod(City* dest, string transportName) {
		list<pair<City*, vector<TransportationMethod*>>>::iterator it = connectedCities->begin();

		while (it != connectedCities->end()) {
			if (it->first == dest) {
				for (int i = 0; i < it->second.size(); i++) {
					if (it->second[i]->name == transportName) {
						return it->second[i];
					}
				}
				break;
			}
			it++;
		}

		return NULL;
	}
};