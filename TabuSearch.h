#pragma once
#include "Algorithm.h"
class TabuSearch : public Algorithm
{
public:
	struct Node
	{
		int verA;
		int verB;
	};
	std::vector<std::vector<int>> tabuListMatrix;
	std::vector<Node> tabuList;
	int dimension;
	int tabuListMaxSize;
	int bestChange[2];
	TabuSearch(Graph&, int);
	std::vector<int> getBestNeighbour(std::vector<int>);
	void realization() override;
	void stop() override;
	void setAllOnZero() override;
	void tabu2();
	void tabu();
	void insert(int, int);
};

