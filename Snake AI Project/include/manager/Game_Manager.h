#pragma once

#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "tools/SfLogger.h"
#include "Map_Manager.h"
#include "entity/Snake.h"

enum class EGameState
{
	IsNotSet,
	IsRunning,
	IsClose,
	IsGameOver,
	IsPause,
	IsShowHighScore
};

class Game_Manager
{
public:
	static EGameState EGameState;

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

private:
	sf::RenderWindow m_window;
	bool m_isFullScreen;
	int m_windowWidth;
	int m_windowHeight;

	/* Saves */
	int m_saveLength;

	Tools::SfLogger m_textTools;
	Map_Manager m_map_manager;
	Snake m_snake;

public:
	Game_Manager();
	~Game_Manager() {};

	int Run();
	void Init();
	void Loop();
	void Update();
	void Close();
	void Reset();

	void DrawHUD();
	void ShowHighScores();

	void SaveScore();
	void LoadScore(std::vector<std::pair<std::string, int>>& p_saveData);

	void InputEvent(sf::Event& event);
	void ExitGame(sf::Event& event);
};

#endif