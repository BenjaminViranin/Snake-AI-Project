
#include "manager/UI_Manager.h"

#include <tools/Time.h>
#include <manager/Game_Manager.h>

UI_Manager::UI_Manager(Snake& p_snake, Map_Manager& p_map_manager, Save_Manager& p_save_manager) :
m_windowWidth(0),
m_windowHeight(0),
m_snake(p_snake),
m_map_manager(p_map_manager),
m_save_manager(p_save_manager)
{
}

UI_Manager::~UI_Manager()
{
}

void UI_Manager::Init(int p_windowWidth, int p_windowHeight)
{
	m_windowWidth = p_windowWidth;
	m_windowHeight = p_windowHeight;

	const sf::Color textColor = sf::Color(135, 206, 250);
	const float heightTextOffset = 4.0f;

	// Draw Pause
	pauseScreen.SetFont(Tools::SfLogger::GetFont("SAO"));
	pauseScreen.SetSize(50);
	pauseScreen.SetColor(textColor);
	pauseScreen.SetOrigin(Tools::ETextEncrage::Middle);
	pauseScreen.SetText("PAUSE");
	pauseScreen.SetPosition(sf::Vector2f(m_windowWidth * 0.5f, m_windowHeight * 0.5f));
	pauseScreen.IsDrawable() = false;
	Tools::SfLogger::Save(pauseScreen);

	// Draw Game Over
	GameOver.SetFont(Tools::SfLogger::GetFont("SAO"));
	GameOver.SetSize(50);
	GameOver.SetColor(sf::Color::Red);
	GameOver.SetOrigin(Tools::ETextEncrage::Middle);
	GameOver.SetText("GAME OVER");
	GameOver.SetPosition(sf::Vector2f(m_windowWidth * 0.5f, m_windowHeight * 0.5f));
	GameOver.IsDrawable() = false;
	Tools::SfLogger::Save(GameOver);

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
	pauseValue.SetColor(Game_Manager::GameState == EGameState::IsPause ? sf::Color::Green : sf::Color::Red);
	pauseValue.SetText(Game_Manager::GameState == EGameState::IsPause ? "true" : "false");
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

	// Draw High Scores Title
	highScoresTitle.SetFont(Tools::SfLogger::GetFont("SAO"));
	highScoresTitle.SetSize(34);
	highScoresTitle.SetColor(textColor);
	highScoresTitle.SetText("HIGH SCORES");
	highScoresTitle.SetOrigin(Tools::ETextEncrage::Middle);
	highScoresTitle.SetPosition(sf::Vector2f(m_windowWidth * 0.5f, 60));
	highScoresTitle.IsDrawable() = false;
	Tools::SfLogger::Save(highScoresTitle);

	// Draw Player High Scores
	Tools::SfText playerName;
	playerName.SetFont(Tools::SfLogger::GetFont("SAO"));
	playerName.SetSize(28);
	playerName.SetColor(textColor);
	playerName.SetText(Game_Manager::PlayerName);
	playerName.IsDrawable() = false;
	sf::Vector2f namePos(m_windowWidth * 0.25f - 92, m_windowHeight * 0.25f);

	Tools::SfText playerScore;
	playerScore.SetFont(Tools::SfLogger::GetFont("SAO"));
	playerScore.SetSize(28);
	playerScore.SetColor(textColor);
	playerScore.SetText(":     ...");
	playerScore.IsDrawable() = false;
	sf::Vector2f scorePos(m_windowWidth * 0.25f + 10, m_windowHeight * 0.25f);

	for (int i = 0; i < m_save_manager.GetSaveLenght(); ++i)
	{
		playerName.SetPosition(namePos);
		playerScore.SetPosition(scorePos);
		playerScores.emplace_back(std::pair<Tools::SfText, Tools::SfText>(playerName, playerScore));
		Tools::SfLogger::Save(playerScores.back().first);
		Tools::SfLogger::Save(playerScores.back().second);

		namePos.y += 30;
		scorePos.y += 30;
	}

	// Draw AI High Scores
	Tools::SfText AIScore;
	AIScore.SetFont(Tools::SfLogger::GetFont("SAO"));
	AIScore.SetSize(28);
	AIScore.SetColor(textColor);
	AIScore.SetOrigin(Tools::ETextEncrage::Middle);
	AIScore.SetText("    AI   :   ...   ");
	AIScore.IsDrawable() = false;

	sf::Vector2f AIScorePos(m_windowWidth * 0.75f, m_windowHeight * 0.25f);
	for (int i = 0; i < m_save_manager.GetSaveLenght(); ++i)
	{
		AIScore.SetPosition(AIScorePos);
		AIScores.push_back(AIScore);
		Tools::SfLogger::Save(AIScores.back());

		AIScorePos.y += 30;
	}

	// Draw High Scores Exit
	highScoresExit.SetFont(Tools::SfLogger::GetFont("SAO"));
	highScoresExit.SetSize(26);
	highScoresExit.SetColor(textColor);
	highScoresExit.SetText("[H] Exit");
	highScoresExit.SetOrigin(Tools::ETextEncrage::Middle);
	highScoresExit.SetPosition(sf::Vector2f(m_windowWidth * 0.5f, AIScores.back().GetPosition().y + 100));
	highScoresExit.IsDrawable() = false;
	Tools::SfLogger::Save(highScoresExit);
}

