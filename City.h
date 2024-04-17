#pragma once
#include <string>
#include <vector>
#include "TransportationMethod.h"

using namespace std;

class City {
	string name;
	vector<TransportationMethod> transportations;
};