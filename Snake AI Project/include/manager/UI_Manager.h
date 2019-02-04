#pragma once

#ifndef __UI_MANAGER_H__
#define __UI_MANAGER_H__

#include "tools/SfText.h"
#include "tools/SfLogger.h"

#include <manager/Map_Manager.h>
#include <entity/Snake.h>

class UI_Manager
{
public:
	UI_Manager(Snake& p_snake, Map_Manager& p_map_manager);
	~UI_Manager();

	void Init(int p_windowWidth, int p_windowHeight);
	void Update();
	void Draw(sf::RenderWindow* p_window);

private:
	Tools::SfLogger m_sfLoggerManager;

	int m_windowWidth;
	int m_windowHeight;
	Snake& m_snake;
	Map_Manager& m_map_manager;

	Tools::SfText GameOver;
	Tools::SfText score;
	Tools::SfText fps;
	Tools::SfText fpsValue;
	Tools::SfText pause;
	Tools::SfText pauseValue;
	Tools::SfText resetGame;
	Tools::SfText quit;
	Tools::SfText drawGrid;
	Tools::SfText drawGridValue;
	Tools::SfText snakeSpeed;
	Tools::SfText snakeSpeedValue;
	Tools::SfText showHighScores;
};

#endif // __UI_MANAGER_H__