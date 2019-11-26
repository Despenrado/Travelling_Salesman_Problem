#include "Graph.h"

void Graph::setFirstNode(int n)
{
	this->firstNode = n;
}

//void Graph::setLastNode(int n)
//{
//	this->lastNode = n;
//}

int Graph::getFirstNode()
{
	return this->firstNode;
}

//int Graph::getLastNode()
//{
//	return this->lastNode;
//}

Graph::Graph()
{
}

Graph::Graph(bool)
{
	loadFromFile();
}

Graph::Graph(int n)
{
	this->N = n;
	for (int i = 0; i < N; i++)
	{
		matrix.push_back(std::vector<int>());
		for (int i2 = 0; i2 < N; i2++) 
		{
			if (i2 != i) 
			{
				matrix[i].push_back(rand()%100);
			}
			else
			{
				matrix[i].push_back(-1);
			}
		}
	}
	/*for (int i = 0; i < N; i++)
	{
		for (int i2 = 0; i2 < N; i2++)
		{
			matrix[i][i2] = matrix[i2][i];
		}
	}*/
	this->firstNode = 0;
	//this->lastNode = N - 1;
}

int Graph::getN()
{
	return this->N;
}

std::vector<std::vector<int>> Graph::getMatrix()
{
	return this->matrix;
}

void Graph::setN(int n)
{
	this->N = n;
}

void Graph::setMatrix(std::vector<std::vector<int>> *newMatrix)
{
	this->matrix = *newMatrix;
}

std::string Graph::getFileName()
{
	std::cout << "Enter FileName:";
	std::string s;
	std::cin >> s;
	std::cout << std::endl;
	return s;
}

void Graph::loadFromFile()
{
	std::vector<std::string>* tmp = new std::vector<std::string>;
	std::ifstream fin;
	fin.open(getFileName());

	if (fin.is_open())
	{
		std::string s;
		int i2 = 0;
		if (!fin.eof())
		{
			s = "";
			fin >> s;
			tmp = My_Environment::line_Split(s, ';');
			this->N = std::stoi(tmp->at(0));
			if (tmp->size() > 1)
			{
				this->firstNode = std::stoi(tmp->at(1));
				//this->lastNode = std::stoi(tmp->at(2));
			}
			else
			{
				this->firstNode = 0;
				//this->lastNode = this->N - 1;
			}
			for (int i = 0; i < N; i++)
			{
				matrix.push_back(std::vector<int>());
			}

		}
		while (!fin.eof())
		{
			s = "";
			fin >> s;
			if (s._Equal("#"))
			{
				fin.close();
				std::cout << "successful" << std::endl;
				return;
			}
			
			if(matrix[i2].size() == N)
			{
				i2++;
			}
			if (s.size() > 0)
			{
				//std::cout << s << std::endl;
				matrix[i2].push_back(std::stoi(s));
			}
				
		}
	}
	else
	{
		std::cout << "ERROR file can't open" << std::endl;
	}


}

void Graph::printToFile()
{
	std::ofstream fout;
	fout.open(getFileName());

	fout << N << ";" << firstNode << ";\n";
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int i2 = 0; i2 < matrix[i].size(); i2++)
		{
			fout << matrix[i][i2] << " ";
		}
		fout << "\n";
	}
	fout << "#\n";
	fout.close();
	std::cout << "successful" << std::endl;
}

Graph::~Graph()
{
	matrix.~vector();
}
