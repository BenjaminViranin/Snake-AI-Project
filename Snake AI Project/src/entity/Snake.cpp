
#include "include/entity/Snake.h"
#include "include/manager/Game_Manager.h"
#include "tools/Time.h"

Snake::Snake(Map& p_map) :	m_lenght(0),									m_isAlive(true),
							m_AI_Active(false),								m_moveSpeed(80.0f),
							m_score(0),										
							m_timeSinceLastMovement(sf::milliseconds(0)),	m_movementDirection(sf::Vector2i()),	
							m_oldFirst(PrimitiveDirection::Idle),			m_map(p_map)
{
}

Snake::~Snake()
{
}

void Snake::Init()
{
	m_body.emplace_back(Map_Coordinate(static_cast<int>(m_map._column * 0.5f), static_cast<int>(m_map._line * 0.5f)));
	m_body.emplace_back(Map_Coordinate(static_cast<int>(m_map._column * 0.5f), static_cast<int>(m_map._line * 0.5f) + 1));
	m_lenght += 2;

	m_bodyPart.setSize(sf::Vector2f(Map_Manager::m_caseSize, Map_Manager::m_caseSize));
	m_bodyPart.setOutlineColor(sf::Color::Black);
	m_bodyPart.setOutlineThickness(1.0f);

	InitHeadShape();
	InitTailShape();
}

void Snake::InitHeadShape()
{
	float l_curve = Map_Manager::m_caseSize * 0.2f;
	m_head._skull.setPointCount(6);
	m_head._skull.setPoint(0, sf::Vector2f(l_curve, 0));
	m_head._skull.setPoint(1, sf::Vector2f(0, l_curve));
	m_head._skull.setPoint(2, sf::Vector2f(0, Map_Manager::m_caseSize));
	m_head._skull.setPoint(3, sf::Vector2f(Map_Manager::m_caseSize, Map_Manager::m_caseSize));
	m_head._skull.setPoint(4, sf::Vector2f(Map_Manager::m_caseSize, l_curve));
	m_head._skull.setPoint(5, sf::Vector2f(Map_Manager::m_caseSize - l_curve, 0));
	m_head._skull.setOrigin(sf::Vector2f(Map_Manager::m_caseSize * 0.5f, Map_Manager::m_caseSize * 0.5f));
	m_head._skull.setOutlineColor(sf::Color::Black);
	m_head._skull.setOutlineThickness(1.0f);

	m_head._leftEye = sf::CircleShape(1.0f, 15);
	m_head._leftEye.setOrigin(sf::Vector2f(1.0f, 1.0f));
	m_head._leftEye.setFillColor(sf::Color::Red);
	m_head._leftEye.setOutlineColor(sf::Color::Black);
	m_head._leftEye.setOutlineThickness(1.0f);

	m_head._rightEye = sf::CircleShape(1.0f, 15);
	m_head._rightEye.setOrigin(sf::Vector2f(1.0f, 1.0f));
	m_head._rightEye.setFillColor(sf::Color::Red);
	m_head._rightEye.setOutlineColor(sf::Color::Black);
	m_head._rightEye.setOutlineThickness(1.0f);
}

