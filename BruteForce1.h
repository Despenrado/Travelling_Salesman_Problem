#pragma once
#include <iostream>
#include <vector>
#include "Graph.h"
#include "Timer.h"


using namespace std;

class BruteForce1 
{
public:
	
	vector<int> najlepsza_droga;
	vector<int> poczatkowa_droga;
	int distance(vector<int>);
	void pull();
	void perm(vector<int>&, int);
	void swap(vector<int>&, int, int);
	void setAllNull();
	void realizacja();
	unsigned long long countOfPerm = 0;
	unsigned long long numOfPerm;
	
	unsigned long long maxTime;
	unsigned long long fact(int);
	int size;


	Graph graph;
	Timer time;
	BruteForce1(Graph&);

	




	

};

