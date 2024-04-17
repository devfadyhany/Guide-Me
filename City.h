#pragma once
#include <string>
#include <list>
#include <map>
#include "TransportationMethod.h"

using namespace std;

class City {
public:
	string name;
	list<pair<City*, TransportationMethod*>> connectedCities;

	City(string name) {
		this->name = name;
	}
};