#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <iterator>
#include <string>
#include <sstream>

#include "City.h"
#include "TransportationMethod.h"
#include "FileHandler.h"
#include "Utilities.h"

using namespace std;

class Graph {
private:
	int size;
	vector<City*>* adjacencyList;

public:
	Graph() {
		size = 0;
		adjacencyList = new vector<City*>;
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
		vector<City*>::iterator it = adjacencyList->begin();

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

		if (source->connectedCities[destination] != NULL) {
			vector<TransportationMethod*>::iterator srcIt = source->connectedCities[destination]->begin();

			while (srcIt != source->connectedCities[destination]->end()) {
				if ((*srcIt)->name == transportName) {
					return;
				}

				srcIt++;
			}

			source->connectedCities[destination]->push_back(newTransport);
			return;
		}

		vector<TransportationMethod*>* v = new vector<TransportationMethod*>;
		v->push_back(newTransport);

		source->connectedCities[destination] = v;
		destination->connectedCities[source] = v;
	}

	void UpdateTransportationMethod(City* source, City* destination, string transportName, string newName, int newPrice) {

		TransportationMethod* t = source->FindTransportationMethod(destination, transportName);

		if (t != NULL) {
			t->name = newName;
			t->price = newPrice;
		}
	}

	void DeleteTransportationMethod(City* source, City* destination, TransportationMethod* transport) {
		vector<TransportationMethod*>::iterator srcIt = source->connectedCities[destination]->begin();

		while (srcIt != source->connectedCities[destination]->end()) {
			if ((*srcIt) == transport) {
				source->connectedCities[destination]->erase(srcIt);
				break;
			}

			srcIt++;
		}

		if (source->connectedCities[destination]->empty()) {
			source->connectedCities.erase(destination);
			destination->connectedCities.erase(source);
		}

		delete transport;
	}

	void DisplayGraph() {
		vector<City*>::iterator it = adjacencyList->begin();

		while (it != adjacencyList->end()) {
			(*it)->DisplayConnections();
			cout << endl;
			it++;
		}
	}

	string BFS(City* startCity) {
		string TraversedCities;
		queue<City*> bfsQueue;

		unordered_map<City*, bool> visited;
		for (City* city : (*adjacencyList)) {
			visited[city] = false;
		}

		visited[startCity] = true;
		bfsQueue.push(startCity);

		while (!bfsQueue.empty()) {
			City* currentCity = bfsQueue.front();
			TraversedCities.append(currentCity->name + " ");
			bfsQueue.pop();

			for (auto it = currentCity->connectedCities.begin(); it != currentCity->connectedCities.end(); ++it) {
				if (!visited[it->first]) {
					visited[it->first] = true;
					bfsQueue.push(it->first);
				}
			}
		}

		return TraversedCities;
	}

	string DFS(City* startCity) {
		string TraversedCities;
		stack<City*> dfsStack;

		unordered_map<City*, bool> visited;
		for (City* city : (*adjacencyList)) {
			visited[city] = false;
		}

		visited[startCity] = true;
		dfsStack.push(startCity);

		while (!dfsStack.empty()) {
			City* currentCity = dfsStack.top();
			TraversedCities.append(currentCity->name + " ");
			dfsStack.pop();

			for (auto it = currentCity->connectedCities.begin(); it != currentCity->connectedCities.end(); ++it) {
				if (!visited[it->first]) {
					visited[it->first] = true;
					dfsStack.push(it->first);
				}
			}
		}

		return TraversedCities;
	}

	bool isComplete() {
		if (size == 0 || size == 1) {
			return false;
		}

		for (auto it = adjacencyList->begin(); it != adjacencyList->end(); it++) {
			if ((*it)->connectedCities.size() < size - 1) {
				return false;
			}
		}

		return true;
	}

