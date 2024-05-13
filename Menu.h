#pragma once
#include <iostream>
#include "Graph.h"
#include "City.h"
#include "TransportationMethod.h"
#include "Utilities.h"


using namespace std;

class Menu {
private:
	City* SourceCityChecker(Graph* g) {
		string sourceCity;

		while (true) {
			system("CLS");

			cout << "Enter Source City Name: ";
			cin >>  sourceCity;

			if (g->FindCity(sourceCity) == NULL) {
				cout << "City Not Found, Try Again!\n";
				system("pause");
			}
			else {
				break;
			}
		}

		return g->FindCity(sourceCity);
	}

	City* DestinationCityChecker(Graph* g, string sourceCity) {
		string destinationCity;

		while (true) {
			system("CLS");
			cout << "Source City is: " << sourceCity << endl;
			cout << "Enter Destination City Name: ";
			cin >> destinationCity;

			if (g->FindCity(destinationCity) == NULL) {
				cout << "City Not Found, Try Again!\n";
				system("pause");
			}
			else if (destinationCity == sourceCity) {
				cout << "Destination City Cannot Be The Same As Source City, Try Again!\n";
				system("pause");
			}
			else {
				break;
			}
		}

		return g->FindCity(destinationCity);
	}

	TransportationMethod* TransportationChecker(Graph* g, City* sourceCity, City* destinationCity) {
		string transportationName;

		while (true) {
			system("CLS");

			cout << "Source City is: " << sourceCity->name << endl;
			cout << "Destination City is: " << destinationCity->name << endl;

			cout << "Enter Transportation Method Name: ";
			cin >> transportationName;

			if (sourceCity->FindTransportationMethod(destinationCity, transportationName) == NULL) {
				cout << "Transportation Not Found, Try Again!\n";
				system("pause");
			}
			else {
				break;
			}
		}

		return sourceCity->FindTransportationMethod(destinationCity, transportationName);
	}

public:
	void MainMenu(Graph* g) {
		int choice = -1;

		do {
			system("CLS");
			cout << "Welcome To Guide Me" << endl;
			cout << "-------------------\n";
			cout << "1- Traverse Transportation Graph.\n";
			cout << "2- Manage Transportation Graph.\n";
			cout << "3- Check Whether Transportation Graph is Complete or Not.\n";
			cout << "4- List Available Routes For a Certain Budget.\n";
			cout << "5- Exit." << endl;
			cout << "-------------------\n";
			cout << "Enter Your Choice: ";
			cin >> choice;

			switch (choice)
			{
			case 1:
				TraverseMenu(g);
				break;
			case 2:
				ManageTransportationsMenu(g);
				break;
			case 3:
				CheckCompleteMenu(g);
				break;
			case 4:
				ShowAvaliableRoutesMenu(g);
				break;
			case 5:
				choice = -1;
				break;
			default:
				cout << "Invalid Choice!" << endl;
				system("pause");
				cin.clear();
				cin.ignore(256, '\n');
				break;
			}
		} while (choice != -1);
	}

	void TraverseMenu(Graph* g) {
		int choice = -1;
		string cityName;

		while (true) {
			system("CLS");

			cout << "Enter Starting City Name: ";
			cin >> cityName;

			if (g->FindCity(cityName) == NULL) {
				cout << "City Not Found, Try Again!\n";
				system("pause");
			}
			else {
				break;
			}
		}

		do {
			system("CLS");
			cout << "----------------------\n";
			cout << "Choose Traversing Mode" << endl;
			cout << "----------------------\n";
			cout << "1- BFS\n";
			cout << "2- DFS\n";
			cout << "3- Back\n";
			cout << "----------------------\n";
			cout << "Enter Your Choice: ";
			cin >> choice;

			switch (choice)
			{
			case 1:
				cout << "----------------------\n";
				cout << g->BFS(g->FindCity(cityName)) << endl;
				system("pause");
				choice = -1;
				break;
			case 2:
				cout << "----------------------\n";
				cout << g->DFS(g->FindCity(cityName)) << endl;
				system("pause");
				choice = -1;
				break;
			case 3:
				choice = -1;
				break;
			default:
				cout << "Invalid Choice!" << endl;
				system("pause");
				cin.clear();
				cin.ignore(256, '\n');
				break;
			}
		} while (choice != -1);
	}

	void ManageTransportationsMenu(Graph* g) {
		int choice = -1;

		do {
			system("CLS");
			cout << "Manage Transportations" << endl;
			cout << "-------------------\n";
			cout << "1- Add New Transportation Method.\n";
			cout << "2- Update Existing Transportation Method.\n";
			cout << "3- Delete Existing Transportation Method.\n";
			cout << "4- Back.\n";
			cout << "-------------------\n";
			cout << "Enter Your Choice: ";
			cin >> choice;

			switch (choice)
			{
			case 1:
				AddTransportationMenu(g);
				break;
			case 2:
				UpdateTransportationMenu(g);
				break;
			case 3:
				DeleteTransportationMenu(g);
				break;
			case 4:
				choice = -1;
				break;
			default:
				cout << "Invalid Choice!" << endl;
				system("pause");
				cin.clear();
				cin.ignore(256, '\n');
				break;
			}
		} while (choice != -1);
	}

