#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include "TransportationMethod.h"

using namespace std;

class City {
private:
	bool RelationExist(vector<pair<string, string>>* visitedList, string source, string destination) {
		for (auto it = visitedList->begin(); it != visitedList->end(); it++) {
			if ((it->first == source && it->second == destination) || (it->first == destination && it->second == source)) {
				return true;
			}
		}

		return false;
	}

public:
	string name;
	unordered_map<City*, vector<TransportationMethod*>*> connectedCities;

	City(string name) {
		this->name = name;
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

	vector<string> ConnectionString(vector<pair<string, string>>* visitedList) {
		vector<string> connectionList;
		string connection;

		unordered_map<City*, vector<TransportationMethod*>*>::iterator it = connectedCities.begin();

		while (it != connectedCities.end()) {
			if (RelationExist(visitedList, name, it->first->name)) {
				it++;
				continue;
			}
			connection.append(name + " - " + it->first->name + " ");
			for (TransportationMethod* t : *it->second) {
				connection.append(t->name + " " + to_string(t->price) + " ");
			}
			connectionList.push_back(connection);
			connection.clear();
			visitedList->push_back(make_pair(name, it->first->name));
			it++;
		}

		return connectionList;
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