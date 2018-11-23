
#include "include/entity/Snake.h"
#include "include/manager/Game_Manager.h"

Snake::Snake(Map& p_map) :	m_lenght(0),			m_isAlive(true),
							m_AI_Active(false),		m_moveSpeed(80.0f),
							m_score(0),				m_timeSinceLastMovement(sf::milliseconds(0)),
							m_map(p_map)		
{
	m_directions.emplace_back(Direction());
}

Snake::~Snake()
{
}

void Snake::Init()
{
	m_body.emplace_back(Map_Coordinate(static_cast<int>(m_map._column * 0.5f), static_cast<int>(m_map._line * 0.5f)));
	m_lenght++;

	m_bodyPart.setSize(sf::Vector2f(Map_Manager::m_caseSize, Map_Manager::m_caseSize));
	m_bodyPart.setOutlineColor(sf::Color::Black);
	m_bodyPart.setOutlineThickness(1.0f);
}

void Snake::Update(sf::Event& event)
{
	InputProcess(event);
	Move();
}

void Snake::Move()
{
	if (m_isAlive)
	{
		if (ShouldMove())
		{
			Map_Coordinate snakeHead = GetHead();

			sf::Vector2i movementDirection = GetMovementDirection();

			Map_Coordinate previousSnakeHead = snakeHead;
			SetHead(snakeHead + movementDirection);

			if (GetHead().IsOutsideOfBounds(m_map._column, m_map._line))
			{
				SetHead(snakeHead);
				Die();
			}
			else
			{
				MoveBody(previousSnakeHead);
				TryToEat();
			}

			// Clear direction
			m_timeSinceLastMovement = Tools::Time::clockFromStart.getElapsedTime();
		}
	}
}

bool Snake::ShouldMove()
{
	return Tools::Time::clockFromStart.getElapsedTime() - m_timeSinceLastMovement >= sf::milliseconds(500) * (1 - m_moveSpeed * 0.01f) && m_moveSpeed != 0.0f;
}

void Snake::InputProcess(sf::Event& event)
{
	/* Set PrimitiveDirection */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (m_directions.back()._primitive != PrimitiveDirection::GoDown 
			&& m_directions.back()._primitive != PrimitiveDirection::GoUp)
		{
			m_directions.emplace_back(Direction(PrimitiveDirection::GoUp));
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (m_directions.back()._primitive != PrimitiveDirection::GoUp
			&& m_directions.back()._primitive != PrimitiveDirection::GoDown)
		{
			m_directions.emplace_back(Direction(PrimitiveDirection::GoDown));
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (m_directions.back()._primitive != PrimitiveDirection::GoLeft
			&& m_directions.back()._primitive != PrimitiveDirection::GoRight)
		{
			m_directions.emplace_back(Direction(PrimitiveDirection::GoRight));
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (m_directions.back()._primitive != PrimitiveDirection::GoRight
			&& m_directions.back()._primitive != PrimitiveDirection::GoLeft)
		{
			m_directions.emplace_back(Direction(PrimitiveDirection::GoLeft));
		}
	}

	/* Set Move Speed */
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
	for (uint16_t i = static_cast<uint16_t>(m_body.size() - 1); i > 0; --i)
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
				m_body.emplace_back(Map_Coordinate(m_body.back().x - 1, m_body.back().y));
			else if (m_body.back().x < m_body[m_body.size() - 2].x)
				m_body.emplace_back(Map_Coordinate(m_body.back().x + 1, m_body.back().y));
		}
		else
		{
			if (m_directions.back()._primitive == PrimitiveDirection::GoDown)
			{
				if (m_body.back().y > 1)
					m_body.emplace_back(Map_Coordinate(m_body.back().x, m_body.back().y - 1));
			}
			if (m_directions.back()._primitive == PrimitiveDirection::GoUp)
			{
				if (m_body.back().y < m_map._line - 1)
					m_body.emplace_back(Map_Coordinate(m_body.back().x, m_body.back().y + 1));
			}
			if (m_directions.back()._primitive == PrimitiveDirection::GoRight)
			{
				if (m_body.back().x > 1)
					m_body.emplace_back(Map_Coordinate(m_body.back().x - 1, m_body.back().y));
			}
			if (m_directions.back()._primitive == PrimitiveDirection::GoLeft)
			{
				if (m_body.back().x < m_map._column - 1)
					m_body.emplace_back(Map_Coordinate(m_body.back().x + 1, m_body.back().y));
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
	m_directions.clear();
	m_directions.emplace_back(Direction());

	m_body.clear();
	m_body.emplace_back(Map_Coordinate(static_cast<int>(m_map._column * 0.5f), static_cast<int>(m_map._line * 0.5f)));
}

Map_Coordinate Snake::GetHead()
{
	return m_body[0];
}

void Snake::SetHead(const Map_Coordinate& p_newHeadCoordinate)
{
	m_body[0] = p_newHeadCoordinate;
}

sf::Vector2i Snake::GetMovementDirection()
{
	for (uint16_t i = 0; i < m_directions.size(); ++i)
	{
		if (!m_directions[i]._isTreated || i == m_directions.size() - 1)
		switch (m_directions[i]._primitive)
		{
		case PrimitiveDirection::GoUp:
			m_directions[i]._isTreated = true;
			return sf::Vector2i(0, -1);
			break;
		case PrimitiveDirection::GoDown:
			m_directions[i]._isTreated = true;
			return sf::Vector2i(0, 1);
			break;
		case PrimitiveDirection::GoRight:
			m_directions[i]._isTreated = true;
			return sf::Vector2i(1, 0);
			break;
		case PrimitiveDirection::GoLeft:
			m_directions[i]._isTreated = true;
			return sf::Vector2i(-1, 0);
			break;
		default:
			m_directions[i]._isTreated = true;
			return sf::Vector2i(0, 0);
			break;
		}
	}
}

void Snake::Draw(sf::RenderWindow* p_window)
{
	for (int i = 0; i < m_lenght; ++i)
	{
		m_bodyPart.setFillColor(sf::Color((i * 15) > 255 ? 255 - (i * 15) : (i * 15), (255 - i * 15) < 0 ? (255 - i * 15) * -1 : (255 - i * 15), i * 15 > 255 ? 255 - i * 15 : i * 15));
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
