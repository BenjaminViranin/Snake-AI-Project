
#include <iostream>
#include <fstream>

#include "include/manager/Game_Manager.h"
#include "tools/Time.h"

EGameState Game_Manager::EGameState = EGameState::IsNotSet;

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
	EGameState = EGameState::IsRunning;

	m_map_manager.GenerateMap(m_windowWidth, m_windowHeight);
	m_snake.Init();
}

void Game_Manager::Loop()
{
	sf::Event event;

	while (EGameState != EGameState::IsClose)
	{
		m_window.pollEvent(event);

		InputEvent(event);

		if (EGameState == EGameState::IsRunning)
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
	const sf::Color textColor = sf::Color(135, 206, 250);
	const float heightTextOffset = 4.0f;

	// Draw Pause
	if (EGameState == EGameState::IsPause)
	{
		pause.SetFont(Tools::SfLogger::GetFont("SAO"));
		pause.SetSize(50);
		pause.SetColor(textColor);
		pause.SetOrigin(Tools::ETextEncrage::Middle);
		pause.SetText("PAUSE");
		pause.SetPosition(sf::Vector2f(m_windowWidth * 0.5f, m_windowHeight * 0.5f));
		Tools::SfLogger::Save(pause);
	}

	// Draw Game Over
	if (EGameState == EGameState::IsGameOver)
	{
		GameOver.SetFont(Tools::SfLogger::GetFont("SAO"));
		GameOver.SetSize(50);
		GameOver.SetColor(sf::Color::Red);
		GameOver.SetOrigin(Tools::ETextEncrage::Middle);
		GameOver.SetText("GAME OVER");
		GameOver.SetPosition(sf::Vector2f(m_windowWidth * 0.5f, m_windowHeight * 0.5f));
		Tools::SfLogger::Save(GameOver);
	}

	// Draw Score
	score.SetFont(Tools::SfLogger::GetFont("SAO"));
	score.SetSize(50);
	score.SetColor(textColor);
	score.SetText("SCORE: ", m_snake.GetScore());
	score.SetPosition(sf::Vector2f(10, 10));
	Tools::SfLogger::Save(score);

	// Draw FPS
	fps.SetFont(Tools::SfLogger::GetFont("SAO"));
	fps.SetSize(22);
	fps.SetColor(textColor);
	fps.SetText("FPS : ");
	fps.SetPosition(sf::Vector2f(static_cast<float>(m_windowWidth - 450), static_cast<float>(10)));
	Tools::SfLogger::Save(fps);

	fpsValue.SetFont(Tools::SfLogger::GetFont("SAO"));
	fpsValue.SetSize(22);
	fpsValue.SetColor(sf::Color(253, 106, 2));
	fpsValue.SetText(Tools::Time::GetFPS());
	fpsValue.SetPositionWithOtherText(fps, Tools::ETextPosition::Right, 2);
	Tools::SfLogger::Save(fpsValue);

	// Draw Pause
	pause.SetFont(Tools::SfLogger::GetFont("SAO"));
	pause.SetSize(22);
	pause.SetColor(textColor);
	pause.SetText("[P] Pause: ");
	pause.SetPositionWithOtherText(fps, Tools::ETextPosition::Down, heightTextOffset);
	Tools::SfLogger::Save(pause);

	pauseValue.SetFont(Tools::SfLogger::GetFont("SAO"));
	pauseValue.SetSize(22);
	pauseValue.SetColor(EGameState == EGameState::IsPause ? sf::Color::Green : sf::Color::Red);
	pauseValue.SetText(EGameState == EGameState::IsPause ? "true" : "false");
	pauseValue.SetPositionWithOtherText(pause, Tools::ETextPosition::Right, 2);
	Tools::SfLogger::Save(pauseValue);
	
	// Draw Reset Game
	resetGame.SetFont(Tools::SfLogger::GetFont("SAO"));
	resetGame.SetSize(22);
	resetGame.SetColor(textColor);
	resetGame.SetText("[R][Return] Reset Game");
	resetGame.SetPositionWithOtherText(pause, Tools::ETextPosition::Down, heightTextOffset);
	Tools::SfLogger::Save(resetGame);

	// Draw Quit
	quit.SetFont(Tools::SfLogger::GetFont("SAO"));
	quit.SetSize(22);
	quit.SetColor(textColor);
	quit.SetText("[Escape] Quit Game");
	quit.SetPositionWithOtherText(resetGame, Tools::ETextPosition::Down, heightTextOffset);
	Tools::SfLogger::Save(quit);

	// Draw Draw Grid
	drawGrid.SetFont(Tools::SfLogger::GetFont("SAO"));
	drawGrid.SetSize(22);
	drawGrid.SetColor(textColor);
	drawGrid.SetText("[G] Draw Grid: ");
	drawGrid.SetPositionWithOtherText(fps, Tools::ETextPosition::Right, 200);
	Tools::SfLogger::Save(drawGrid);

	drawGridValue.SetFont(Tools::SfLogger::GetFont("SAO"));
	drawGridValue.SetSize(22);
	drawGridValue.SetColor(m_map_manager.IsDrawGrid() ? sf::Color::Green : sf::Color::Red);
	drawGridValue.SetText(m_map_manager.IsDrawGrid() ? "true" : "false");
	drawGridValue.SetPositionWithOtherText(drawGrid, Tools::ETextPosition::Right, 2);
	Tools::SfLogger::Save(drawGridValue);

	// Draw Snake Speed
	snakeSpeed.SetFont(Tools::SfLogger::GetFont("SAO"));
	snakeSpeed.SetSize(22);
	snakeSpeed.SetColor(textColor);
	snakeSpeed.SetText("[-][+] Snake Speed: ");
	snakeSpeed.SetPositionWithOtherText(drawGrid, Tools::ETextPosition::Down, heightTextOffset);
	Tools::SfLogger::Save(snakeSpeed);

	snakeSpeedValue.SetFont(Tools::SfLogger::GetFont("SAO"));
	snakeSpeedValue.SetSize(22);
	snakeSpeedValue.SetColor(m_snake.GetSpeed() < 50 ? sf::Color::Red : m_snake.GetSpeed() > 85 ? sf::Color::Red : sf::Color::Green);
	snakeSpeedValue.SetText(m_snake.GetSpeed());
	snakeSpeedValue.SetPositionWithOtherText(snakeSpeed, Tools::ETextPosition::Right, 2);
	Tools::SfLogger::Save(snakeSpeedValue);

	// Draw Show High Scores
	showHighScores.SetFont(Tools::SfLogger::GetFont("SAO"));
	showHighScores.SetSize(22);
	showHighScores.SetColor(textColor);
	showHighScores.SetText("[H] Show High Scores ");
	showHighScores.SetPositionWithOtherText(snakeSpeed, Tools::ETextPosition::Down, heightTextOffset);
	Tools::SfLogger::Save(showHighScores);
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
			if (EGameState == EGameState::IsRunning)
			{
				EGameState = EGameState::IsPause;
			}
			else if (EGameState == EGameState::IsPause)
			{
				EGameState = EGameState::IsRunning;
			}
			break;
		case sf::Keyboard::R:
			Reset();
			break;
		case sf::Keyboard::Return:
			Reset();
			break;
		case sf::Keyboard::H:
			if (EGameState == EGameState::IsRunning)
			{
				EGameState = EGameState::IsShowHighScore;
			}
			else if (EGameState == EGameState::IsShowHighScore)
			{
				EGameState = EGameState::IsRunning;
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

	if (EGameState == EGameState::IsShowHighScore)
		ShowHighScores();
	else
	{
		m_map_manager.DrawMap(&m_window);
		m_snake.Draw(&m_window);
		DrawHUD();
	}

	Tools::SfLogger::Draw(&m_window);

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
	EGameState = EGameState::IsRunning;
}
