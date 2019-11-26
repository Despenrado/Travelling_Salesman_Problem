#include "Algorithm.h"




void Algorithm::initializeVecror(std::vector<int> &vec, int n)
{
	for (int i = 0; i < n; i++)
	{
		vec.push_back(i);
	}
}

void Algorithm::start()
{
	setAllOnZero();
	running = true;
	timer.startTimer();
	realization();
	timer.stopTimer();
	stop();
}


void Algorithm::swap(std::vector<int>& vec, int n1, int n2)
{
	int tmp = vec[n1];
	vec[n1] = vec[n2];
	vec[n2] = tmp;;
}

std::vector<int> Algorithm::getBestWay()
{
	return this->bestWay;
}

std::string Algorithm::vectorToString(std::vector<int> vec)
{
	std::string str = "";
	for (unsigned int i2 = 0; i2 < vec.size(); i2++)
	{
		str += std::to_string(vec[i2]) + " ";
	}
	return str;
}

std::string Algorithm::getReport()
{
	std::string s =  "[ " + vectorToString(bestWay) + " ]\n"
		+ "lenth = " + std::to_string(getWayValue(bestWay)) + "; "
		+ "Evalution = " + std::to_string(countOperation) + "; "
		+ "time is: " + std::to_string(this->timer.getDeltataTime());
	return s;
}

void Algorithm::setMaxTime()
{
	std::cout << "Enter max time" << std::endl << "$:";
	std::string s;
	std::cin >> s;
	maxTimer = std::stoi(s);
}

int Algorithm::getNodeIndex(std::vector<int> vec, int n)
{
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] == n)
		{
			return i;
		}
	}
	return 0;
}

int Algorithm::compare(std::vector<int> vec1, std::vector<int> vec2)
{
	return getWayValue(vec1) - getWayValue(vec2);
}

void Algorithm::printToFile()
{
	std::ofstream fout;
	fout.open(fileName + ".txt");

	fout << "[ " << vectorToString(bestWay) << " ]\n"
		<< "lenth = " << getWayValue(bestWay) << "; "
		<< "Evalution = " << std::to_string(countOperation) << "; "
		<< "time is: " << std::to_string(this->timer.getDeltataTime()) << "\n";
	fout << "#\n";
	fout.close();
}

int Algorithm::getWayValue(std::vector<int> vec)
{
	int value = 0;
	for (unsigned int i = 0; i < vec.size() - 1; i++)
	{
		value += graph.matrix[vec[i]][vec[i + 1]];
	}
	return value;
}
