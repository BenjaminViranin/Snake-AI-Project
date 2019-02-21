#pragma once

#ifndef __UI_MANAGER_H__
#define __UI_MANAGER_H__

#include "tools/SfText.h"
#include "tools/SfLogger.h"

#include "manager/Map_Manager.h"
#include "entity/Snake.h"
#include "Save_Manager.h"

#include <deque>

class UI_Manager
{
public:
	UI_Manager(Snake& p_snake, Map_Manager& p_map_manager, Save_Manager& p_save_manager);
	~UI_Manager();

	void Init(int p_windowWidth, int p_windowHeight);
	void Update();
	void Draw(sf::RenderWindow* p_window);

	void ShowScoreScreen();

private:
	Tools::SfLogger m_sfLoggerManager;

	int m_windowWidth;
	int m_windowHeight;
	Snake& m_snake;
	Map_Manager& m_map_manager;
	Save_Manager& m_save_manager;

	/* Main Screen */
	Tools::SfText GameOver;
	Tools::SfText score;
	Tools::SfText fps;
	Tools::SfText fpsValue;
	Tools::SfText pauseScreen;
	Tools::SfText pause;
	Tools::SfText pauseValue;
	Tools::SfText resetGame;
	Tools::SfText quit;
	Tools::SfText drawGrid;
	Tools::SfText drawGridValue;
	Tools::SfText snakeSpeed;
	Tools::SfText snakeSpeedValue;
	Tools::SfText showHighScores;

	/* High Scores Screen */
	std::deque<Tools::SfText> playerScores;
	std::deque<Tools::SfText> AIScores;
};

#endif // __UI_MANAGER_H__