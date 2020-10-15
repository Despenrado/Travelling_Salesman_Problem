#include "Genetic.h"

Genetic::Genetic(Graph& graph)
{
	this->graph = graph;
	this->fileName = "Genetic";
}

Genetic::Genetic(Graph& graph, int n, int cq, int cp, int mq, int nrq, int mt)
{
	this->graph = graph;
	this->fileName = "Genetic";
	populationMaxSize = n;
	crosoverQuantity = cq;
	crosoverPoint = cp;
	mutationQuantity = mq;
	newRandQuantity = nrq;
	muetationType = mt;
}

void Genetic::geneticEngine1()
{
	for (int i = 0; i < crosoverQuantity; i++)
	{
		int randNode1 = rand() % (populationMaxSize - 1) + 1;
		int randNode2 = rand() % (populationMaxSize - 1) + 1;
		while (randNode1 == randNode2)
		{
			randNode2 = rand() % (populationMaxSize - 1) + 1;
		}
		population.push_back(crosover(population[randNode1], population[randNode2]));
	}
	for (int i = 0; i < mutationQuantity; i++)
	{
		int randNode1 = rand() % (populationMaxSize - 1) + 1;
		population.push_back(mutate(population[randNode1]));
	}
	for (int i = 0; i < newRandQuantity; i++)
	{
		population.push_back(newRandVector(graph.N));
	}
	if (this->maxTimer <= this->timer.getTimeFromStart())
	{
		populationMaxSize = 1;
	}
	naturalSelection();
}

void Genetic::geneticEngine2()
{
	for (int i = 0; i < populationMaxSize; i++)
	{
		if (rand() % 100 + 1 <= crosoverQuantity)
		{
			int randNode2 = rand() % (populationMaxSize - 1) + 1;
			while (i == randNode2)
			{
				randNode2 = rand() % (populationMaxSize - 1) + 1;
			}
			population.push_back(crosover(population[i], population[randNode2]));
		}
	}
	for (int i = 0; i < population.size(); i++)
	{
		if (rand() % 100 + 1 <= mutationQuantity)
		{
			int randNode2 = rand() % (populationMaxSize - 1) + 1;
			if (muetationType == 1)
			{
				population.push_back(mutate(population[i]));
			}
			if (muetationType == 2)
			{
				population.push_back(mutate2(population[i]));
			}
			if (muetationType == 3)
			{
				population.push_back(mutate3(population[i]));
			}
		}
	}
	if (this->maxTimer <= this->timer.getTimeFromStart())
	{
		populationMaxSize = 1;
	}
	naturalSelection();
}

int Genetic::fitness(const std::vector<int>& vec)
{
	return getWayValue(vec);
}

std::vector<int> Genetic::mutate(const std::vector<int>& oldVec)
{
	std::vector<int> vec = oldVec;
	int startFirstSection = 3;
	do
	{
		startFirstSection = rand() % (vec.size() - 2) + 1;
	} while (startFirstSection >= vec.size() - 3);
	int finishFirstSection = 5;
	do
	{
		finishFirstSection = rand() % (vec.size() - 2) + 1;
	} while (finishFirstSection >= vec.size() - 2 || finishFirstSection <= startFirstSection);

	int startSecondSection = 7;
	do
	{
		startSecondSection = rand() % (vec.size() - 2) + 1;
	} while (startSecondSection >= vec.size() - 2 || startSecondSection < finishFirstSection);
	int finishSecondSection = 9;
	do
	{
		finishSecondSection = rand() % (vec.size() - 2) + 1;
	} while (finishSecondSection >= vec.size() - 1 || finishSecondSection <= startSecondSection);
	//std::cout << startFirstSection << " " << finishFirstSection << " " << startSecondSection << " " << finishSecondSection << std::endl;
	//std::vector<int> tmp1(vec.begin(), vec.begin() + startFirstSection);
	//std::vector<int> tmp2(vec.begin() + startFirstSection, vec.begin() + finishFirstSection);
	//std::vector<int> tmp3(vec.begin() + finishFirstSection, vec.begin() + startSecondSection);
	//std::vector<int> tmp4(vec.begin() + startSecondSection, vec.begin() + finishSecondSection);
	//std::vector<int> tmp5(vec.begin() + finishSecondSection, vec.begin() + vec.size());
	for (int i = startFirstSection; i < finishFirstSection; i++)
	{
		vec.insert(vec.begin()+finishSecondSection, oldVec.at(i));
	}
	vec.erase(vec.begin() + startSecondSection, vec.begin() + finishSecondSection);
	for (int i = startSecondSection; i < finishSecondSection; i++)
	{
		vec.insert(vec.begin() + finishFirstSection, oldVec.at(i));
	}
	vec.erase(vec.begin() + startFirstSection, vec.begin() + finishFirstSection);
	//bestWay = vec;
	return vec;
}

