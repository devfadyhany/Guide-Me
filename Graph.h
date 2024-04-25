#pragma once
#include <iostream>
#include<queue>
#include <vector>
#include <iterator>
#include <string>

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

	void UpdateTransportationMethod(TransportationMethod* transport, string newName, int newPrice) {
		transport->name = newName;
		transport->price = newPrice;
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

	void ReadGraphFromFile(string filePath) {
		vector<string>* strList = FileHandler::ReadFromFile(filePath);

		for (int i = 1; i < strList->size(); i++) {
			vector<string>* splitedString = Utilities::split(strList->at(i), ' ');

			string sourceCity = splitedString->at(0);
			string destinationCity = splitedString->at(2);

			AddCity(sourceCity);
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

	void BFS(City* startCity) {
		// Create a queue for BFS
		queue<City*> bfsQueue;

		// Mark all the cities as not visited
		unordered_map<City*, bool> visited;
		for (City* city : (*adjacencyList)) {
			visited[city] = false;
		}

		// Mark the current city as visited and enqueue it
		visited[startCity] = true;
		bfsQueue.push(startCity);

		// Iterator to traverse adjacency list
		//vector<City*>::iterator it;

		while (!bfsQueue.empty()) {
			// Dequeue a city from queue and print it
			City* currentCity = bfsQueue.front();
			cout << currentCity->name << " ";
			bfsQueue.pop();

			// Get all adjacent cities of the dequeued city currentCity.
			// If an adjacent has not been visited, then mark it visited
			// and enqueue it
			for (auto it = currentCity->connectedCities.begin(); it != currentCity->connectedCities.end(); ++it) {
				if (!visited[it->first]) {
					visited[it->first] = true;
					bfsQueue.push(it->first);
				}
			}
		}
	}

	~Graph() {
		delete[] adjacencyList;
	}
};