
#include "include/manager/Game_Manager.h"
#include "tools/Time.h"

EGameState Game_Manager::gameState = EGameState::IsNotSet;

Game_Manager::Game_Manager() : m_isFullScreen(false), m_windowWidth(1200), m_windowHeight(675),
							   m_snake(m_map_manager.GetMap())
{
}

int Game_Manager::Run()
{
	this->Init();
	this->Update();
	this->Close();

	return 0;
}

void Game_Manager::Init()
{
	if (m_isFullScreen)
	{
		m_windowWidth = sf::VideoMode::getDesktopMode().width;
		m_windowHeight = sf::VideoMode::getDesktopMode().height;
		this->m_window.create(sf::VideoMode(m_windowWidth, m_windowHeight), "-- SNAKE AI --", 
							  sf::Style::Fullscreen);
	}
	else
		this->m_window.create(sf::VideoMode(m_windowWidth, m_windowHeight), "-- SNAKE AI --");

	m_window.setMouseCursorVisible(true);

	this->m_window.display();
	gameState = EGameState::IsRunning;

	m_ui_manager.Init(m_windowWidth, m_windowHeight);
	m_map_manager.GenerateMap(m_windowWidth, m_windowHeight);
	m_snake.Init();
}

void Game_Manager::Update()
{
	sf::Event event;

	while (gameState != EGameState::IsClose)
	{
		m_window.pollEvent(event);

		InputEvent(event);

		if (gameState == EGameState::IsRunning)
		{
			m_snake.Update(event);
			m_map_manager.Update();
		}

		Tools::Time::UpdateTime();

		m_ui_manager.Update();

		this->Draw();
	}
}

void Game_Manager::InputEvent(sf::Event& event)
{
	ExitGame(event);

	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::P:
			if (gameState == EGameState::IsRunning)
			{
				gameState = EGameState::IsPause;
			}
			else if (gameState == EGameState::IsPause)
			{
				gameState = EGameState::IsRunning;
			}
			break;
		case sf::Keyboard::R:
			Reset();
			break;
		case sf::Keyboard::Return:
			Reset();
			break;
		case sf::Keyboard::H:
			if (gameState == EGameState::IsRunning)
			{
				m_save_manager.LoadSave();
				gameState = EGameState::IsShowingHighScore;
			}
			else if (gameState == EGameState::IsShowingHighScore)
			{
				gameState = EGameState::IsRunning;
			}
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

void Game_Manager::Draw()
{
	this->m_window.clear();

	if (gameState == EGameState::IsShowingHighScore)
		m_ui_manager.ShowScoreScreen();
	else
	{
		m_map_manager.DrawMap(&m_window);
		m_snake.Draw(&m_window);
		m_ui_manager.Draw(&m_window);
	}

	this->m_window.display();
}

void Game_Manager::Close()
{
}

void Game_Manager::Reset()
{
	m_save_manager.SaveScore();
	m_map_manager.ResetMap();
	m_snake.Reset();
	gameState = EGameState::IsRunning;
}