	void AddTransportationMenu(Graph* g) {
		int transportationPrice;
		string transportationName;

		City* sourceCity = SourceCityChecker(g);
		City* destinationCity = DestinationCityChecker(g, sourceCity->name);

		cout << "Enter Transportation Method Name: ";
		cin >> transportationName;

		bool PriceError = false;

		do {
			system("CLS");
			cout << "Transportation Method Name: " << transportationName << endl;


			cout << "Enter Transportation Method Price: ";
			cin >> transportationPrice;

			if (cin.fail()) {
				cout << "Please, Enter Numbers Only For Price!" << endl;
				system("Pause");
				cin.clear();
				cin.ignore(256, '\n');
				system("CLS");

				PriceError = true;
			}
			else {
				PriceError = false;
			}

		} while (PriceError);

		g->AddTransportationMethod(sourceCity, destinationCity, transportationName, transportationPrice);

		system("CLS");
		cout << "Transportation Method Has Been Added Successfully!" << endl;
		system("pause");
	}

	void UpdateTransportationMenu(Graph* g) {
		int newPrice;
		string newName;
		bool PriceError = false;

		City* sourceCity = SourceCityChecker(g);
		City* destinationCity = DestinationCityChecker(g, sourceCity->name);
		TransportationMethod* transportation = TransportationChecker(g, sourceCity, destinationCity);

		int choice = -1;
		do {
			cout << "What Do You Want To Edit" << endl;
			cout << "------------------------\n";
			cout << "1- Name\n";
			cout << "2- Price\n";
			cout << "3- Back\n";
			cout << "------------------------\n";
			cout << "Enter Your Choice: ";
			cin >> choice;

			switch (choice)
			{
			case 1:
				cout << "Enter The New Name: ";
				cin >> newName;

				g->UpdateTransportationMethod(sourceCity, destinationCity, transportation->name, newName, transportation->price);

				system("CLS");
				cout << "Transportation Method Name Has Been Edited Successfully!" << endl;
				system("pause");
				break;
			case 2:
				do {
					cout << "Enter The New Price: ";
					cin >> newPrice;

					if (cin.fail()) {
						cout << "Please, Enter Numbers Only For Price!" << endl;
						system("Pause");
						cin.clear();
						cin.ignore(256, '\n');
						system("CLS");
						
						PriceError = true;
					}
					else {
						PriceError = false;
					}

				} while (PriceError);

				g->UpdateTransportationMethod(sourceCity, destinationCity, transportation->name, transportation->name, newPrice);

				system("CLS");
				cout << "Transportation Method Price Has Been Edited Successfully!" << endl;
				system("pause");
				break;
			case 3:
				choice = -1;
				break;
			default:
				cout << "Invalid Choice!" << endl;
				system("pause");
				cin.clear();
				cin.ignore(256, '\n');
				break;
			}
		} while (choice != -1);
	}

	void DeleteTransportationMenu(Graph* g) {
		City* sourceCity = SourceCityChecker(g);
		City* destinationCity = DestinationCityChecker(g, sourceCity->name);
		TransportationMethod* transportation = TransportationChecker(g, sourceCity, destinationCity);

		g->DeleteTransportationMethod(sourceCity, destinationCity, transportation);

		system("CLS");
		cout << "Transportation Method Has Been Deleted Successfully!";
		system("pause");
	}

	void CheckCompleteMenu(Graph* g) {
		system("CLS");

		if (g->isComplete()) {
			cout << "The Transportation Map Is Complete!" << endl;
		}
		else {
			cout << "The Transportation Map Is Not Complete!" << endl;
		}

		system("pause");
	}

	void ShowAvaliableRoutesMenu(Graph* g) {
		int budget;

		City* sourceCity = SourceCityChecker(g);
		City* destinationCity = DestinationCityChecker(g, sourceCity->name);

		bool BudgetError = false;

		do {
			system("CLS");
			cout << "Source City: " << sourceCity->name << endl;
			cout << "Destination City: " << destinationCity->name << endl;

			cout << "Enter Your Budget: ";
			cin >> budget;

			if (cin.fail()) {
				cout << "Please, Enter Numbers Only For Budget!" << endl;
				system("Pause");
				cin.clear();
				cin.ignore(256, '\n');
				system("CLS");

				BudgetError = true;
			}
			else {
				BudgetError = false;
			}

		} while (BudgetError);

		g->ShowAvaliableRoutes(sourceCity, destinationCity, budget);

		system("pause");
	}
};