void UI_Manager::Update() 
{
	// Update Pause
	if (Game_Manager::GameState == EGameState::IsPause)
		pauseScreen.IsDrawable() = true;
	else
		pauseScreen.IsDrawable() = false;

	// Update Game Over
	if (Game_Manager::GameState == EGameState::IsGameOver)
		GameOver.IsDrawable() = true;
	else
		GameOver.IsDrawable() = false;

	// Update Score
	score.SetText("SCORE: ", m_snake.GetScore());

	// Update FPS
	fpsValue.SetText(Tools::Time::GetFPS());

	// Update Pause
	pauseValue.SetColor(Game_Manager::GameState == EGameState::IsPause ? sf::Color::Green : sf::Color::Red);
	pauseValue.SetText(Game_Manager::GameState == EGameState::IsPause ? "true" : "false");

	// Update Draw Grid
	drawGridValue.SetColor(m_map_manager.IsDrawGrid() ? sf::Color::Green : sf::Color::Red);
	drawGridValue.SetText(m_map_manager.IsDrawGrid() ? "true" : "false");

	// Update Snake Speed
	snakeSpeedValue.SetColor(m_snake.GetSpeed() < 50 ? sf::Color::Red : m_snake.GetSpeed() > 85 ? sf::Color::Red : sf::Color::Green);
	snakeSpeedValue.SetText(m_snake.GetSpeed());
}

void UI_Manager::Draw(sf::RenderWindow* p_window)
{
	Tools::SfLogger::Draw(p_window);
}

void UI_Manager::ShowMainScreen()
{
	highScoresTitle.IsDrawable() = false;
	highScoresExit.IsDrawable() = false;
	for (auto& text : playerScores)
		text.first.IsDrawable() = text.second.IsDrawable() = false;
	for (auto& text : AIScores)
		text.IsDrawable() = false;

	GameOver.IsDrawable() = true;
	score.IsDrawable() = true;
	fps.IsDrawable() = true;
	fpsValue.IsDrawable() = true;
	pauseScreen.IsDrawable() = true;
	pause.IsDrawable() = true;
	pauseValue.IsDrawable() = true;
	resetGame.IsDrawable() = true;
	quit.IsDrawable() = true;
	drawGrid.IsDrawable() = true;
	drawGridValue.IsDrawable() = true;
	snakeSpeed.IsDrawable() = true;
	snakeSpeedValue.IsDrawable() = true;
	showHighScores.IsDrawable() = true;
}

void UI_Manager::ShowScoreScreen()
{
	 GameOver.IsDrawable() = false;
	 score.IsDrawable() = false;
	 fps.IsDrawable() = false;
	 fpsValue.IsDrawable() = false;
	 pauseScreen.IsDrawable() = false;
	 pause.IsDrawable() = false;
	 pauseValue.IsDrawable() = false;
	 resetGame.IsDrawable() = false;
	 quit.IsDrawable() = false;
	 drawGrid.IsDrawable() = false;
	 drawGridValue.IsDrawable() = false;
	 snakeSpeed.IsDrawable() = false;
	 snakeSpeedValue.IsDrawable() = false;
	 showHighScores.IsDrawable() = false;

	const auto& PlayerData = m_save_manager.GetPlayerData();
	const auto& AI_Data = m_save_manager.GetAIData();

	highScoresTitle.IsDrawable() = true;
	highScoresExit.IsDrawable() = true;

	for (int i = 0; i < m_save_manager.GetSaveLenght(); ++i)
	{
		playerScores[i].first.IsDrawable() = playerScores[i].second.IsDrawable() = true;
		if (i < PlayerData.size())
		{
			playerScores[i].first.SetText(PlayerData[i].first);
			playerScores[i].second.SetText(":   ", PlayerData[i].second);
		}
		else
		{
			playerScores[i].first.SetText("Unknown   ");
			playerScores[i].second.SetText(":   ...   ");
		}

		AIScores[i].IsDrawable() = true;
		if (i < AI_Data.size())
			AIScores[i].SetText("   AI   :   ", AI_Data[i].second);
		else
			AIScores[i].SetText("   AI   :   ...   ");
	}

}
