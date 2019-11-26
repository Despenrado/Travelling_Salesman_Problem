#include "Timer.h"

void Timer::startTimer()
{
	timeStart = std::chrono::steady_clock::now();
}

void Timer::stopTimer()
{
	timeEnd = std::chrono::steady_clock::now();
}

unsigned long long Timer::getTimeFromStart()
{
	std::chrono::steady_clock::time_point timeTMP;
	timeTMP = std::chrono::steady_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(timeTMP - timeStart).count();
}

unsigned long long Timer::getDeltataTime()
{
	return std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeStart).count();
}

