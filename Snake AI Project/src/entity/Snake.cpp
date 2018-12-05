
#include "include/entity/Snake.h"
#include "include/manager/Game_Manager.h"

Snake::Snake(Map& p_map) :	m_lenght(0),									m_isAlive(true),
							m_AI_Active(false),								m_moveSpeed(80.0f),
							m_score(0),										m_takeMovementInput(true),
							m_timeSinceLastMovement(sf::milliseconds(0)),	m_movementDirection(sf::Vector2i()),	
							m_oldFirst(PrimitiveDirection::Idle),			m_map(p_map)
{
}

Snake::~Snake()
{
	m_upThread.join();
	m_downThread.join();
	m_rightThread.join();
	m_leftThread.join();
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
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (m_direction.second._primitive != PrimitiveDirection::GoDown)
		{
			m_direction.first._primitive = m_direction.second._primitive;
			m_direction.first._isTreated = m_direction.second._isTreated;

			m_direction.second._primitive = PrimitiveDirection::GoUp;
			m_direction.second._isTreated = false;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (m_direction.second._primitive != PrimitiveDirection::GoUp)
		{
			m_direction.first._primitive = m_direction.second._primitive;
			m_direction.first._isTreated = m_direction.second._isTreated;

			m_direction.second._primitive = PrimitiveDirection::GoDown;
			m_direction.second._isTreated = false;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (m_direction.second._primitive != PrimitiveDirection::GoLeft)
		{
			m_direction.first._primitive = m_direction.second._primitive;
			m_direction.first._isTreated = m_direction.second._isTreated;

			m_direction.second._primitive = PrimitiveDirection::GoRight;
			m_direction.second._isTreated = false;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (m_direction.second._primitive != PrimitiveDirection::GoRight)
		{
			m_direction.first._primitive = m_direction.second._primitive;
			m_direction.first._isTreated = m_direction.second._isTreated;

			m_direction.second._primitive = PrimitiveDirection::GoLeft;
			m_direction.second._isTreated = false;
		}
	}*/

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

void Snake::StartMovementInputThread()
{
	m_upThread = std::thread { &Snake::TakeUpInput, this };
	m_downThread = std::thread { &Snake::TakeDownInput, this };
	//m_rightThread = std::thread { &Snake::TakeRightInput, this };
	//m_leftThread = std::thread { &Snake::TakeLeftInput, this };
}

void Snake::TakeUpInput()
{
	while (true)
	{
		if (m_takeMovementInput && Game_Manager::GameState == GameState::IsRunning)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				if (m_direction.second._primitive != PrimitiveDirection::GoDown)
				{
					m_mutex.lock();
					m_direction.first._primitive = m_direction.second._primitive;
					m_direction.first._isTreated = m_direction.second._isTreated;

					m_direction.second._primitive = PrimitiveDirection::GoUp;
					m_direction.second._isTreated = false;
					m_mutex.unlock();
				}
			}
		}
		if (m_takeMovementInput && Game_Manager::GameState == GameState::IsRunning)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				if (m_direction.second._primitive != PrimitiveDirection::GoUp)
				{
					m_mutex.lock();
					m_direction.first._primitive = m_direction.second._primitive;
					m_direction.first._isTreated = m_direction.second._isTreated;

					m_direction.second._primitive = PrimitiveDirection::GoDown;
					m_direction.second._isTreated = false;
					m_mutex.unlock();
				}
			}
		}
	}
}

void Snake::TakeDownInput()
{
	while (true)
	{
		
		if (m_takeMovementInput && Game_Manager::GameState == GameState::IsRunning)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if (m_direction.second._primitive != PrimitiveDirection::GoRight)
				{
					m_mutex.lock();
					m_direction.first._primitive = m_direction.second._primitive;
					m_direction.first._isTreated = m_direction.second._isTreated;

					m_direction.second._primitive = PrimitiveDirection::GoLeft;
					m_direction.second._isTreated = false;
					m_mutex.unlock();
				}
			}
		}
		if (m_takeMovementInput && Game_Manager::GameState == GameState::IsRunning)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if (m_direction.second._primitive != PrimitiveDirection::GoLeft)
				{
					m_mutex.lock();
					m_direction.first._primitive = m_direction.second._primitive;
					m_direction.first._isTreated = m_direction.second._isTreated;

					m_direction.second._primitive = PrimitiveDirection::GoRight;
					m_direction.second._isTreated = false;
					m_mutex.unlock();
				}
			}
		}
	}
}

