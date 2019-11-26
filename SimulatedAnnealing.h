#pragma once
#include "Algorithm.h"
#include <cmath>
class SimulatedAnnealing :
	public Algorithm
{
public:
	double temperature;
	double tempFactor;
	
	SimulatedAnnealing(Graph&);
	void realization() override;
	void stop() override;
	void setAllOnZero() override;
	void simAnn();
};

