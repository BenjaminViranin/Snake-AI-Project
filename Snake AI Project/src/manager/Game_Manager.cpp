
#include <iostream>
#include <fstream>
#include "include/manager/Game_Manager.h"

GameState Game_Manager::GameState = GameState::IsNotSet;

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
	GameState = GameState::IsRunning;

	m_map_manager.GenerateMap(m_windowWidth, m_windowHeight);
	m_snake.Init();
}

void Game_Manager::Loop()
{
	sf::Event event;

	while (GameState != GameState::IsClose)
	{
		m_window.pollEvent(event);

		InputEvent(event);

		if (GameState == GameState::IsRunning)
		{
			m_snake.Update(event);
			m_map_manager.Update();
		}

		Tools::Time::UpdateTime();

		this->Update();
	}
}

void Game_Manager::DrawHUD()
{
	sf::Color l_textColor = sf::Color(135, 206, 250);
	sf::Vector2f l_textPos;
	float l_heightTextOffset = 4.0f;

	// TODO auto bounds detection

	// Draw Pause
	if (GameState == GameState::IsPause)
	{
		l_textPos = sf::Vector2f(m_windowWidth * 0.5f - (Tools::Text::GetTextBounds("PAUSE", 50).width * 0.5f), 
								 m_windowHeight * 0.5f - (Tools::Text::GetTextBounds("PAUSE", 50).height * 0.5f));
		Tools::Text::Print(50, l_textColor, l_textPos, "PAUSE");
	}

	// Draw Game Over
	if (GameState == GameState::IsGameOver)
	{
		l_textPos = sf::Vector2f(m_windowWidth * 0.5f - (Tools::Text::GetTextBounds("DEAD", 50).width * 0.5f),
								 m_windowHeight * 0.5f - (Tools::Text::GetTextBounds("DEAD", 50).height * 0.5f));
		Tools::Text::Print(50, sf::Color::Red, l_textPos, "DEAD");
	}

	// Draw Score
	l_textPos = sf::Vector2f(10, 10);
	Tools::Text::Print(50, l_textColor, l_textPos, "SCORE: ", m_snake.GetScore());

	// Draw FPS
	l_textPos = sf::Vector2f(static_cast<float>(m_windowWidth - 450), static_cast<float>(10));
	Tools::Text::Print(22, l_textColor, l_textPos, "FPS : ");
	l_textPos = Tools::Text::GetPositionByOtherText(Tools::Text::GetLastText().getString(), RIGHT, 2);
	Tools::Text::Print(22, sf::Color(253, 106, 2), l_textPos, Tools::Time::GetFPS());

	// Draw Pause
	l_textPos = Tools::Text::GetPositionByOtherText("FPS : ", DOWN, l_heightTextOffset);
	Tools::Text::Print(22, l_textColor, l_textPos, "[P] Pause: ");
	l_textPos = Tools::Text::GetPositionByOtherText(Tools::Text::GetLastText().getString(), RIGHT, 2);
	Tools::Text::Print(22, GameState == GameState::IsPause ? sf::Color::Green : sf::Color::Red, l_textPos, GameState == GameState::IsPause ? "true" : "false");
	
	// Draw Reset Game
	l_textPos = Tools::Text::GetPositionByOtherText("[P] Pause: ", DOWN, l_heightTextOffset);
	Tools::Text::Print(22, l_textColor, l_textPos, "[R][Return] Reset Game");

	// Draw Quit
	l_textPos = Tools::Text::GetPositionByOtherText(Tools::Text::GetLastText().getString(), DOWN, l_heightTextOffset);
	Tools::Text::Print(22, l_textColor, l_textPos, "[Escape] Quit Game");

	// Draw Draw Grid
	l_textPos = Tools::Text::GetPositionByOtherText("FPS : ", RIGHT, 200);
	Tools::Text::Print(22, l_textColor, l_textPos,"[G] Draw Grid: ");
	l_textPos = Tools::Text::GetPositionByOtherText(Tools::Text::GetLastText().getString(), RIGHT, 2);
	Tools::Text::Print(22, m_map_manager.IsDrawGrid() ? sf::Color::Green : sf::Color::Red, l_textPos, m_map_manager.IsDrawGrid() ? "true" : "false");

	// Draw Snake Speed
	l_textPos = Tools::Text::GetPositionByOtherText("[G] Draw Grid: ", DOWN, l_heightTextOffset);
	Tools::Text::Print(22, l_textColor, l_textPos, "[-][+] Snake Speed: ");
	l_textPos = Tools::Text::GetPositionByOtherText(Tools::Text::GetLastText().getString(), RIGHT, 2);
	Tools::Text::Print(22, m_snake.GetSpeed() < 50 ? sf::Color::Red : m_snake.GetSpeed() > 85 ? sf::Color::Red : sf::Color::Green, l_textPos, m_snake.GetSpeed());

	// Draw Show High Scores
	l_textPos = Tools::Text::GetPositionByOtherText("[-][+] Snake Speed: ", DOWN, l_heightTextOffset);
	Tools::Text::Print(22, l_textColor, l_textPos, "[H] Show High Scores");
}

void Game_Manager::ShowHighScores()
{
	sf::Color l_textColor = sf::Color(135, 206, 250);
	sf::Vector2f l_textPos;
	float l_heightTextOffset = 4.0f;

	std::vector<std::pair<std::string, int>> l_saveData;
	LoadScore(l_saveData);

	for (int i = 0; i < l_saveData.size(); ++i)
	{
		if (i == 0)
			l_textPos = sf::Vector2f(m_windowWidth * 0.5f - (Tools::Text::GetTextBounds("[H] EXIT", 22).width * 0.5f),
									 m_windowHeight * 0.5f - (Tools::Text::GetTextBounds("[H] EXIT", 22).height * 0.5f));
		else
			l_textPos = Tools::Text::GetPositionByOtherText(Tools::Text::GetLastText().getString(), DOWN, 4);

		Tools::Text::Print(22, l_textColor, l_textPos, l_saveData[i].first, std::to_string(l_saveData[i].second));
	}

	l_textPos = Tools::Text::GetPositionByOtherText(Tools::Text::GetLastText().getString(), DOWN, 8);
	Tools::Text::Print(22, l_textColor, l_textPos, "[H] EXIT");
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
			if (GameState == GameState::IsRunning)
			{
				GameState = GameState::IsPause;
			}
			else if (GameState == GameState::IsPause)
			{
				GameState = GameState::IsRunning;
			}
			break;
		case sf::Keyboard::R:
			Reset();
			break;
		case sf::Keyboard::Return:
			Reset();
			break;
		case sf::Keyboard::H:
			if (GameState == GameState::IsRunning)
			{
				GameState = GameState::IsShowHighScore;
			}
			else if (GameState == GameState::IsShowHighScore)
			{
				GameState = GameState::IsRunning;
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

	if (GameState == GameState::IsShowHighScore)
		ShowHighScores();
	else
	{
		m_map_manager.DrawMap(&m_window);
		m_snake.Draw(&m_window);
		DrawHUD();
	}

	Tools::Text::Draw(&m_window);

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
	GameState = GameState::IsRunning;
}
