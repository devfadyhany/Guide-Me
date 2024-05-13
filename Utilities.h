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

	 static bool equalsIgnoreCase(string& str1, string& str2) {	
		string str1_lower = str1;
		string str2_lower = str2;
		transform(str1_lower.begin(), str1_lower.end(), str1_lower.begin(), ::tolower);
		transform(str2_lower.begin(), str2_lower.end(), str2_lower.begin(), ::tolower);
		return strcmp(str1_lower.c_str(), str2_lower.c_str()) == 0;
	}
};