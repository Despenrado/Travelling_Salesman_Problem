#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>


class My_Environment
{
public:
	My_Environment() {};
	~My_Environment() {};

	//split string 's' on 'delimiter' and return
	static std::vector<std::string>* line_Split(std::string& s, char delimiter)
	{
		std::vector<std::string>* tokens = new std::vector<std::string>;
		std::string token;
		std::istringstream streamS(s);
		while (std::getline(streamS, token, delimiter))
		{
			tokens->push_back(token);
		}
		return tokens;
	};


};

