#pragma once

#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Map_Manager.h"
#include "entity/Snake.h"
#include "UI_Manager.h"
#include "Save_Manager.h"

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
	static EGameState GameState;
	static std::string PlayerName;

private:
	sf::RenderWindow m_window;
	bool m_isFullScreen;
	int m_windowWidth;
	int m_windowHeight;

	Snake m_snake;
	Map_Manager m_map_manager;
	Save_Manager m_save_manager = Save_Manager(m_snake);
	UI_Manager m_ui_manager = UI_Manager(m_snake, m_map_manager, m_save_manager);

public:
	Game_Manager();
	~Game_Manager() = default;

	int Run();
	void Init();
	void Update();
	void Draw();
	void Close();
	void Reset();

	void InputEvent(sf::Event& event);
	void ExitGame(sf::Event& event);
};

#endif