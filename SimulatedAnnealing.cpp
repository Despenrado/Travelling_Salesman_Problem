#include "SimulatedAnnealing.h"
#include <corecrt_math_defines.h>
#include <cmath>

SimulatedAnnealing::SimulatedAnnealing(Graph& graph)
{
	this->graph = graph;
	this->fileName = "SimulatedAnnealing";
}

void SimulatedAnnealing::realization()
{
	simAnn();
}

void SimulatedAnnealing::stop()
{
	running = false;
	std::cout << "Finnished" << std::endl;
}

void SimulatedAnnealing::setAllOnZero()
{
	tempFactor = (double)rand() / ((double)RAND_MAX + 1);
	temperature = rand() % (100) + 1;

	bestWay.clear();
	initializeVecror(bestWay, graph.N);
	bestWay.push_back(0);
	tmpWay.clear();
}

void SimulatedAnnealing::simAnn()
{
	int orderNotChanged = 0;

	tmpWay = bestWay;
	do
	{
		for (int i3 = 0; i3 < sqrt(bestWay.size()); i3++)
		{
			for (int i = 1; i < bestWay.size() - 1; i++)
			{
				for (int i2 = 1; i2 < bestWay.size() - 1; i2++)
				{
					int randomCity = rand() % (graph.N - 1) + 1;		//generujemy dwie wartoœci ró¿ne od zera oraz od siebie
					int anotherRandomCity = rand() % (graph.N - 1) + 1;
					while (randomCity == anotherRandomCity)
					{
						anotherRandomCity = rand() % (graph.N - 1) + 1;
					}
					std::vector<int> vec = tmpWay;
					swap(vec, randomCity, anotherRandomCity);
					int delta = getWayValue(vec) - getWayValue(tmpWay);
					if (delta <= 0)
					{
						tmpWay = vec;
						orderNotChanged = 0;
					}
					else
					{
						if ((double)100*(pow(M_E,(-(delta/temperature)))) > (double)(rand() % (100) + 1))
						{
							tmpWay = vec;
							orderNotChanged = 0;
						}
						else
						{
							orderNotChanged++;
						}
					}
					temperature = tempFactor * temperature;
				}
			}
		}
	} while (getWayValue(bestWay) < getWayValue(tmpWay) && orderNotChanged < 100);
	bestWay = tmpWay;
}
