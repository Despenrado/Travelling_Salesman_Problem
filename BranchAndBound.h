#pragma once
#include "Algorithm.h"
class BranchAndBound : public Algorithm
{
public:
	unsigned long long numberOfPermutation;
	unsigned long long countCompleted = 0;
	std::vector<std::vector<int>> vecHeap;
	std::vector<int> heapValues;
	int downBound;

	unsigned long calulateNumberOfPermutation(unsigned long);
	BranchAndBound(Graph&);

	void stop() override;
	void setAllOnZero() override;
	void realization() override;
	int findFirstMinInLine(std::vector<std::vector<int>>, int);
	int findFirstMinInColumn(std::vector<std::vector<int>>, int);
	int findNode(std::vector<int>, int);
	int matrixCalculation(std::vector<std::vector<int>>, std::vector<int>);

	void solvePrepare();
	void solveTick(std::vector<std::vector<int>>, int);
};

