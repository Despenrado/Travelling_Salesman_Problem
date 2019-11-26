//#include "DynamicProg.h"
//
//DynamicProg::DynamicProg(Graph* graph)
//{
//	this->graph = graph;
//	this->fileName = "DymamicProg";
//}
//
//void DynamicProg::setAllOnZero()
//{
//	wayLenth = 0;
//	this->countOperation = 0;
//	countCompleted = 0;
//	//wayList.clear();
//	bestWay.clear();
//	//completed.clear();
//	//for (int i = 0; i < graph->getN(); i++)
//	//{
//	//	bestWay.push_back(i);
//	//}
//	//tmpWay.clear();
//	vecPerm.clear();
//	for (int i = 0; i < (1 << graph->getN()); i++)
//	{
//		vecPerm.push_back(std::vector<int>());
//		for (int i2 = 0; i2 < graph->getN(); i2++)
//		{
//			vecPerm[i].push_back(INT_MAX);
//		}
//	}
//	vecPerm[0][graph->getFirstNode()] = 0;
//}
//
//void DynamicProg::stop()
//{
//	std::cout << "stop.." << std::endl;
//	running = false;
//}
//
//void DynamicProg::realization()
//{
//	solve();
//	stop();
//	std::cout << countCompleted / graph->getN() * 100 << "% ";
//}
//
//void DynamicProg::solve()
//{
//	int state = 1 << graph->getFirstNode();
//	std::vector<std::vector<int>> memo;
//	std::vector<std::vector<int>> prev;
//	for (int i = 0; i < graph->getN(); i++)
//	{
//		prev.push_back(std::vector<int>());
//		memo.push_back(std::vector<int>());
//		for (int i2 = 0; i2 < (1 << graph->getN()); i2++)
//		{
//			memo[i].push_back(0);
//			prev[i].push_back(0);
//		}
//	}
//	
//	wayLenth = tsp(graph->getFirstNode(), state, memo, prev);
//
//	int index = graph->getFirstNode();
//
//	while (true)
//	{
//		bestWay.push_back(index);
//		int nextIndex = prev[index][state];
//		if (nextIndex == NULL)
//			break;
//		int nextState = state | (1 << nextIndex);
//		state = nextState;
//		index = nextIndex;
//	}
//
//	//bestWay.push_back(vecPerm[(1 << graph->getN()) -1][5]);
//	//std::cout << std::endl << std::endl << vecPerm[(1 << graph->getN()) - 1][2] << std::endl << std::endl << std::endl;
//	//std::cout << std::endl << std::endl << vecPerm[(1 << graph->getN()) - 1][2] << std::endl << std::endl << std::endl;
//
//
//
//
//
//
//
//
//
//
//
//
//
//	//int i = 0;
//	//int ncity = 0;
//
//	//completed[city] = 1;
//
//	//this->bestWay.push_back(city);
//	//countCompleted++;
//	//if (countCompleted == graph->getN() - 1)
//	//{
//	//	completed[graph->getLastNode()] = 0;
//	//}
//	//ncity = least(city);
//
//	//if (ncity == INT_MAX)
//	//{
//	//	return;
//	//}
//
//	//permutation(ncity);
//
//
//
//}
//
//int DynamicProg::tsp(int i, int state, std::vector<std::vector<int>> memo, std::vector<std::vector<int>> prev)
//{
//
//	if (memo[i][state] != INT_MAX)
//		return memo[i][state];
//
//	int minCost = INT_MAX;
//	int index = -1;
//	for (int next = 0; next < graph->getN(); next++)
//	{
//		if ((state & (1 << next)) != 0)
//			continue;
//
//		int nextState = state | (1 << next);
//		int newCost = graph->getMatrix()[i][next] + tsp(next, nextState, memo, prev);
//		if (newCost < minCost)
//		{
//			minCost = newCost;
//			index = next;
//		}
//	}
//	prev[i][state] = index;
//	return memo[i][state] = minCost;
//}
//
////int DynamicProg::least(int c)
////{
////	if (!running) 
////	{
////		return INT_MAX;
////	}
////	int i = 0;
////	int kmin = 0;
////	int nc = INT_MAX;
////	int min = INT_MAX;
////
////
////	for (i = 0; i < graph->getN(); i++)
////	{
////		if ((graph->getMatrix()[c][i] != -1) && (completed[i] == 0))
////			if (graph->getMatrix()[c][i] + graph->getMatrix()[i][c] < min)
////			{
////				min = graph->getMatrix()[i][0];
////				nc = i;
////			}
////	}
////
////	if (min != 999)
////		wayLenth += min;
////
////	return nc;
////}
