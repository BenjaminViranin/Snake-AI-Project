
#include "include/manager/Game_Manager.h"
#include "tools/Time.h"

EGameState Game_Manager::GameState = EGameState::IsNotSet;
std::string Game_Manager::PlayerName = "Unknown";

Game_Manager::Game_Manager() : 
m_isFullScreen(false), 
m_windowWidth(1200),
m_windowHeight(675),
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
	GameState = EGameState::IsRunning;

	m_ui_manager.Init(m_windowWidth, m_windowHeight);
	m_map_manager.GenerateMap(m_windowWidth, m_windowHeight);
	m_snake.Init();
}

void Game_Manager::Update()
{
	sf::Event event;

	while (GameState != EGameState::IsClose)
	{
		m_window.pollEvent(event);

		InputEvent(event);

		if (GameState == EGameState::IsRunning)
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
			if (GameState == EGameState::IsRunning)
			{
				GameState = EGameState::IsPause;
			}
			else if (GameState == EGameState::IsPause)
			{
				GameState = EGameState::IsRunning;
			}
			break;
		case sf::Keyboard::R:
			Reset();
			break;
		case sf::Keyboard::Return:
			Reset();
			break;
		case sf::Keyboard::H:
			if (GameState == EGameState::IsRunning)
			{
				m_save_manager.LoadSave();
				m_ui_manager.ShowScoreScreen();
				GameState = EGameState::IsShowingHighScore;
			}
			else if (GameState == EGameState::IsShowingHighScore)
			{
				m_ui_manager.ShowMainScreen();
				GameState = EGameState::IsRunning;
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

	if (GameState != EGameState::IsShowingHighScore)
	{
		m_map_manager.DrawMap(&m_window);
		m_snake.Draw(&m_window);
	}

	m_ui_manager.Draw(&m_window);

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
	GameState = EGameState::IsRunning;
}
