#pragma once
#include<fstream>
#include<vector>
#include<string>

using namespace std;

class FileHandler {
public:
	static void WriteInFile(string filePath, vector<string> dataList[]) {
		ofstream newFile(filePath);

		for (int i = 0; i < dataList->size(); i++) {
			newFile << dataList->at(i) << endl;
		}

		newFile.close();
	}

	static vector<string>* ReadFromFile(string filePath) {
		ifstream newFile(filePath);

		string currentText;

		vector<string>* dataList = new vector<string>;

		while (getline(newFile, currentText)) {
			dataList->push_back(currentText);
		}

		return dataList;
	}
};