std::vector<int> Genetic::mutate2(const std::vector<int>& vec)//transpozycja
{
	std::vector<int> newVec = vec;
	swap(newVec, rand() % (vec.size() - 2) + 1, rand() % (vec.size() - 2) + 1);
	return newVec;
}

std::vector<int> Genetic::mutate3(const std::vector<int>& vec)
{
	std::vector<int> newVec = vec;
	int startFirstSection = 3;
	do
	{
		startFirstSection = rand() % (vec.size() - 2) + 1;
	} while (startFirstSection >= vec.size() - 3);
	int finishFirstSection = 5;
	do
	{
		finishFirstSection = rand() % (vec.size() - 2) + 1;
	} while (finishFirstSection >= newVec.size() - 1 || finishFirstSection <= startFirstSection);
	for (int i = startFirstSection; i < finishFirstSection; i++)
	{
		newVec.insert(newVec.begin() + finishFirstSection, vec.at(i));
	}
	newVec.erase(newVec.begin() + startFirstSection, newVec.begin() + finishFirstSection);
	return newVec;
}

std::vector<int> Genetic::crosover(const std::vector<int>& vec1, const std::vector<int>& vec2)
{
	std::vector<int> newChild = vec1;
	for (int i = crosoverPoint; i < vec2.size()-1; i++)
	{
		newChild.erase(newChild.begin()+ getNodeIndex(newChild, vec2.at(i)));
		newChild.insert(newChild.begin() + (newChild.size() - 1), vec2.at(i));
	}
	return newChild;
}

void Genetic::naturalSelection()
{
	for (int i = populationMaxSize; i < population.size(); i++)
	{
		individualsWays.push_back(fitness(population[i]));
	}
	if (populationMaxSize <= 1) 
	{
		int minIdx = 0;
		for (int i = 0; i < population.size(); i++)
		{
			if (individualsWays[minIdx] > individualsWays[i])
			{
				minIdx = i;
			}
		}
		return;
	}
	while (population.size() > populationMaxSize)
	{
		int maxIdx = 0;
		for (int i = 0; i < population.size(); i++)
		{
			if (individualsWays[maxIdx] < individualsWays[i])
			{
				maxIdx = i;
			}
		}
		population.erase(population.begin()+maxIdx);
		individualsWays.erase(individualsWays.begin() + maxIdx);
	}
}

std::vector<int> Genetic::newRandVector(int size)
{
	std::map<int, int> tmpMap;
	for (int i = 1; i < size; i++)
	{
		if (i != graph.firstNode)
		{
			int randINT = rand();
			while (tmpMap[randINT] != 0)
			{
				randINT = rand();
			}
			tmpMap[randINT] = i;
		}
	}
	std::vector<int> vec;
	vec.push_back(graph.firstNode);
	std::map<int, int>::iterator it;
	for (it = tmpMap.begin(); it != tmpMap.end(); it++)
	{
		vec.push_back(it->second);   // string's value 
	}
	vec.push_back(graph.firstNode);
	return vec;
}

void Genetic::realization()
{
	int tmp = populationMaxSize;
	while (populationMaxSize > 1)
	{
		geneticEngine2();
	}
	populationMaxSize = tmp;
	bestWay = population[0];
}

void Genetic::setAllOnZero()
{
	if (addParam.size() >= 5)
	{
		populationMaxSize = addParam[0];
		crosoverQuantity = addParam[1];
		crosoverPoint = addParam[2];
		mutationQuantity = addParam[3];
		newRandQuantity = addParam[4];
		muetationType = addParam[5];
	}
	tmpWay.clear();
	bestWay.clear();
	population.clear();
	individualsWays.clear();
	initializeVecror(bestWay, graph.N);
	bestWay.push_back(0);
	population.push_back(bestWay);
	individualsWays.push_back(fitness(bestWay));
	for (int i = 0; i < populationMaxSize - 1; i++)
	{
		population.push_back(newRandVector(graph.N));
		individualsWays.push_back(fitness(population[i]));
	}
}

void Genetic::stop()
{
}
