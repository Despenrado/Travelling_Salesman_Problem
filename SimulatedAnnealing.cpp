#include "SimulatedAnnealing.h"
#include <corecrt_math_defines.h>
#include <cmath>

SimulatedAnnealing::SimulatedAnnealing(Graph& graph)
{
	this->graph = graph;
	this->fileName = "SimulatedAnnealing";
}

SimulatedAnnealing::SimulatedAnnealing(Graph& graph, int time, int other)
{
	this->graph = graph;
	this->fileName = "TabuSearch";
	maxTimer = time;
	tempFactor = (double)other/1000;
	//std::cout << tempFactor << std::endl;
}

void SimulatedAnnealing::realization()
{
	simAnn();
}

void SimulatedAnnealing::stop()
{
	running = false;
	std::cout << "Finnished" << std::endl
		<< "temperature = " << temperature << std::endl;
}

void SimulatedAnnealing::setAllOnZero()
{
	if (addParam.size() > 0)
	{
		tempFactor = addParam[0] / 1000;
	}
	else
	{
		if (tempFactor == 0)
		{
			tempFactor = (double)0.98;
		}
	}
	bestWay.clear();
	initializeVecror(bestWay, graph.N);
	bestWay.push_back(0);
	temperature = getWayValue(bestWay)*10;//rand() % (100) + 1;
	std::cout << "start Temperature = " << temperature << std::endl;
	tmpWay.clear();
}

std::string SimulatedAnnealing::getReport()
{
		std::string s = "[ " + vectorToString(bestWay) + " ]\n"
			+ "lenth = " + std::to_string(getWayValue(bestWay)) + "; "
			+ "Evalution = " + std::to_string(countOperation) + "; "
			+ "temperature = " + std::to_string(temperature) + "; "
			+ "time is: " + std::to_string(this->timer.getDeltataTime());
		return s;
}

void SimulatedAnnealing::simAnn()
{
	//int orderNotChanged = 0;

	tmpWay = bestWay;
	while (this->maxTimer > this->timer.getTimeFromStart())
	{

		int randNode1 = rand() % (graph.N - 1) + 1;
		int randNode2 = rand() % (graph.N - 1) + 1;
		while (randNode1 == randNode2)
		{
			randNode2 = rand() % (graph.N - 1) + 1;
		}
		std::vector<int> vec = tmpWay;
		swap(vec, getNodeIndex(vec, randNode1), getNodeIndex(vec, randNode2));
		int delta = getWayValue(vec) - getWayValue(tmpWay);
		if (delta <= 0)
		{
			tmpWay = vec;
			countOperation = this->timer.getTimeFromStart();
			//orderNotChanged = 0;
		}
		else
		{
			if ((double)100*(pow(M_E,(-(delta/temperature)))) > (double)(rand() % (100) + 1))
			{
				tmpWay = vec;
				countOperation = this->timer.getTimeFromStart();
				//orderNotChanged = 0;
			}
		}
		temperature = tempFactor * temperature;
	}
	bestWay = tmpWay;
}

void SimulatedAnnealing::simAnn2()
{
	int orderNotChanged = 100;

	tmpWay = bestWay;
	while (this->maxTimer > this->timer.getTimeFromStart())
	{
		for (int i3 = 0; i3 < sqrt(bestWay.size()) && this->maxTimer > this->timer.getTimeFromStart(); i3++)
		{
			for (int i = 1; i < bestWay.size() - 1 && this->maxTimer > this->timer.getTimeFromStart(); i++)
			{
				std::vector<int> vec = tmpWay;
				for (int i2 = 1; i2 < bestWay.size() - 1; i2++)
				{
					swap(vec, i, i2);
					if (getWayValue(vec) < getWayValue(tmpWay))
					{
						tmpWay = vec;
						orderNotChanged = 0;
						countOperation = this->timer.getTimeFromStart();
					}
					else
					{
						orderNotChanged++;
					}
					swap(vec, i, i2);
				}
			}
		}
		if (orderNotChanged > 100)
		{
			int randomCity = rand() % (graph.N - 1) + 1;
			int anotherRandomCity = rand() % (graph.N - 1) + 1;
			while (randomCity == anotherRandomCity)
			{
				anotherRandomCity = rand() % (graph.N - 1) + 1;
			}
			std::vector<int> vec = tmpWay;
			swap(vec, randomCity, anotherRandomCity);

			if (getWayValue(vec) < getWayValue(tmpWay))
			{
				tmpWay = vec;
				countOperation = this->timer.getTimeFromStart();
				orderNotChanged = 0;
			}
		}
	}
	bestWay = tmpWay;

}
