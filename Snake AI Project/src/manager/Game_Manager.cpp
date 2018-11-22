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
			m_map_manager.Update();
		}

		Time::UpdateTime();

		DrawHUD();

		this->Update();
	}
}

void Game_Manager::DrawHUD()
{
	// Draw Pause, Game Over
	if (GameState == IsPause)
	{
		Text_Manager::Print(34, sf::Color::Yellow, sf::Vector2f(m_windowWidth * 0.5 - 58, m_windowHeight * 0.5 - 17), "PAUSE");
	}
	else if (GameState == IsGameOver)
	{
		Text_Manager::Print(34, sf::Color::Red, sf::Vector2f(m_windowWidth * 0.5 - 46, m_windowHeight * 0.5 - 17), "DEAD");
	}

	// Draw FPS
	Text_Manager::Print(18, sf::Color::Yellow, sf::Vector2f(m_windowWidth - 200, 2), "FPS : ", Time::GetFPS());

	// Draw Pause
	Text_Manager::Print(16, sf::Color::Yellow, sf::Vector2f(m_windowWidth - 200, 2 + 18),
						"[P] Pause: ");
	Text_Manager::Print(16, GameState == IsPause ? sf::Color::Green : sf::Color::Red,
						sf::Vector2f(m_windowWidth - 200 + 90, 2 + 18),
						GameState == IsPause ? "true" : "false");
	// Draw Reset Game
	Text_Manager::Print(16, sf::Color::Yellow, sf::Vector2f(m_windowWidth - 200, 2 + 18 * 2),
						"[R][Return] Reset Game");

	// Draw Quit
	Text_Manager::Print(16, sf::Color::Yellow, sf::Vector2f(m_windowWidth - 200, 2 + 18 * 3),
						"[Escape] Quit Game");

	// Draw Draw Grid
	Text_Manager::Print(16, sf::Color::Yellow, sf::Vector2f(m_windowWidth - 200, 2 + 18 * 4),
						"[G] Draw Grid: ");
	Text_Manager::Print(16, m_map_manager.IsDrawGrid() ? sf::Color::Green : sf::Color::Red,
						sf::Vector2f(m_windowWidth - 200 + 120, 2 + 18 * 4),
						m_map_manager.IsDrawGrid() ? "true" : "false");
	// Draw Snake Speed
	Text_Manager::Print(16, sf::Color::Yellow, sf::Vector2f(m_windowWidth - 200, 2 + 18 * 5), 
						"[-][+] Snake Speed: ");
	Text_Manager::Print(16, m_snake.GetSpeed() < 50 ? sf::Color::Red : m_snake.GetSpeed() > 85 ? sf::Color::Red : sf::Color::Green,
						sf::Vector2f(m_windowWidth - 200 + 160, 2 + 18 * 5),
						m_snake.GetSpeed());

	// Draw Score
	Text_Manager::Print(34, sf::Color::Yellow, sf::Vector2f(10, 10),
						"SCORE: ", m_snake.GetScore());
}

void Game_Manager::InputEvent(sf::Event& event)
{
	ExitGame(event);

	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::P:
			if (GameState == IsRunning)
			{
				GameState = IsPause;
			}
			else if (GameState == IsPause)
			{
				GameState = IsRunning;
			}
			break;
		case sf::Keyboard::R:
			m_map_manager.ResetMap();
			m_snake.Reset();
			GameState = IsRunning;
			break;
		case sf::Keyboard::Return:
			m_map_manager.ResetMap();
			m_snake.Reset();
			GameState = IsRunning;
			break;
		}
	}

	m_map_manager.inputProcess(event);
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

void Game_Manager::Reset()
{
}
