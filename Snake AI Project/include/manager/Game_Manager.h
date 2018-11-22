#pragma once

#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "../tools/Text_Manager.h"
#include "../tools/Time.h"
#include "Map_Manager.h"
#include "../entity/Snake.h"

enum GameState
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
	float m_windowWidth;
	float m_windowHeight;

	Map_Manager m_map_manager;
	Snake m_snake;

	Text_Manager m_text_manager;

public:
	Game_Manager();
	~Game_Manager() {};

	int Run();
	void Init();
	void Loop();
	void Close();

	void InputEvent(sf::Event& event);
	void ExitGame(sf::Event& event);
	void Update();
};

#endif