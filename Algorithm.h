#pragma once
#include <vector>
#include "Graph.h"
#include "Timer.h"
#include <string>
class Algorithm
{
public:
	

	//std::vector<std::vector<int>> getWayList();
	//std::string getAllPermutations();
	//void cleanWayList();
	void initializeVecror(std::vector<int>&, int);
	void swap(std::vector<int>&, int, int);
	int compare(std::vector<int>, std::vector<int>);
	std::string vectorToString(std::vector<int>);
	void setMaxTime();
	int getNodeIndex(std::vector<int>, int);

	int getWayValue(std::vector<int>);
	std::vector<int> getBestWay();
	void start();
	std::string getReport();
	void printToFile();

	virtual void stop()=0;
	virtual void realization()=0;
	virtual void setAllOnZero()=0;

	int bestVal;
	std::vector<int> tmpWay;
	unsigned long long countCompleted = 0;
	Graph graph;
	std::vector<int> bestWay;
	Timer timer;
	int countOperation = 0;
	std::string fileName;
	bool running = false;
	unsigned long long maxTimer = 600*1000000;
	std::vector<int> addParam;
};


