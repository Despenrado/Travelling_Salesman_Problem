#include "ConsoleUI.h"

ConsoleUI::ConsoleUI()
{
	mainMenu();
}

void ConsoleUI::loandingProcess()
{
}

string ConsoleUI::cinConsole()
{
	cout << "$:";
	string s;
	cin >> s;
	return s;
}

void ConsoleUI::printMatrix(vector<vector<int>> vec)
{
	cout << "\t\t";
	for (int i = 0; i < vec.size(); i++)
	{
		cout << i << "\t";
	}
		cout << endl << "___________________________________________________________________________________________________________________" << endl;
	for (size_t i = 0; i < vec.size(); i++)
	{
		cout << i << "\t|\t";
		for (size_t i2 = 0; i2 < vec[i].size(); i2++)
		{
			cout << vec[i][i2] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

void ConsoleUI::mainMenu()
{
	cout << "1 - Genrate Graph" << endl
		<< "2 - Load From File" << endl
		<< "3 - Save To File" << endl
		<< "4 - Show Graph" << endl
		<< "5 - Algorithms" << endl
		<< "6 - Tests" << endl
		<< "0 - Exit" << endl;
	string s = cinConsole();
	if (s._Equal("1"))
	{
		generationMenu();
	}
	if (s._Equal("2"))
	{
		graph = Graph(true);
	}
	if (s._Equal("4"))
	{
		printMatrix(graph.getMatrix());
	}
	if (s._Equal("5"))
	{
		algorithmsListMenu();
	}
	if (s._Equal("3"))
	{
		graph.printToFile();
	}
	if (s._Equal("6"))
	{
		cinTestsProperies();
		testsMenu();
	}
	if (s._Equal("0"))
	{
			exit(0);
	}
	if (!s._Equal("0") && !s._Equal("1") && !s._Equal("2") && !s._Equal("3") && !s._Equal("4") && !s._Equal("5") && !s._Equal("6"))
	{
		cout << "	Wrong value!" << endl;
	}
	mainMenu();
}

void ConsoleUI::algorithmsListMenu()
{
	cout << "Algorithm Menu" << endl
		<< "1 - Brure Force" << endl
		<< "2 - Branch And Bound" << endl
		<< "3 - Tabu Search" << endl
		<< "4 - Simulated Annealing" << endl
		<< "0 - Go Back" << endl;
	string s = cinConsole();
	if (s._Equal("1"))
	{
		algorithmMenu(new BruteForce(graph));
	}
	if (s._Equal("3"))
	{
		//cout << "Enter Number" << endl;
		//s = cinConsole();
		algorithmMenu(new TabuSearch(graph, 8));
	}
	if (s._Equal("2"))
	{
		algorithmMenu(new BranchAndBound(graph));
	}
	if (s._Equal("4"))
	{
		algorithmMenu(new SimulatedAnnealing(graph));
	}
	if (s._Equal("0"))
	{
		return;
	}
	if (!s._Equal("0") && !s._Equal("1") && !s._Equal("2") && !s._Equal("3") && !s._Equal("4"))
	{
		cout << "	Wrong value!" << endl;
	}

	algorithmsListMenu();
}

void ConsoleUI::generationMenu()
{
	cout << "Enter number of points" << endl;
	graph = (atoi(cinConsole().c_str()));
	cout << "Enter First Node" << endl;
	graph.setFirstNode(atoi(cinConsole().c_str()));
	/*cout << "Enter Last Node" << endl;
	graph->setLastNode(atoi(cinConsole().c_str()));*/
}

void ConsoleUI::printReport(Algorithm* alg)
{
	std::cout << alg->fileName << " finished" << std::endl
		<< "Best Way is:" << std::endl
		<< "[ " << alg->vectorToString(alg->bestWay) << " ]" << std::endl
		<< "lenth = " << alg->getWayValue(alg->bestWay) << std::endl
		<< "Evalution = " << std::to_string(alg->countOperation) << std::endl
		<< "time is: " << std::to_string(alg->timer.getDeltataTime()) << std::endl;
}

void ConsoleUI::algorithmMenu(Algorithm* alg)
{

		std::cout << std::endl << alg->fileName << std::endl
			<< "1 - Start" << std::endl
			<< "2 - Get best Way" << std::endl
			<< "3 - Get time" << std::endl
			<< "4 - Frint To File Results" << std::endl
			<< "5 - Set Max Time" << std::endl
			<< "0 - Go Back" << std::endl;
		std::cout << "$:";
		std::string s;
		std::cin >> s;
		if (s._Equal("1"))
		{
			alg->start();
			printReport(alg);
			alg->printToFile();
		}
		if (s._Equal("2"))
		{
			std::cout << alg->vectorToString(alg->getBestWay()) << std::endl;
		}
		if (s._Equal("3"))
		{
			std::cout << "Evalution = " << std::to_string(alg->countOperation) << std::endl << std::to_string(alg->timer.getDeltataTime()) << std::endl;
		}
		if (s._Equal("4"))
		{
			alg->printToFile();
		}
		if (s._Equal("5"))
		{
			alg->maxTimer = stoi(cinConsole());
		}
		if (s._Equal("0"))
		{
			delete alg;
			return;
		}
		if (!s._Equal("0") && !s._Equal("1") && !s._Equal("2") && !s._Equal("3") && !s._Equal("4") && !s._Equal("5"))
		{
			std::cout << "	Wrong value!" << std::endl;
		}

		algorithmMenu(alg);

}

void ConsoleUI::testsMenu()
{
	std::cout << std::endl << "Test Menu" << std::endl
		<< "1 - Brure Force" << endl
		<< "2 - Branch And Bound" << endl
		<< "3 - Tabu Search" << endl
		<< "4 - Simulated Annealing" << endl
		<< "5 - " << std::endl
		<< "0 - Go Back" << std::endl;
	std::cout << "$:";
	std::string s;
	std::cin >> s;
	if (s._Equal("1"))
	{
		tests.algorithmType = 1;
		tests.algorithmThread();
		tests.printResultsToFile();
	}
	if (s._Equal("2"))
	{
		tests.algorithmType = 2;
		tests.algorithmThread();
		tests.printResultsToFile();
	}
	if (s._Equal("3"))
	{
		tests.algorithmType = 3;
		tests.algorithmThread();
		tests.printResultsToFile();
	}
	if (s._Equal("4"))
	{
		tests.algorithmType = 4;
		tests.algorithmThread();
		tests.printResultsToFile();
	}
	if (s._Equal("5"))
	{

	}
	if (s._Equal("0"))
	{
		return;
	}
	if (!s._Equal("0") && !s._Equal("1") && !s._Equal("2") && !s._Equal("3") && !s._Equal("4") && !s._Equal("5"))
	{
		std::cout << "	Wrong value!" << std::endl;
	}
	cout << "AVG time = " << tests.getAVGTime() << endl;
	tests.clear();
	testsMenu();
}

void ConsoleUI::cinTestsProperies()
{
	std::cout << "Enter number of repeat" << std::endl << "$:";
	std::string s;
	std::cin >> s;
	tests.numRepeat = std::stoi(s);
	std::cout << "Enter number Nodes" << std::endl << "$:";
	std::cin >> s;
	tests.numNodes = std::stoi(s);
}
