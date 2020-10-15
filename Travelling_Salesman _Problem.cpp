// Travelling_Salesman _Problem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#define _CRTDBG_MAP_ALLOC 
//#include <stdlib.h>
//#include <crtdbg.h>
#include <iostream>
#include "ConsoleUI.h"
#include "Algorithm.h"
#include "BruteForce1.h"
#include "BranchAndBound.h"
//S#include "BruteForce1.h"
int main()
{
	std::cout <<
		std::endl << "######################################################################################################################" <<
		std::endl << "##==================================================================================================================##" <<
		std::endl << "##=================================            PEA      projekt             ========================================##" <<
		std::endl << "##=================================            Nikita  Stepanenko           ========================================##" <<
		std::endl << "##=================================            Nr. albomu: 245816           ========================================##" <<
		std::endl << "##==================================================================================================================##" <<
		std::endl << "######################################################################################################################" <<
		std::endl << "Program is running" << std::endl << std::endl << std::endl;
	srand(time(0));
	//std::cout << (double)1/RAND_MAX << endl;
	ConsoleUI *ui = new ConsoleUI();
	delete ui;

	/*Graph g(12);
	BnB bab(g);
	bab.start();
	std::cout << bab.getReport();*/
	//std::cout << _CrtDumpMemoryLeaks() << std::endl;
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
