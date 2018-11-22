#include "../../include/tools/Time.h"
#include <iostream>

sf::Clock Time::clockFromStart;

double Time::time = 0.0f;
double Time::deltaTime = 0.0f;

/* FPS */
const int Time::FPS = 500;
const sf::Time Time::frameDelay = sf::milliseconds(1000 / FPS);
sf::Time Time::frameStart;
sf::Time Time::frameTime;
int Time::currentFPS = 0;
int Time::maxFPS = 0;
int Time::minFPS = 5000;
int Time::averageFPS = 0;
int Time::sumFPS = 0;
int Time::allFPS = 0;
int  Time::fpsCounter = 0;
sf::Time Time::fpsCountingOldTime = sf::milliseconds(0);

Time::Time()
{
}

void Time::UpdateTime()
{
	const double previousTime = time;
	time = clockFromStart.getElapsedTime().asSeconds();
	deltaTime = time - previousTime;
}

int Time::GetFPS()
{
	fpsCounter++;
	if (clockFromStart.getElapsedTime() - fpsCountingOldTime >= sf::milliseconds(1000))
	{
		currentFPS = fpsCounter;
		fpsCounter = 0;
		fpsCountingOldTime = clockFromStart.getElapsedTime();
		sumFPS += currentFPS;
		++allFPS;
	};
	return currentFPS;
}

int Time::GetMaxFPS()
{
	return maxFPS = currentFPS > maxFPS ? currentFPS : maxFPS;
}

int Time::GetMinFPS()
{
	return minFPS = currentFPS < minFPS ? currentFPS > 1 ? currentFPS : minFPS : minFPS;
}

int Time::GetAverageFPS()
{
	return averageFPS = sumFPS / allFPS;
}

Time::~Time()
{
}