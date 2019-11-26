#pragma once
#include <iostream>
#include <vector>
#include "Graph.h"
#include "Test.h"
#include "BruteForce.h"
#include "DynamicProg.h"
#include "BranchAndBound.h"
#include "TabuSearch.h"
#include "SimulatedAnnealing.h"

using namespace std;
class ConsoleUI
{
public:
	ConsoleUI();
	~ConsoleUI();
	void loandingProcess();
	string cinConsole();
	void printMatrix(vector<vector<int>>);
private:
	Graph graph;
	Test tests;
	void mainMenu();
	void algorithmsListMenu();
	void generationMenu();
	void graphProperties();
	void printReport(Algorithm*);
	void algorithmMenu(Algorithm*);
	void testsMenu();
	void cinTestsProperies();
};

