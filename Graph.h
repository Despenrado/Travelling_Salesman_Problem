#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include "My_Environment.h"
class Graph
{
public:
	int N;
	std::vector<std::vector<int>> matrix;
	int firstNode;
	//int lastNode;
	void setFirstNode(int);
	//void setLastNode(int);
	int getFirstNode();
	//int getLastNode();
	Graph();
	Graph(bool);
	Graph(int);
	int getN();
	std::vector<std::vector<int>> getMatrix();
	void setN(int);
	void setMatrix(std::vector<std::vector<int>>*);

	std::string getFileName();
	void loadFromFile();
	void printToFile();
};

