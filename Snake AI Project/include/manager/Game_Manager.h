#pragma once

#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "../tools/Text.h"
#include "../tools/Time.h"
#include "Map_Manager.h"
#include "../entity/Snake.h"

enum class GameState
{
	IsNotSet,
	IsRunning,
	IsClose,
	IsGameOver,
	IsPause
};

class Game_Manager
{
public:
	static GameState GameState;

private:
	sf::RenderWindow m_window;
	bool m_isFullScreen;
	int m_windowWidth;
	int m_windowHeight;

	Tools::Text m_textTools;
	Map_Manager m_map_manager;
	Snake m_snake;

public:
	Game_Manager();
	~Game_Manager() {};

	int Run();
	void Init();
	void Loop();
	void Close();
	void Reset();

	void UpdateHUD();
	void InputEvent(sf::Event& event);
	void ExitGame(sf::Event& event);
	void Update();
};

#endif