void Snake::InitTailShape()
{
	m_tail.setPointCount(3);
	m_tail.setPoint(0, sf::Vector2f(0, 0));
	m_tail.setPoint(1, sf::Vector2f(0, Map_Manager::m_caseSize));
	m_tail.setPoint(2, sf::Vector2f(Map_Manager::m_caseSize, Map_Manager::m_caseSize * 0.5f));
	m_tail.setOrigin(sf::Vector2f(Map_Manager::m_caseSize * 0.5f, Map_Manager::m_caseSize * 0.5f));
	m_tail.setOutlineColor(sf::Color::Black);
	m_tail.setOutlineThickness(1.0f);
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

			const sf::Vector2i movementDirection = GetMovementDirection();

			const Map_Coordinate previousSnakeHead = snakeHead;
			const Map_Coordinate previousSnakeTail = GetTail();
			SetHead(snakeHead + movementDirection);

			if (GetHead().IsOutsideOfBounds(m_map._column, m_map._line)
				|| CheckCollision(GetHead()))
			{
				SetHead(previousSnakeHead);
				Die();
			}
			else
			{
				if (m_direction.second._primitive != PrimitiveDirection::Idle)
					MoveBody(previousSnakeHead);
				UpdateMapGridCase(previousSnakeTail);
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

bool Snake::CheckCollision(const Map_Coordinate& p_head)
{
	return !m_map._mapGrid[p_head.x][p_head.y]._isFree;
}

void Snake::UpdateMapGridCase(const Map_Coordinate& p_previousTailPos)
{
	m_map._mapGrid[m_body[1].x][m_body[1].y]._isFree = false;
	m_map._mapGrid[p_previousTailPos.x][p_previousTailPos.y]._isFree = true;
}

void Snake::InputProcess(sf::Event& event)
{
	/* Set PrimitiveDirection */
	ProcessUpInput();
	ProcessDownInput();
	ProcessRightInput();
	ProcessLeftInput();

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

void Snake::ProcessUpInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (m_direction.second._primitive != PrimitiveDirection::GoDown)
		{
			m_direction.first._primitive = m_direction.second._primitive;
			m_direction.first._isTreated = m_direction.second._isTreated;

			m_direction.second._primitive = PrimitiveDirection::GoUp;
			m_direction.second._isTreated = false;
		}
	}
}

void Snake::ProcessDownInput()
{
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
}

void Snake::ProcessRightInput()
{
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
}

void Snake::ProcessLeftInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (m_direction.second._primitive != PrimitiveDirection::GoRight)
		{
			m_direction.first._primitive = m_direction.second._primitive;
			m_direction.first._isTreated = m_direction.second._isTreated;

			m_direction.second._primitive = PrimitiveDirection::GoLeft;
			m_direction.second._isTreated = false;
		}
	}
}

bool Snake::IsOnFood()
{
	return m_body[0].x == m_map._Apple._coord.x && m_body[0].y == m_map._Apple._coord.y;
}

void Snake::TryToEat()
{
	if (IsOnFood())
		Eat();
}

void Snake::Eat()
{
	m_map._Apple.isAlive = false;
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
	Game_Manager::gameState = GameState::IsGameOver;
}

void Snake::GrowUp(int p_num)
{
	while(p_num--)
	{	
		if (m_body.back().y < m_body[m_body.size() - 2].y)
			m_body.emplace_back(Map_Coordinate(m_body.back().x, m_body.back().y - 1));
		else if (m_body.back().y > m_body[m_body.size() - 2].y)
			m_body.emplace_back(Map_Coordinate(m_body.back().x, m_body.back().y + 1));
		else if (m_body.back().x > m_body[m_body.size() - 2].x)
			m_body.emplace_back(Map_Coordinate(m_body.back().x + 1, m_body.back().y));
		else if (m_body.back().x < m_body[m_body.size() - 2].x)
			m_body.emplace_back(Map_Coordinate(m_body.back().x - 1, m_body.back().y));

		m_lenght++;
	}
}

void Snake::Reset()
{
	m_isAlive = true;
	m_AI_Active = false;
	m_moveSpeed = 80.0f;
	m_score = 0;
	m_direction.first = Direction();
	m_direction.second = Direction();

	m_body.clear();
	m_body.emplace_back(Map_Coordinate(static_cast<int>(m_map._column * 0.5f), static_cast<int>(m_map._line * 0.5f)));
	m_body.emplace_back(Map_Coordinate(static_cast<int>(m_map._column * 0.5f), static_cast<int>(m_map._line * 0.5f + 1)));
	m_lenght = 2;
}

Map_Coordinate Snake::GetHead()
{
	return m_body[0];
}

Map_Coordinate Snake::GetTail()
{
	return m_body.back();
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
		if (i == 0)
		{
			DrawHead(p_window);
		}
		else if ( i == m_lenght - 1)
		{
			DrawTail(p_window);
		}
		else
		{
			m_bodyPart.setFillColor(m_bodyColor);
			m_bodyPart.setPosition(m_map._mapGrid[m_body[i].x][m_body[i].y]._pos);
			p_window->draw(m_bodyPart);
		}
	}
}

