#pragma once
#include <vector>
#include <string>

using namespace std;

class Utilities {
public:
	static vector<string>* split(string str, char delimiter) {
		vector<string>* itemList = new vector<string>;

		size_t start = 0;
		size_t end = str.find(delimiter);

		while (end <= str.length()) {
			itemList->push_back(str.substr(start, end - start));
			start = end + 1;
			end = str.find(delimiter, start);
		}

		itemList->push_back(str.substr(start));

		return itemList;
	}
};