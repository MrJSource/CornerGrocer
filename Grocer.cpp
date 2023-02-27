#include "Grocer.h"
//default constructor if default file names are going to be used.
Grocer::Grocer() {
	setInputFileName("CS210_Project_Three_Input_File.txt");
	setOutputFileName("frequency.dat");
	readFile();
	writeFile();
}
//constructor to set specific file names.
Grocer::Grocer(string inputFileName, string outputFileName) {
	setInputFileName(inputFileName);
	setOutputFileName(outputFileName);
	readFile();
	writeFile();
}
//setter for input file name
void Grocer::setInputFileName(string fileName) {
	inputFileName = fileName;
}
//setter for output file name
void Grocer::setOutputFileName(string fileName) {
	outputFileName = fileName;
}
void Grocer::writeFile() {
	//ofstream object to for writing too file
	ofstream outFS;
	//open the file
	outFS.open(outputFileName);
	//checks if file is open
	if (!outFS.is_open()) {
		cout << "Could not open file." << endl;
	}
	//iterates thru grocerMap and saves each item to file
	for (auto itr = grocerMap.begin(); itr != grocerMap.end(); itr++) {
		outFS << itr->first << " " << itr->second << endl;
	}

	//close file before ending function
	outFS.close();
}
void Grocer::readFile() {
	//ifstream object for reading file
	ifstream inFS;
	//opens the file
	inFS.open(inputFileName);
	//checks if file opened corretly
	if (!inFS.is_open()) {
		cout << "Could not open file";
	}
	// temporary variables to store read data before saving to vectors
	string tempString;
	//while we can still read program then read data and write to map
	map<string, int> tempMap;
	while (!inFS.fail()) {
		inFS >> tempString;
		if (tempMap.count(tempString)) {
			tempMap[tempString] += 1;
		}
		else {
			tempMap.insert(std::pair<std::string, int>(tempString, 1));
		}
	}
	grocerMap = tempMap;
	//close the file before ending function
	inFS.close();
}
//prints out each item in the grocerMap
void Grocer::printGrocerMap() {
	for (auto itr = grocerMap.begin(); itr != grocerMap.end(); itr++) {
		cout << itr->first << " " << itr->second << endl;
	}
}
//prints out menu options for main menu
void Grocer::printMenu() {
	cout << "\033[1m\033[4mMain Menu:\033[0m" << endl; // Bold and underline text
	cout << "\033[33m1. Search For Groccery Item.\033" << endl; // Yellow number menu option 1
	cout << "\033[32m2. Show All Grocery Items And Amounts.\033" << endl; // Green number menu option 2
	cout << "\033[31m3. Show All Grocery Items In Histogram\033" << endl; // Red number menu option 3
	cout << "\033[34m4. Exit The Program\033" << endl; // Blue number menu option 4
	cout << "[0m"; //clearing the color used in previous cout on a new line to avoid confusion
	//gets menu choice and checks that it is of correct range and type
	int choice = getMenuOption();
	//chooses what to do with menu option
	executeMenuOption(choice);
}
//function to run grocer program
void Grocer::run() {
	while (true) {
		printMenu();
	}
}
//function to get input for menu options
int Grocer::getMenuOption() {
	//variable for store menu option selected
	int menuOption;
	//while method to loop until correct input is selected
	while (true) {
		cout << "Choose a menu option: ";
		cin >> menuOption;
		//try catch block for exception handling input
		try {
			//if menu option is out of range thru exception
			if (menuOption < 1 || menuOption > 4) {
				throw std::out_of_range("Invalid input. Value must be between 1 and 4.");
				menuOption = 0;
			}
			//if in range break from while loop
			else {
				break;
			}
		}
		//catch block for handling incorrect input and clearing input stream
		catch (std::out_of_range& e) {
			std::cout << e.what() << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	//returns menu option for next function
	return menuOption;
}
//function for choosing what to do with menu option input
void Grocer::executeMenuOption(int choice) {
	//clear console
	system("cls");
	//if 1 call search for item function
	if (choice == 1) {
		searchForItem();
	}
	// if 2 call print grocer map function
	else if (choice == 2) {
		printGrocerMap();
	}
	//if 3 call print grocer histogram function
	else if (choice == 3) {
		printGrocerHistogram();
	}
	//if 4 exit program with code 0
	else if (choice == 4) {
		exit(0);
	}
	//pause for input
	system("pause");
	//clear console for next call of print menu
	system("cls");
}
void Grocer::searchForItem() {
	//prompt user to enter a term to search for
	//return the amount of that item in the map if at all
	//if no items just return 0 items
	// 
	//string for input item to search for
	string input;
	//boolean for looping while input is not valid
	bool inputIsValid = false;
	//while input is not valid loop
	while (!inputIsValid) {
		cout << "Please enter an item name to search for: ";
		cin >> input;
		//try and catch block for validating input
		try {
			// Check if input is valid
			for (char c : input) {
				if (!isalpha(c)) {
					throw invalid_argument("Input is not a valid string.");
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
			}

			// Set flag to indicate that input is valid
			inputIsValid = true;

			// Perform action if input is valid
			if (grocerMap.find(input) != grocerMap.end()) {
				cout << "There are " << grocerMap[input] << " " << input << " in the system." << endl;
			}
			else {
				cout << "There are no " << input << " in the system." << endl;
			}
		}
		catch (const invalid_argument& e) {
			cout << "Error: " << e.what() << std::endl;
		}
	}
}
//function to print out grocer map in histogram format
void Grocer::printGrocerHistogram() {
	//for each item in map print item and for amount of item print amount in asterisks
	for (auto itr = grocerMap.begin(); itr != grocerMap.end(); itr++) {
		cout << itr->first << " ";
		int tempInt = itr->second;
		for (int i = 0; i < tempInt; i++) {
			cout << "*";
		}
		cout << endl;
	}
}