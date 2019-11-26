#include "TabuSearch.h"

TabuSearch::TabuSearch(Graph& graph, int tabuListMaxSize)
{
	this->graph = graph;
	this->tabuListMaxSize = tabuListMaxSize;
	this->fileName = "TabuSearch";
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
	tabu();
}

void TabuSearch::stop()
{
	running = false;
	std::cout << "Finnished" << std::endl;
}

void TabuSearch::setAllOnZero()
{
	tabuListMatrix.clear();
	for (int i = 0; i < graph.N+1; i++)
	{
		tabuListMatrix.push_back(std::vector<int>());
		for (int i2 = 0; i2 < graph.N+1; i2++)
		{
			tabuListMatrix[i].push_back(0);
		}
	}
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
	do
	{
		for (int i3 = 0; i3 < sqrt(bestWay.size()); i3++)
		{
			for (int i = 1; i < bestWay.size() - 1; i++)
			{
				std::vector<int> vec = tmpWay;
				for (int i2 = 1; i2 < bestWay.size() - 1; i2++)
				{
					swap(vec, i, i2);
					if (tabuListMatrix[i][i2] == 0 && getWayValue(vec) < getWayValue(tmpWay))
					{
						tmpWay = vec;
						bestChange[0] = i;
						bestChange[1] = i2;
					}
					else
					{
						insert(bestChange[0], bestChange[1]);
					}
					swap(vec, i, i2);
				}
			}
			int randomCity = rand() % (graph.N - 1) + 1;		//generujemy dwie wartoœci ró¿ne od zera oraz od siebie
			int anotherRandomCity = rand() % (graph.N - 1) + 1;
			while (randomCity == anotherRandomCity)
			{
				anotherRandomCity = rand() % (graph.N - 1) + 1;
			}
			std::vector<int> vec = tmpWay;
			swap(vec, randomCity, anotherRandomCity);

			if (!(tabuListMatrix[randomCity][anotherRandomCity] == 1) && getWayValue(vec) < getWayValue(tmpWay))
			{
				tmpWay = vec;
				bestChange[0] = randomCity;
				bestChange[1] = anotherRandomCity;
			}
		}
	} while (getWayValue(bestWay) < getWayValue(tmpWay));
	bestWay = tmpWay;
}

void TabuSearch::tabu()
{

	int orderNotChanged = 0;

	tmpWay = bestWay;
	do
	{
		for (int i3 = 0; i3 < sqrt(bestWay.size()); i3++)
		{
			for (int i = 1; i < bestWay.size() - 1; i++)
			{
				std::vector<int> vec = tmpWay;
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

					if (!(tabuListMatrix[randomCity][anotherRandomCity] == 1) && getWayValue(vec) < getWayValue(tmpWay))
					{
						tmpWay = vec;
						bestChange[0] = randomCity;
						bestChange[1] = anotherRandomCity;
						orderNotChanged = 0;
					}
					else
					{
						orderNotChanged++;
						insert(bestChange[0], bestChange[1]);
					}
					swap(vec, randomCity, anotherRandomCity);
				}
			}
			int randomCity = rand() % (graph.N - 1) + 1;		//generujemy dwie wartoœci ró¿ne od zera oraz od siebie
			int anotherRandomCity = rand() % (graph.N - 1) + 1;
			while (randomCity == anotherRandomCity)
			{
				anotherRandomCity = rand() % (graph.N - 1) + 1;
			}
			std::vector<int> vec = tmpWay;
			swap(vec, randomCity, anotherRandomCity);

			if (!(tabuListMatrix[randomCity][anotherRandomCity] == 1) && getWayValue(vec) < getWayValue(tmpWay))
			{
				tmpWay = vec;
				bestChange[0] = randomCity;
				bestChange[1] = anotherRandomCity;
			}
		}
	} while (getWayValue(bestWay) < getWayValue(tmpWay) && orderNotChanged < 100);
	bestWay = tmpWay;
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
