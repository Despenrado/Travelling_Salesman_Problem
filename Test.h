#pragma once
#include "Algorithm.h"
#include <iostream>
#include <string>
#include <vector>
#include "Graph.h"
#include "BruteForce.h"
#include "DynamicProg.h"
#include "BranchAndBound.h"
#include "TabuSearch.h"
#include "SimulatedAnnealing.h"
class Test
{
public:
	Test();
	
	void algorithmThread();
	Algorithm* generateAlgorithm(); //на основе номера алгоритма выбирается алгоритм
	Graph* generateGraph(int);
	void printResultsToFile();
	void clear();
	long double getAVGTime();

	int numRepeat;
	int numNodes;
	std::vector<unsigned long long> timeVec;
	std::vector<std::string> vecResults;
	int algorithmType; //1 - bruteforce, 2 - , 3 - , 4 - , 5 - 
};

