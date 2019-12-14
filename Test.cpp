#include "Test.h"

Test::Test()
{
}

void Test::algorithmThread()
{
	//Algorithm* algorithm;
	//Algorithm* algorithm1;
	//Algorithm* algorithm2;
	for (int i = 0; i < numRepeat; i++)
	{
		Algorithm *algorithm = generateAlgorithm();
		algorithm->start();
		vecResults.push_back(algorithm->getReport());
		std::cout << algorithm->getReport() << std::endl;
		timeVec.push_back(algorithm->timer.getDeltataTime());
		delete algorithm;
		/*Graph graph(5);
		algorithm1 = new BruteForce(&graph);
		algorithm1->start();
		vecResults.push_back(algorithm1->getReport());
		delete algorithm1;
		algorithm2 = new BranchAndBound(&graph);
		algorithm2->start();
		vecResults.push_back(algorithm2->getReport());
		delete algorithm2;*/
	}
}

Algorithm* Test::generateAlgorithm()
{
	if (numNodes > 0)
	{
		switch (algorithmType)
		{
		case 1: {
			return new BruteForce(*generateGraph(numNodes));
			break;
		}case 2: {
			return new BranchAndBound(*generateGraph(numNodes));;
			break;
		}case 3: {
			return new TabuSearch(*generateGraph(numNodes), param[1], param[0], param[2]);
			break;
		}case 4: {
			return new SimulatedAnnealing(*generateGraph(numNodes), param[0], param[1]);
			break;
		}case 5: {

			break;
		}
		default:
			break;
		}
	}
	else
	{
		switch (algorithmType)
		{
		case 1: {
			return new BruteForce(*graph);
			break;
		}case 2: {
			return new BranchAndBound(*graph);;
			break;
		}case 3: {
			return new TabuSearch(*graph, param[1], param[0], param[2]);
			break;
		}case 4: {
			return new SimulatedAnnealing(*graph, param[0], param[1]);
			break;
		}case 5: {

			break;
		}
		default:
			break;
		}
	}
	
	return nullptr;
}

Graph* Test::generateGraph(int n)
{
	return new Graph(n);
}

void Test::printResultsToFile()
{
		std::ofstream fout;
		fout.open(std::to_string(algorithmType) + "_" + std::to_string(numRepeat) + "_" + std::to_string(numNodes) + ".txt");

		
		for (int i = 0; i < vecResults.size(); i++)
		{
			fout << vecResults[i] << "\n";// << "#\n";
		}
		fout.close();
		//std::cout << "printToFileResults: successful" << std::endl;
}

void Test::clear()
{
	vecResults.clear();
	timeVec.clear();
}

long double Test::getAVGTime()
{
	long double tmp = 0;
	for (int i = 0; i < timeVec.size(); i++)
	{
		tmp += timeVec[i];
	}
	return tmp/numRepeat;
}

