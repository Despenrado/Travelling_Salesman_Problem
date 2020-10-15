#pragma once
#include <map>
#include "Algorithm.h"
class Genetic : public Algorithm
{
public:
	std::vector<std::vector<int>> population;
	int populationMaxSize = 10;
	int crosoverQuantity = 10;
	int mutationQuantity = 5;
	int newRandQuantity = 4;
	int crosoverPoint = 8;
	int muetationType = 0;
	std::vector<int> individualsWays;


	Genetic(Graph&);
	Genetic(Graph&, int, int, int, int, int, int);
	void geneticEngine1();
	void geneticEngine2();
	int fitness(const std::vector<int>&);
	std::vector<int> mutate(const std::vector<int>&);
	std::vector<int> mutate2(const std::vector<int>&);
	std::vector<int> mutate3(const std::vector<int>&);
	std::vector<int> crosover(const std::vector<int>&, const std::vector<int>&);
	void naturalSelection();
	std::vector<int> newRandVector(int);
	void realization();
	void setAllOnZero();
	void stop();

};
