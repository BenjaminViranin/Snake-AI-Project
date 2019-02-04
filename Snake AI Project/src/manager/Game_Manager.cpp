
#include <iostream>
#include <fstream>

#include "include/manager/Game_Manager.h"
#include "tools/Time.h"

EGameState Game_Manager::gameState = EGameState::IsNotSet;

Game_Manager::Game_Manager() : m_isFullScreen(false), m_windowWidth(1200), m_windowHeight(675),
							   m_snake(m_map_manager.GetMap()), m_saveLength(20)
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

void Game_Manager::Loop()
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

		this->Update();
	}
}

void Game_Manager::ShowHighScores()
{
	sf::Color l_textColor = sf::Color(135, 206, 250);
	sf::Vector2f l_textPos;

	std::vector<std::pair<std::string, int>> l_saveData;
	LoadScore(l_saveData);

	/*for (int i = 0; i < l_saveData.size(); ++i)
	{
		if (i == 0)
			l_textPos = sf::Vector2f(m_windowWidth * 0.5f - (Tools::SfLogger::GetTextBounds("[H] EXIT", 22).width * 0.5f),
									 m_windowHeight * 0.5f - (Tools::SfLogger::GetTextBounds("[H] EXIT", 22).height * 0.5f));
		else
			l_textPos = Tools::SfLogger::GetPositionByOtherText(Tools::SfLogger::GetLastText().getString(), Tools::ETextPosition::Down, 4);

		Tools::SfLogger::Save(22, l_textColor, l_textPos, l_saveData[i].first, std::to_string(l_saveData[i].second));
	}

	l_textPos = Tools::SfLogger::GetPositionByOtherText(Tools::SfLogger::GetLastText().getString(), Tools::ETextPosition::Down, 8);
	Tools::SfLogger::Save(22, l_textColor, l_textPos, "[H] EXIT");*/
}

void Game_Manager::SaveScore()
{
	int l_linesNumber = 0;

	std::ifstream readFile;
	std::ofstream writeFile;
	std::string line;

	readFile.open("Save/HighScores.txt");
	if (readFile.is_open())
	{
		while (getline(readFile, line))
			++l_linesNumber;
		readFile.close();
	}
	else std::cout << "Unable to open file";

	writeFile.open("Save/HighScores.txt", std::fstream::app);
	if (writeFile.is_open())
	{
		std::string name = "Benji";
		std::string score = ":" + std::to_string(m_snake.GetScore());
		if (l_linesNumber <= m_saveLength)
		{
			std::string data = "\n" + name + score;
			writeFile << data;
		}
		writeFile.close();
	}
	else std::cout << "Unable to open file";
}

void Game_Manager::LoadScore(std::vector<std::pair<std::string, int>>& p_saveData)
{
	std::ifstream readFile;
	std::string line;

	std::string name;
	int score;

	readFile.open("Save/HighScores.txt");
	if (readFile.is_open())
	{
		while (getline(readFile, line))
		{
			bool isName = true;
			
			for (auto c : line)
			{
				if (c == ':')
				{
					isName = false;
					continue;
				}
				if (isName)
					name += c;
				else
					score = 0;
			}

			p_saveData.emplace_back(std::pair<std::string, int>(name, score));
		}
		readFile.close();
	}
	else std::cout << "Unable to open file";
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
				gameState = EGameState::IsShowHighScore;
			}
			else if (gameState == EGameState::IsShowHighScore)
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

void Game_Manager::Update()
{
	this->m_window.clear();

	if (gameState == EGameState::IsShowHighScore)
		ShowHighScores();
	else
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
	SaveScore();
	m_map_manager.ResetMap();
	m_snake.Reset();
	gameState = EGameState::IsRunning;
}