	vector<pair<string,int>> TraverseRoutes(City* origianlSource, City* source, City* destination, vector<pair<string, int>> traversedRoutes, string routeInitial, unordered_map<City*, bool> visited, int routePrice) {
		if (visited.empty()) {
			for (City* city : (*adjacencyList)) {
				visited[city] = false;
			}
		}

		// Loop Through Connections Of the Source
		auto it = source->connectedCities.begin();
		while (it != source->connectedCities.end()) {
			City* currentCity = it->first;

			if (visited[currentCity] || currentCity == origianlSource) {
				it++;
				continue;
			}

			// Loop Through Transportations with the Current City
			for (auto transport : *it->second) {
				routePrice += transport->price;

				if (currentCity == destination) {
					traversedRoutes.push_back(make_pair(routeInitial + " " + source->name + " (" + transport->name + ") " + destination->name, routePrice) );
					routePrice -= transport->price;
				}
				else {
					routeInitial += source->name + " (" + transport->name + ") ";

					visited[currentCity] = true;
					traversedRoutes = TraverseRoutes(origianlSource, currentCity, destination, traversedRoutes, routeInitial, visited, routePrice);

					int pos = routeInitial.find(source->name);
					routeInitial = routeInitial.substr(0, pos);
					routePrice -= transport->price;

				}
			}

			it++;
		}
		return traversedRoutes;
	}

	vector<pair<string, int>> ClearExtraSpaces(vector<pair<string, int>> routes, int budget) {
		vector<pair<string, int>> temp;
		
		for (auto route : routes) {
			if (route.second <= budget) {
				string routeString;
				vector<string>* wordsOfRoutes = Utilities::split(route.first, ' ');
				for (auto word : *wordsOfRoutes) {
					if (word != "") {
						routeString += word + " ";
					}
				}
				temp.push_back(make_pair(routeString, route.second));
			}
		}

		return temp;
	}

	void swap(pair<string, int> &a, pair<string, int> &b) {
		pair<string, int> temp;
		temp = a;
		a = b;
		b = temp;
	}

	void sortByPrice(vector<pair<string, int>>& routes) {
		for (int i = 0; i < routes.size(); i++) {
			for (int j = i + 1; j < routes.size(); j++) {
				if (routes[j].second < routes[i].second) {
					swap(routes[i], routes[j]);
				}
			}
		}
	}

	void ShowAvaliableRoutes(City* sourceCity, City* destinationCity, int budget) {
		unordered_map<City*, bool> visited;
		vector<pair<string, int>> routes = TraverseRoutes(sourceCity, sourceCity, destinationCity, routes, "", visited, 0);
		routes = ClearExtraSpaces(routes, budget);
		sortByPrice(routes);

		if (routes.size() == 0){
			cout << "Couldn't Find Any Routes For Your Budget." << endl;
		}

		int counter = 1;
		for (auto route : routes) {
			cout << "Route#" << counter << ": " << route.first << " " << route.second << endl;
			counter++;
		}
	}

	void ReadGraphFromFile(string filePath) {
		vector<string>* strList = FileHandler::ReadFromFile(filePath);

		for (int i = 1; i < strList->size(); i++) {
			vector<string>* splitedString = Utilities::split(strList->at(i), ' ');

			string sourceCity = splitedString->at(0);
			AddCity(sourceCity);

			if (splitedString->size() < 4) {
				continue;
			}

			string destinationCity = splitedString->at(2);
			AddCity(destinationCity);

			

			for (int i = 3; i < splitedString->size(); i = i + 2) {
				AddTransportationMethod(FindCity(sourceCity), FindCity(destinationCity), splitedString->at(i), stoi(splitedString->at(i + 1)));
			}
		}
	}

	void WriteGraphInFile(string filePath) {
		vector<string>* strList = new vector<string>;
		vector<pair<string, string>>* visitedList = new vector<pair<string, string>>;

		strList->push_back(to_string(size));

		for (int i = 0; i < adjacencyList->size(); i++) {

			vector<string> ConnectionString = adjacencyList->at(i)->ConnectionString(visitedList);

			for (int j = 0; j < ConnectionString.size(); j++) {
				strList->push_back(ConnectionString[j]);
			}
		}

		FileHandler::WriteInFile(filePath, strList);
	}

	~Graph() {
		delete[] adjacencyList;
	}
};