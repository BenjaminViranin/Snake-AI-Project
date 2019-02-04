
#include "manager/UI_Manager.h"

#include <tools/Time.h>
#include <manager/Game_Manager.h>

UI_Manager::UI_Manager(Snake& p_snake, Map_Manager& p_map_manager) :
m_windowWidth(0),
m_windowHeight(0),
m_snake(p_snake),
m_map_manager(p_map_manager)
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
	pauseValue.SetColor(Game_Manager::gameState == EGameState::IsPause ? sf::Color::Green : sf::Color::Red);
	pauseValue.SetText(Game_Manager::gameState == EGameState::IsPause ? "true" : "false");
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

void UI_Manager::Update() 
{
	const sf::Color textColor = sf::Color(135, 206, 250);
	const float heightTextOffset = 4.0f;

	// Draw Pause
	if (Game_Manager::gameState == EGameState::IsPause)
		pauseScreen.IsDrawable() = true;
	else
		pauseScreen.IsDrawable() = false;

	// Draw Game Over
	if (Game_Manager::gameState == EGameState::IsGameOver)
		GameOver.IsDrawable() = true;
	else
		GameOver.IsDrawable() = false;

	// Draw Score
	score.SetText("SCORE: ", m_snake.GetScore());

	// Draw FPS
	fpsValue.SetText(Tools::Time::GetFPS());

	// Draw Pause
	pauseValue.SetColor(Game_Manager::gameState == EGameState::IsPause ? sf::Color::Green : sf::Color::Red);
	pauseValue.SetText(Game_Manager::gameState == EGameState::IsPause ? "true" : "false");

	// Draw Draw Grid
	drawGridValue.SetColor(m_map_manager.IsDrawGrid() ? sf::Color::Green : sf::Color::Red);
	drawGridValue.SetText(m_map_manager.IsDrawGrid() ? "true" : "false");

	// Draw Snake Speed
	snakeSpeedValue.SetColor(m_snake.GetSpeed() < 50 ? sf::Color::Red : m_snake.GetSpeed() > 85 ? sf::Color::Red : sf::Color::Green);
	snakeSpeedValue.SetText(m_snake.GetSpeed());
}

void UI_Manager::Draw(sf::RenderWindow* p_window)
{
	Tools::SfLogger::Draw(p_window);
	Tools::SfLogger::DrawTextsBounds(p_window);
}