#pragma once
#include "Algorithm.h"
#include <cmath>
class SimulatedAnnealing :
	public Algorithm
{
public:
	double temperature;
	double tempFactor = 0;
	
	SimulatedAnnealing(Graph&);
	SimulatedAnnealing(Graph&, int, int);
	void realization() override;
	void stop() override;
	void setAllOnZero() override;
	std::string getReport();
	void simAnn();
	void simAnn2();
};

