#include "BranchAndBound.h"

unsigned long BranchAndBound::calulateNumberOfPermutation(unsigned long N)
{
	if (N == 0)
		return 1;
	else
		return N * calulateNumberOfPermutation(N - 1);
}

BranchAndBound::BranchAndBound(Graph& graph)
{
	this->graph = graph;
	this->fileName = "BranchAndBound";
	numberOfPermutation = calulateNumberOfPermutation((unsigned long)this->graph.N - 1);
}

void BranchAndBound::stop()
{
	running = false;
	std::cout << (long double)countCompleted / (long double)numberOfPermutation * (long double)100 << "% ways was seen. " << std::endl;
}

void BranchAndBound::setAllOnZero()
{
	this->countOperation = 0;
	this->countCompleted = 0;
	this->bestWay.clear();
	vecHeap.clear();
	heapValues.clear();
}

void BranchAndBound::realization()
{
	solvePrepare();
}

int BranchAndBound::findFirstMinInLine(std::vector<std::vector<int>> vec, int i)
{
	int min = INT_MAX;
	int number = 0;
	for (int i2 = 0; i2 < vec.size(); i2++)
	{
		if (vec[i][i2] < min && vec[i][i2] >= 0)
		{
			min = vec[i][i2];
			number = i2;
		}
	}
	return number;
}

int BranchAndBound::findFirstMinInColumn(std::vector<std::vector<int>> vec, int i)
{
	int min = INT_MAX;
	int number = 0;
	for (int i2 = 0; i2 < vec.size(); i2++)
	{
		if (vec[i2][i] < min && vec[i][i2] >= 0)
		{
			min = vec[i2][i];
			number = i2;
		}
	}
	return number;
}

int BranchAndBound::findNode(std::vector<int> vec, int node)
{
	for (int i = 0; i < vec.size(); i++)
	{
		if (node == vec[i])
			return i;
	}
	return -1;
}

int BranchAndBound::matrixCalculation(std::vector<std::vector<int>> matrix, std::vector<int> vec)
{
	int sum = 0;
	std::vector<std::vector<int>> tmpMatrix = matrix;///////////////////////////////////////// = graph.matrix
	for (int i3 = 0; i3 < vec.size() - 1; i3++) // try use: i3 = 1; i3 < vec.size(); i++
	{
		countOperation++;
		sum += tmpMatrix[vec[i3]][vec[i3 + 1]]; // vec[i3-1][i3]
		//удаление пройденного
		for (int i2 = 0; i2 < matrix.size(); i2++)
		{
			matrix[vec[i3]][i2] = -2;/////////////////////////////////////////////////////// delete this line
			matrix[i2][vec[i3 + 1]] = -2;  // [i2][i3]
		}
		matrix[vec[i3 + 1]][vec[i3]] = -2;
		//вычисление штрафа
		for (int i = 0; i < this->graph.matrix.size(); i++)
		{
			int min = matrix[i][findFirstMinInLine(matrix, i)];
			if (min < 0)
			{
				min = 0;
			}
			sum += min;
			for (int i2 = 0; i2 < matrix.size(); i2++)
			{
				if (i != i2)
					matrix[i][i2] -= min;
			}
		}
		for (int i = 0; i < this->graph.matrix.size(); i++)
		{
			int min = matrix[findFirstMinInColumn(matrix, i)][i];
			if (min < 0)
			{
				min = 0;
			}
			sum += min;
			for (int i2 = 0; i2 < matrix.size(); i2++)
			{
				if (i != i2)
					matrix[i2][i] -= min;
			}
		}
		for (int i2 = 0; i2 < matrix.size(); i2++)
		{
			matrix[vec[i3]][i2] = -2; // [vec[i3-1]][i2]
		}

	}
	
	countCompleted++;
	return downBound + sum;
}

void BranchAndBound::solvePrepare()
{
	downBound = 0;
	int currPath = 0;

	std::vector<std::vector<int>> matrix = this->graph.matrix;

	
	//рудукция строк
	for (int i = 0; i < this->graph.matrix.size(); i++)
	{
		int min = matrix[i][findFirstMinInLine(matrix, i)];
		downBound += min;
		for (int i2 = 0; i2 < matrix.size(); i2++)
		{
			if(i != i2)
				matrix[i][i2] -= min;
		}
	}
	//редукция колонок
	for (int i = 0; i < this->graph.matrix.size(); i++)
	{
		int min = matrix[findFirstMinInColumn(matrix, i)][i];
		downBound += min;
		for (int i2 = 0; i2 < matrix.size(); i2++)
		{
			if(i != i2)
				matrix[i2][i] -= min;
		}
	}
	//заполнение стога путей
	vecHeap.push_back(std::vector<int>());
	vecHeap[0].push_back(0);
	heapValues.push_back(0);
	//конец подготовки

	solveTick(matrix, currPath);
	
}

void BranchAndBound::solveTick(std::vector<std::vector<int>> matrix, int currPath)
{
	if (vecHeap[currPath].size() == (this->graph.matrix.size() + 1))
	{
		bestWay = vecHeap[currPath];
		return;
	}
	//заполнение стога путей
	bool first = true;
	std::vector<int >tmpVec = vecHeap[currPath];
	for (int i = 0; i < matrix.size(); i++)
	{
		if (findNode(vecHeap[currPath], i) < 0 || (i == this->graph.firstNode && this->graph.N == tmpVec.size()))
		{
			if (first)
			{
				vecHeap[currPath].push_back(i);
				heapValues[currPath] = matrixCalculation(matrix, vecHeap[currPath]);
				first = false;
			}
			else
			{
				vecHeap.push_back(tmpVec);
				vecHeap[vecHeap.size() - 1].push_back(i);
				heapValues.push_back(matrixCalculation(matrix, vecHeap[vecHeap.size() - 1]));
			}
		}
	}
	//нахождение минимального неполного пути
	int min = INT_MAX;
	for (int i = 0; i < heapValues.size(); i++)
	{
		if (min > heapValues[i])
		{
			min = heapValues[i];
			currPath = i;
		}
	}

	solveTick(matrix, currPath);
}

