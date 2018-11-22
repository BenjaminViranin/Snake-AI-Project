#include <iostream>
#include "../../include/manager/Game_Manager.h"

GameState Game_Manager::GameState = IsNotSet;

Game_Manager::Game_Manager() : m_isFullScreen(false), m_windowWidth(1200), m_windowHeight(675),
							   m_snake(m_map_manager.GetMap())
{
}

int Game_Manager::Run()
{
	this->Init();
	this->Loop();
	this->Close();

	return 0;
}

void Game_Manager::Init()
{
	if (m_isFullScreen)
	{
		m_windowWidth = sf::VideoMode::getDesktopMode().width;
		m_windowHeight = sf::VideoMode::getDesktopMode().height;
		this->m_window.create(sf::VideoMode(m_windowWidth, m_windowHeight), "-- TOWER DEFENCE --", 
							  sf::Style::Fullscreen);
	}
	else
		this->m_window.create(sf::VideoMode(m_windowWidth, m_windowHeight), "-- TOWER DEFENCE --");

	m_window.setMouseCursorVisible(true);

	this->m_window.display();
	GameState = IsRunning;

	m_map_manager.GenerateMap(m_windowWidth, m_windowHeight);
	m_snake.Init();
}

void Game_Manager::Loop()
{
	sf::Event event;
	while (GameState != IsClose)
	{
		m_window.pollEvent(event);

		InputEvent(event);

		if (GameState == IsRunning)
		{
			m_snake.InputProcess(event);
			m_snake.Move();
		}

		Time::UpdateTime();

		// Draw FPS
		Text_Manager::Print(18, sf::Color::Red, sf::Vector2f(m_windowWidth - 177, 2), "FPS : ", Time::GetFPS());
		if (Time::allFPS > 0)
			Text_Manager::Print(18, sf::Color::Yellow, sf::Vector2f(m_windowWidth - 177, 20), "Average FPS : ", Time::GetAverageFPS());
		Text_Manager::Print(18, sf::Color::Yellow, sf::Vector2f(m_windowWidth - 177, 38), "Min FPS : ", Time::GetMinFPS());
		Text_Manager::Print(18, sf::Color::Yellow, sf::Vector2f(m_windowWidth - 177, 56), "Max FPS : ", Time::GetMaxFPS());

		this->Update();
	}
}

void Game_Manager::InputEvent(sf::Event& event)
{
	switch (GameState)
	{
	case IsPause:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			GameState = IsRunning;
		}
		break;
	case IsRunning:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			GameState = IsPause;
		}
		break;
	case IsGameOver:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{

			GameState = IsRunning;
		}
		break;
	}

	ExitGame(event);
}

void Game_Manager::ExitGame(sf::Event& event)
{
	if (event.type == sf::Event::Closed)
	{
		Close();
		m_window.close();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		Close();
		m_window.close();
	}
}

void Game_Manager::Update()
{
	this->m_window.clear();

	m_map_manager.DrawMap(&m_window);
	m_snake.Draw(&m_window);
	Text_Manager::Draw(&m_window);

	this->m_window.display();
}

void Game_Manager::Close()
{
	m_map_manager.DestroyMap();
}
