#include "BruteForce.h"

unsigned long BruteForce::calulateNumberOfPermutation(unsigned long N)
{
	if (N == 0) 
		return 1; 
	else 
		return N * calulateNumberOfPermutation(N - 1);
}

BruteForce::BruteForce(Graph& graph)
{
	this->graph = graph;
	this->fileName = "BruteForce";
	numberOfPermutation = calulateNumberOfPermutation((unsigned long)graph.N - 1);
}

void BruteForce::setAllOnZero()
{
	maxTimer = ULLONG_MAX;
	bestVal = INT_MAX;
	this->countOperation = 0;
	countCompleted = 0;
	bestWay.clear();
	tmpWay.clear();
	initializeVecror(this->tmpWay, this->graph.N);
	swap(this->tmpWay, 0, getNodeIndex(this->tmpWay, this->graph.firstNode));
	tmpWay.push_back(this->graph.firstNode);
	initializeVecror(this->bestWay, this->graph.N);
	swap(this->bestWay, 0, getNodeIndex(this->bestWay, this->graph.firstNode));
	bestWay.push_back(this->graph.firstNode);
}

void BruteForce::stop()
{ 
	running = false;
	std::cout << (long double)countCompleted / (long double)numberOfPermutation * (long double)100 << "% ways was seen. " << std::endl;
}

void BruteForce::realization()
{
	permutation(this->tmpWay, 1);
	stop();

}

void BruteForce::permutation(std::vector<int>& vec, int lf)
{
	if (running == false || maxTimer <= this->timer.getTimeFromStart())
	{
		return;
	}
	countOperation++;
	if (lf >= vec.size() - 1) {                           
		countCompleted++;
		if (getWayValue(bestWay) > getWayValue(vec))
		{
			bestWay = vec;
		}
		return;
	}


	permutation(vec, lf + 1);
	for (int i = lf+1; i < vec.size() - 1; i++)
	{
		swap(vec, lf, i);
		permutation(vec, lf + 1);
		swap(vec, lf, i);
	}
}
