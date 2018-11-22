#pragma once

#ifndef __TIME_H__
#define __TIME_H__

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

class Time
{
public:

	static sf::Clock clockFromStart;

	static double time;
	static double deltaTime;
	
	static const int FPS;
	static const sf::Time frameDelay;
	static sf::Time frameStart;
	static sf::Time frameTime;

	/* FPS */
	static int currentFPS;
	static int maxFPS;
	static int minFPS;
	static int averageFPS;
	static int sumFPS;
	static int allFPS;
	static int fpsCounter;
	static sf::Time fpsCountingOldTime;

public:
		
	Time();
	~Time();

	static void UpdateTime();
	static int GetFPS();
	static int GetMaxFPS();
	static int GetMinFPS();
	static int GetAverageFPS();
};

#endif