void Snake::TakeRightInput()
{
	while (true)
	{
		if (m_takeMovementInput && Game_Manager::GameState == GameState::IsRunning)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if (m_direction.second._primitive != PrimitiveDirection::GoLeft)
				{
					m_mutex.lock();
					m_direction.first._primitive = m_direction.second._primitive;
					m_direction.first._isTreated = m_direction.second._isTreated;

					m_direction.second._primitive = PrimitiveDirection::GoRight;
					m_direction.second._isTreated = false;
					m_mutex.unlock();
				}
			}
		}
	}
}

void Snake::TakeLeftInput()
{
	while (true)
	{
		if (m_takeMovementInput && Game_Manager::GameState == GameState::IsRunning)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if (m_direction.second._primitive != PrimitiveDirection::GoRight)
				{
					m_mutex.lock();
					m_direction.first._primitive = m_direction.second._primitive;
					m_direction.first._isTreated = m_direction.second._isTreated;

					m_direction.second._primitive = PrimitiveDirection::GoLeft;
					m_direction.second._isTreated = false;
					m_mutex.unlock();
				}
			}
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
	m_takeMovementInput = false;
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
			if (m_direction.second._primitive == PrimitiveDirection::GoDown)
			{
				if (m_body.back().y > 1)
					m_body.emplace_back(Map_Coordinate(m_body.back().x, m_body.back().y - 1));
			}
			if (m_direction.second._primitive == PrimitiveDirection::GoUp)
			{
				if (m_body.back().y < m_map._line - 1)
					m_body.emplace_back(Map_Coordinate(m_body.back().x, m_body.back().y + 1));
			}
			if (m_direction.second._primitive == PrimitiveDirection::GoRight)
			{
				if (m_body.back().x > 1)
					m_body.emplace_back(Map_Coordinate(m_body.back().x - 1, m_body.back().y));
			}
			if (m_direction.second._primitive == PrimitiveDirection::GoLeft)
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
	m_takeMovementInput = true;
	m_direction.first = Direction();
	m_direction.second = Direction();

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
	Direction& direction = m_direction.first;
	if (m_direction.first._isTreated || m_direction.first._primitive == m_oldFirst)
		direction = m_direction.second;
	direction._isTreated = true;
	m_oldFirst = m_direction.first._primitive;

	switch (direction._primitive)
	{
	case PrimitiveDirection::GoUp:
		if (m_movementDirection != sf::Vector2i(0, 1))
			m_movementDirection = sf::Vector2i(0, -1);
		break;

	case PrimitiveDirection::GoDown:
		if (m_movementDirection != sf::Vector2i(0, -1))
			m_movementDirection = sf::Vector2i(0, 1);
		break;

	case PrimitiveDirection::GoRight:
		if (m_movementDirection != sf::Vector2i(-1, 0))
			m_movementDirection = sf::Vector2i(1, 0);
		break;

	case PrimitiveDirection::GoLeft:
		if (m_movementDirection != sf::Vector2i(1, 0))
			m_movementDirection = sf::Vector2i(-1, 0);
		break;

	case PrimitiveDirection::Idle:
		m_movementDirection = sf::Vector2i(0, 0);
		break;
	}

	return m_movementDirection;
}

void Snake::Draw(sf::RenderWindow* p_window)
{
	for (int i = 0; i < m_lenght; ++i)
	{
		SetBodyColor(i, "Rainbow", 0.5f);
		m_bodyPart.setFillColor(m_bodyColor);
		m_bodyPart.setPosition(m_map._mapGrid[m_body[i].x][m_body[i].y]);
		p_window->draw(m_bodyPart);
	}
}

void Snake::SetBodyColor(int p_index, std::string p_mode, float p_frequency)
{
	if (p_mode == "Rainbow")
	{
		m_bodyColor.r = std::sin(p_frequency * p_index + 0) * 127 + 128;
		m_bodyColor.g = std::sin(p_frequency * p_index + 2) * 127 + 128;
		m_bodyColor.b = std::sin(p_frequency * p_index + 4) * 127 + 128;
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
