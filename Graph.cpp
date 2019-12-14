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
	try
	{
		std::vector<std::string>* tmp = new std::vector<std::string>;
		std::ifstream fin;
		std::string filename = getFileName();
		fin.open(filename);

		if (fin.is_open())
		{
			std::string s;
			int i2 = 0;
			if (My_Environment::line_Split(filename, '.')->at(1)._Equal("txt"))
			{
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
				}
			}
			else
			{
				if (My_Environment::line_Split(filename, '.')->at(1)._Equal("atsp"))
				{
					this->firstNode = 0;
					do
						fin >> s;
					while (s != "DIMENSION:");

					fin >> s;
					this->N = std::stoi(s);

					do
						fin >> s;
					while (s != "EDGE_WEIGHT_TYPE:");

					fin >> s;
					if (s != "EXPLICIT")
					{
						std::cout << "UNKNOWN FORMAT " << s << " +++" << std::endl;
						return;
					}

					do
						fin >> s;
					while (s != "EDGE_WEIGHT_SECTION");
				}
				else
				{
					fin.close();
					std::cout << "File type not correct" << std::endl;
					return;
				}
			}
			for (int i = 0; i < N; i++)
			{
				matrix.push_back(std::vector<int>());
			}
			int i = 0;
			while (!fin.eof())
			{
				s = "";
				fin >> s;
				if (s._Equal("#") || s._Equal("EOF"))
				{
					fin.close();
					std::cout << "successful" << std::endl;
					return;
				}

				if (matrix[i2].size() == N)
				{
					i2++;
					i = 0;
				}
				if (s.size() > 0)
				{
					//std::cout << s << std::endl;
					try
					{
						int tmpInt = std::stoi(s);
						if (i2 == i)
						{
							tmpInt = -1;
						}
						i++;
						matrix[i2].push_back(tmpInt);
					}
					catch (std::invalid_argument & e)
					{
						std::cout << "invalid_argument" << std::endl;
					}
					catch (std::out_of_range & e)
					{
						std::cout << e.what() << std::endl;
					}
				}

			}
		}
		else
		{
			std::cout << "ERROR file can't open" << std::endl;
		}
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Exception opening/reading/closing file\n";
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
