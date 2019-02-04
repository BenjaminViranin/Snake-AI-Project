#pragma once

#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "tools/SfLogger.h"
#include "Map_Manager.h"
#include "entity/Snake.h"
#include "UI_Manager.h"

enum class EGameState
{
	IsNotSet,
	IsRunning,
	IsClose,
	IsGameOver,
	IsPause,
	IsShowingHighScore
};

class Game_Manager
{
public:
	static EGameState gameState;

private:
	sf::RenderWindow m_window;
	bool m_isFullScreen;
	int m_windowWidth;
	int m_windowHeight;

	/* Saves */
	int m_saveLength;

	Map_Manager m_map_manager;
	Snake m_snake;
	UI_Manager m_ui_manager = UI_Manager(m_snake, m_map_manager);

public:
	Game_Manager();
	~Game_Manager() = default;

	int Run();
	void Init();
	void Loop();
	void Update();
	void Close();
	void Reset();

	// TODO implemente in Ui_Manager
	void ShowHighScores();

	// TODO implement in Save_Manager
	void SaveScore();
	void LoadSave(std::vector<std::pair<std::string, int>>& p_saveData);

	void InputEvent(sf::Event& event);
	void ExitGame(sf::Event& event);
};

#endif