#pragma once
#include <vector>
#include <string>
#include "City.h"

using namespace std;

class Graph {
	vector<City> Cities;
	vector<vector<int>> adjacenyMatrix;

	void AddCity(City city);
	void DeleteCity(string CityName);
	void AddTransportationMethod(City source, City Destination, string TransportationMethodName, int price);
	void DeleteTransportationMethod(City source, City Destination, string TransportationMethodName);
};