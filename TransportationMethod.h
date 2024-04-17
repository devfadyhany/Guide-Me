#pragma once
#include <string>

using namespace std;

class TransportationMethod {
public:
	string name;
	int price;

	TransportationMethod(string name, int price) {
		this->name = name;
		this->price = price;
	}
};