void Snake::DrawHead(sf::RenderWindow* p_window)
{
	m_head._skull.setFillColor(m_bodyColor);
	m_head._skull.setPosition(m_map._mapGrid[m_body.front().x][m_body.front().y]._pos);
	m_head._skull.setPosition(m_head._skull.getPosition().x + Map_Manager::m_caseSize * 0.5f, m_head._skull.getPosition().y + Map_Manager::m_caseSize * 0.5f);

	m_head._leftEye.setPosition(m_map._mapGrid[m_body.front().x][m_body.front().y]._pos);
	m_head._rightEye.setPosition(m_map._mapGrid[m_body.front().x][m_body.front().y]._pos);

	float l_eyeOffset = 4.0f;
	m_head._skull.rotate(-m_head._skull.getRotation());
	if (m_body[1].y > m_body.front().y)  // Up
	{
		m_head._leftEye.setPosition(m_head._leftEye.getPosition().x + l_eyeOffset, m_head._leftEye.getPosition().y + l_eyeOffset);
		m_head._rightEye.setPosition(m_head._rightEye.getPosition().x + Map_Manager::m_caseSize - l_eyeOffset, m_head._rightEye.getPosition().y + l_eyeOffset);
	}
	else if (m_body[1].y < m_body.front().y)  // Down
	{
		m_head._leftEye.setPosition(m_head._leftEye.getPosition().x + l_eyeOffset, m_head._leftEye.getPosition().y + Map_Manager::m_caseSize - l_eyeOffset);
		m_head._rightEye.setPosition(m_head._rightEye.getPosition().x + Map_Manager::m_caseSize - 3.0f, m_head._rightEye.getPosition().y + Map_Manager::m_caseSize - l_eyeOffset);
		m_head._skull.rotate(180);
	}
	else if (m_body[1].x < m_body.front().x)  // Right
	{
		m_head._leftEye.setPosition(m_head._leftEye.getPosition().x + Map_Manager::m_caseSize - l_eyeOffset, m_head._leftEye.getPosition().y + l_eyeOffset);
		m_head._rightEye.setPosition(m_head._rightEye.getPosition().x + Map_Manager::m_caseSize - l_eyeOffset, m_head._rightEye.getPosition().y + Map_Manager::m_caseSize - l_eyeOffset);
		m_head._skull.rotate(90);
	}
	else if (m_body[1].x > m_body.front().x)  // Left
	{
		m_head._leftEye.setPosition(m_head._leftEye.getPosition().x + l_eyeOffset, m_head._leftEye.getPosition().y + Map_Manager::m_caseSize - l_eyeOffset);
		m_head._rightEye.setPosition(m_head._rightEye.getPosition().x + l_eyeOffset, m_head._rightEye.getPosition().y + l_eyeOffset);
		m_head._skull.rotate(-90);
	}

	p_window->draw(m_head._skull);
	p_window->draw(m_head._leftEye);
	p_window->draw(m_head._rightEye);
}

void Snake::DrawTail(sf::RenderWindow* p_window)
{
	m_tail.setFillColor(m_bodyColor);
	m_tail.setPosition(m_map._mapGrid[m_body.back().x][m_body.back().y]._pos);
	m_tail.setPosition(m_tail.getPosition().x + Map_Manager::m_caseSize * 0.5f, m_tail.getPosition().y + Map_Manager::m_caseSize * 0.5f);

	m_tail.rotate(-m_tail.getRotation());
	if (m_body.back().y < m_body[m_body.size() - 2].y)
		m_tail.rotate(-90);
	else if (m_body.back().y > m_body[m_body.size() - 2].y)
		m_tail.rotate(90);
	else if (m_body.back().x < m_body[m_body.size() - 2].x)
		m_tail.rotate(180);

	p_window->draw(m_tail);
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
