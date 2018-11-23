
#include "include/entity/Snake.h"
#include "include/manager/Game_Manager.h"

Snake::Snake(Map& p_map) :
	m_lenght(0),			m_isAlive(true),
	m_AI_Active(false),		m_moveSpeed(80.0f),
	m_score(0),				m_direction(Direction::Idle),
	m_map(p_map),			m_timeSinceLastMovement(sf::milliseconds(0))
{
}

Snake::~Snake()
{
}

void Snake::Init()
{
	m_body.emplace_back(Map_Coordinate(static_cast<int>(m_map._colunm * 0.5f), static_cast<int>(m_map._line * 0.5f)));
	m_lenght++;

	m_bodyPart.setSize(sf::Vector2f(Map_Manager::m_caseSize, Map_Manager::m_caseSize));
	m_bodyPart.setOutlineColor(sf::Color::Black);
	m_bodyPart.setOutlineThickness(1.0f);
}


void Snake::Move()
{
	if (m_isAlive)
	{
		/*if (m_lenght > 1)
		{
			std::cout << "m_body[last]: " << m_body[m_body.size() - 1].x << "; " << m_body[m_body.size() - 1].y << "\n";
			std::cout << "m_body[before last]: " << m_body[m_body.size() - 2].x << "; " << m_body[m_body.size() - 2].y << "\n";
		}*/

		if (ShouldMove())
		{
			Map_Coordinate snakeHead = GetHead();

			auto[xMovement, yMovement] = GetMovementDirection(m_direction);

			Map_Coordinate previousSnakeHead = snakeHead;
			SetHead(snakeHead + Map_Coordinate{ xMovement, yMovement });

			if (GetHead().IsOutsideOfBounds(m_map._colunm, m_map._line))
			{
				Die();
			}
			else
			{
				MoveBody(previousSnakeHead);
				TryToEat();
			}

			m_timeSinceLastMovement = Time::clockFromStart.getElapsedTime();
		}
	}
}

bool Snake::ShouldMove()
{
	return Time::clockFromStart.getElapsedTime() - m_timeSinceLastMovement >= sf::milliseconds(500) * (1 - m_moveSpeed * 0.01f) && m_moveSpeed != 0.0f;
}

void Snake::InputProcess(sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (m_direction != Direction::GoDown)
			m_direction = Direction::GoUp;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (m_direction != Direction::GoUp)
			m_direction = Direction::GoDown;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (m_direction != Direction::GoLeft)
			m_direction = Direction::GoRight;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (m_direction != Direction::GoRight)
			m_direction = Direction::GoLeft;
	}

	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Subtract:
			--m_moveSpeed;
			if (m_moveSpeed < 0)
				m_moveSpeed = 0;
			break;
		case sf::Keyboard::Add:
			++m_moveSpeed;
			if (m_moveSpeed > 100)
				m_moveSpeed = 100;
			break;
		}
	}
}

bool Snake::IsOnFood()
{
	return m_body[0].x == m_map._food._coord.x && m_body[0].y == m_map._food._coord.y;
}

void Snake::TryToEat()
{
	if (IsOnFood())
		Eat();
}

void Snake::Eat()
{
	m_map._food.isAlive = false;
	++m_score;
	GrowUp(1);
}

void Snake::MoveBody(const Map_Coordinate& p_previousHeadPosition)
{
	for (uint16_t i = m_body.size() - 1; i > 0; --i)
		m_body[i] = i == 1 ? p_previousHeadPosition : m_body[i - 1];
}

void Snake::Die()
{
	m_isAlive = false;
	Game_Manager::GameState = GameState::IsGameOver;
}

void Snake::GrowUp(int p_num)
{
	while(p_num--)
	{
		if (m_lenght > 1)
		{
			if (m_body.back().y < m_body[m_body.size() - 2].y)
				m_body.emplace_back(Map_Coordinate(m_body.back().x, m_body.back().y - 1));
			else if (m_body.back().y > m_body[m_body.size() - 2].y)
				m_body.emplace_back(Map_Coordinate(m_body.back().x, m_body.back().y + 1));
			else if (m_body.back().x > m_body[m_body.size() - 2].x)
				m_body.emplace_back(Map_Coordinate(m_body.back().x, m_body.back().x + 1));
			else if (m_body.back().x < m_body[m_body.size() - 2].x)
				m_body.emplace_back(Map_Coordinate(m_body.back().x, m_body.back().x - 1));
		}
		else
		{
			if (m_direction == Direction::GoDown)
			{
				if (m_body.back().y > 1)
					m_body.emplace_back(Map_Coordinate(m_body.back().x, m_body.back().y - 1));
			}
			if (m_direction == Direction::GoUp)
			{
				if (m_body.back().y < m_map._line - 1)
					m_body.emplace_back(Map_Coordinate(m_body.back().x, m_body.back().y + 1));
			}
			if (m_direction == Direction::GoRight)
			{
				if (m_body.back().x > 1)
					m_body.emplace_back(Map_Coordinate(m_body.back().x, m_body.back().x - 1));
			}
			if (m_direction == Direction::GoLeft)
			{
				if (m_body.back().x < m_map._colunm - 1)
					m_body.emplace_back(Map_Coordinate(m_body.back().x, m_body.back().x + 1));
			}
		}

		m_lenght++;
	}
}

void Snake::Reset()
{
	m_lenght = 1;
	m_isAlive = true;
	m_AI_Active = false;
	m_moveSpeed = 80.0f;
	m_score = 0;
	m_direction = Direction::Idle;

	m_body.clear();
	m_body.emplace_back(Map_Coordinate(static_cast<int>(m_map._colunm * 0.5f), static_cast<int>(m_map._line * 0.5f)));
}

Map_Coordinate Snake::GetHead()
{
	return m_body[0];
}

void Snake::SetHead(const Map_Coordinate & p_newHeadCoordinate)
{
	m_body[0] = p_newHeadCoordinate;
}

std::pair<int, int> Snake::GetMovementDirection(Direction p_direction)
{
	switch (p_direction)
	{
	case Direction::GoUp:
		return std::make_pair(0, -1);
		break;
	case Direction::GoDown:
		return std::make_pair(0, 1);
		break;
	case Direction::GoRight:
		return std::make_pair(1, 0);
		break;
	case Direction::GoLeft:
		return std::make_pair(-1, -0);
		break;
	default:
		return std::make_pair(0, 0);
		break;
	}
}

void Snake::Draw(sf::RenderWindow* p_window)
{
	for (int i = 0; i < m_lenght; ++i)
	{
		m_bodyPart.setPosition(m_map._mapGrid[m_body[i].x][m_body[i].y]);
		p_window->draw(m_bodyPart);
	}
}

float& Snake::GetSpeed()
{
	return m_moveSpeed;
}

int& Snake::GetScore()
{
	return m_score;
}

bool Snake::IsAlive()
{
	return m_isAlive;
}
