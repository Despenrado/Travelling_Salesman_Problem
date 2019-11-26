#pragma once
#include <iostream>
#include <chrono>
class Timer
{
public:
	void startTimer();
	void stopTimer();
	unsigned long long getTimeFromStart();
	unsigned long long getDeltataTime();
private:
	std::chrono::steady_clock::time_point timeStart;
	std::chrono::steady_clock::time_point timeEnd;
	
};

