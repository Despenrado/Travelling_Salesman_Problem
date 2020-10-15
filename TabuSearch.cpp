#include "TabuSearch.h"

TabuSearch::TabuSearch(Graph& graph, int tabuListMaxSize, bool defal)
{
	this->graph = graph;
	this->tabuListMaxSize = tabuListMaxSize;
	this->fileName = "TabuSearch";
	this->def = defal;
}

TabuSearch::TabuSearch(Graph& graph, int tabuListMaxSize, int time, int defal)
{
	this->graph = graph;
	this->tabuListMaxSize = tabuListMaxSize;
	this->fileName = "TabuSearch";
	maxTimer = time;
	if (defal == 1)
	{
		this->def = false;
	}
	else
	{
		this->def = true;
	}
}

std::vector<int> TabuSearch::getBestNeighbour(std::vector<int> order)
{

	std::vector<int> nextOrder(order);
	int repeats = 0;

	for (int i = 0; i < sqrt(dimension); i++)
	{
		std::vector<int> newOrder(nextOrder);

		int randomCity = rand() % (dimension - 1) + 1;		//generujemy dwie wartoœci ró¿ne od zera oraz od siebie
		int anotherRandomCity = rand() % (dimension - 1) + 1;
		while (randomCity == anotherRandomCity)
		{
			anotherRandomCity = rand() % (dimension - 1) + 1;
		}

		swap(newOrder, randomCity, anotherRandomCity);

		if (!(tabuListMatrix[randomCity][anotherRandomCity] == 1) && getWayValue(newOrder) < getWayValue(nextOrder))
		{
			nextOrder = newOrder;
			bestChange[0] = randomCity;
			bestChange[1] = anotherRandomCity;
		}

	}
	return nextOrder;
}

void TabuSearch::realization()
{
	if (def)
	{
		tabu2();
	}
	else
	{
		tabu();
	}
}

void TabuSearch::stop()
{
	running = false;
	std::cout << "Finnished" << std::endl;
}

void TabuSearch::setAllOnZero()
{
	if (addParam.size() > 0)
	{
		tabuListMaxSize = addParam[0];
	}
	tabuListMatrix.clear();
	for (int i = 0; i < graph.N+1; i++)
	{
		tabuListMatrix.push_back(std::vector<int>());
		for (int i2 = 0; i2 < graph.N+1; i2++)
		{
			tabuListMatrix[i].push_back(0);
		}
	}
	tmpWay.clear();
	tabuList.clear();
	dimension = 0;
	bestWay.clear();
	initializeVecror(bestWay, graph.N);
	bestWay.push_back(0);
}

void TabuSearch::tabu2()
{
	int orderNotChanged = 0;

	tmpWay = bestWay;
	std::vector<int> tmpBest = tmpWay;
	while(this->maxTimer > this->timer.getTimeFromStart())
	{
		for (int i3 = 0; i3 < sqrt(bestWay.size()) && this->maxTimer > this->timer.getTimeFromStart(); i3++)
		{
			for (int i = 1; i < bestWay.size() - 1 && this->maxTimer > this->timer.getTimeFromStart(); i++)
			{
				std::vector<int> vec = tmpBest;
				for (int i2 = 1; i2 < bestWay.size() - 1; i2++)
				{
					swap(vec, i, i2);
					int tmpValue = getWayValue(vec);
					if (tabuListMatrix[i][i2] == 0 && tmpValue < getWayValue(tmpBest))
					{
						tmpBest = vec;
						bestChange[0] = i;
						bestChange[1] = i2;
						orderNotChanged = 0;
						if (tmpValue < getWayValue(tmpWay))
						{
							tmpWay = vec;
							countOperation = this->timer.getTimeFromStart();
						}
						
					}
					else
					{
						insert(bestChange[0], bestChange[1]);
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
			std::vector<int> vec = tmpBest;
			swap(vec, randomCity, anotherRandomCity);

				tmpBest = vec;
				//countOperation = this->timer.getTimeFromStart();

				orderNotChanged = 0;

				tabuList.clear();
				for (int i = 0; i < tabuListMatrix.size(); i++)
				{
					for (int i2 = 0; i2 < tabuListMatrix.size(); i2++)
					{
						tabuListMatrix[i][i2] = 0;
					}
				}
		}
	}
	bestWay = tmpWay;
}

void TabuSearch::tabu()
{

	int orderNotChanged = 0;
	countOperation = 0;
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
		//std::cout << delta << std::endl;
			//countOperation++;
		if (!(tabuListMatrix[randNode1][randNode2] == 1) && getWayValue(vec) < getWayValue(tmpWay))
		{
			tmpWay = vec;
			bestChange[0] = randNode1;
			bestChange[1] = randNode2;
			orderNotChanged = 0;
			countOperation = this->timer.getTimeFromStart();
			
		}
		else
		{
			orderNotChanged++;
			insert(bestChange[0], bestChange[1]);
		}
		//swap(vec, randNode1, randNode2);
		if (orderNotChanged >= 100)
		{
			orderNotChanged = 0;
			tabuList.clear();
			for (int i = 0; i < tabuListMatrix.size(); i++)
			{
				for (int i2 = 0; i2 < tabuListMatrix.size(); i2++)
				{
					tabuListMatrix[i][i2] = 0;
				}
			}
		}
	}
	if (getWayValue(bestWay) >= getWayValue(tmpWay)) 
	{

		bestWay = tmpWay;
	}
}

void TabuSearch::insert(int vertexA, int vertexB)
{
	Node cities;
	cities.verA = vertexA;
	cities.verB = vertexB;

	if (tabuList.size() < tabuListMaxSize)
	{
		tabuList.push_back(cities);
		tabuListMatrix[vertexA][vertexB] = 1;
	}
	else
	{
		Node cities2 = tabuList.front();
		tabuList.erase(tabuList.begin() + 1, tabuList.end());

		tabuListMatrix[cities2.verA][cities2.verB] = 0;

		tabuListMatrix[vertexA][vertexB] = 1;
		tabuList.push_back(cities);

	}
}
