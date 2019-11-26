#pragma once
#include "Algorithm.h"
class BruteForce : public Algorithm
{
public:

	unsigned long numberOfPermutation;
	unsigned long calulateNumberOfPermutation(unsigned long);
	
	
	BruteForce(Graph&);

	void setAllOnZero()override;
	void stop() override;
	void realization() override;
	void permutation(std::vector<int>&, int);
};

