#pragma once
#include<iostream>
#include<string>
#include<map>
#include<fstream>
#include <cstdlib>
using namespace std;
class Grocer
{
	public:
		Grocer();
		Grocer(string inputFileName, string outputFileName);
		void setInputFileName(string fileName);
		void setOutputFileName(string fileName);
		void readFile();
		void writeFile();
		void printGrocerMap();
		void printMenu();
		int getMenuOption();
		void executeMenuOption(int choice);
		void searchForItem();
		void run();
		void printGrocerHistogram();

	private:
		map<string, int> grocerMap;
		string inputFileName;
		string outputFileName;
};

