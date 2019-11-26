#include "BruteForce1.h"
#include "Graph.h"


//metoda która liczy dystancję
int BruteForce1::distance(vector<int> tmpVec)
{
	int result = 0;
	for (int i = 0; i < tmpVec.size()-1; i++) {

		result += this->graph.matrix[tmpVec[i]][tmpVec[i + 1]];
	}
	return result;
}


void BruteForce1::pull()
{
	for (int j = 0; j < this->graph.matrix.size(); j++) {
		najlepsza_droga.push_back(j);
		poczatkowa_droga.push_back(j);
	}
	poczatkowa_droga.push_back(0);
	najlepsza_droga.push_back(0);
}

//glowna funkcja algorytmu, ktora odpowiada za znalezienie najlepszej drogi, w tej funkcji też wskazujemy maksymalny czas działania ałgorytmu
void BruteForce1::perm(vector<int>& tmpVec, int lf )
{
	maxTime = LONG_MAX;//60000*1;//maks czas
	if (time.getTimeFromStart() >= maxTime) {
		
		return;
	}
	
	if (lf >= tmpVec.size()-1) {
		if (distance(najlepsza_droga) >= distance(tmpVec)) {
			najlepsza_droga = tmpVec;
			
		}
		countOfPerm++;
		return;
		
	}
	perm(tmpVec, lf + 1);
	for (int i = lf + 1; i < tmpVec.size() - 1; i++) {
		swap(tmpVec, lf, i);
		perm(tmpVec, lf + 1);
		swap(tmpVec, lf, i);
	}
	
}
//wspamagające funkcja do perm, która zamienia miejsczami miasta
void BruteForce1::swap(vector<int>& tmpVec, int i, int j)
{
	int i2 = tmpVec[i];
	tmpVec[i] = tmpVec[j];
	tmpVec[j] = i2;
}

//wyczyszczenie dla welokrotnego wykorzystania programu
void BruteForce1::setAllNull()
{
	najlepsza_droga.clear();
	poczatkowa_droga.clear();
	

}

//inicjalizacja calego algorytmu z pomiarem czasu
void BruteForce1::realizacja()
{
	setAllNull();
	pull();
	
	size = this->graph.matrix.size();
	numOfPerm = fact(size-1);
	time.startTimer();
	perm(poczatkowa_droga, 1);
	time.stopTimer();
	cout << "Time: " << time.getDeltataTime() << "ms"<< endl;
	
	cout << "Percent = " << (long double)countOfPerm / (long double)numOfPerm * (long double)100 << "%" << endl;
	cout << "BestWay = ";
	for (int i = 0; i < najlepsza_droga.size(); i++) {
		cout << najlepsza_droga[i] << " ";
	}
	cout << endl << "Lenght = " <<distance(najlepsza_droga) << endl;
	//cout << "count = " << countOfPerm<< "numPerm = "<< numOfPerm  << endl;
}

//liczenie silniej
unsigned long long BruteForce1::fact(int N)
{
	if (N < 0) // если пользователь ввел отрицательное число
		return 0; // возвращаем ноль
	if (N == 0) // если пользователь ввел ноль,
		return 1; // возвращаем факториал от нуля - не удивляетесь, но это 1 =)
	else // Во всех остальных случаях
		return N * fact(N - 1); // делаем рекурсию.
}


BruteForce1::BruteForce1(Graph& graph)
{
	this->graph = graph;
}
