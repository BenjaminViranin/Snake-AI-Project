
#include "../../include/entity/Snake.h"
#include "../../include/manager/Game_Manager.h"

Snake::Snake(Map& p_map) : m_lenght(0), m_isAlive(true), m_AI_Active(false),
						   m_moveSpeed(80.0f), m_direction(idle), m_map(p_map)
{
}

Snake::~Snake()
{
}

void Snake::Init()
{
	m_body.emplace_back(Map_Coordinate(m_map._colunm * 0.5f, m_map._line * 0.5f));
	m_lenght++;
	GrowUp(3);

	m_bodyPart.setSize(sf::Vector2f(Map_Manager::m_caseSize, Map_Manager::m_caseSize));
	m_bodyPart.setOutlineColor(sf::Color::Black);
	m_bodyPart.setOutlineThickness(1.0f);
}

sf::Time timerCountMove = sf::milliseconds(0);
void Snake::Move()
{
	if (m_isAlive)
	{
		if (Time::clockFromStart.getElapsedTime() - timerCountMove
			>= sf::milliseconds(500) * (1 - m_moveSpeed * 0.01f) && m_moveSpeed != 0.0f)
		{
			Map_Coordinate l_frontPart;
			l_frontPart = m_body[0];

			if (m_direction == goUp)
			{
				if (m_body[0].y != 1)
					m_body[0].y--;
				else
					m_isAlive = false;
			}
			else if (m_direction == goDown)
			{
				if (m_body[0].y != m_map._line - 1)
					m_body[0].y++;
				else
					m_isAlive = false;
			}
			else if (m_direction == goRight)
			{
				if (m_body[0].x != m_map._colunm - 1)
					m_body[0].x++;
				else
					m_isAlive = false;
			}
			else if (m_direction == goLeft)
			{
				if (m_body[0].x != 1)
					m_body[0].x--;
				else
					m_isAlive = false;
			}

			if (m_isAlive)
			{
				for (int i = 1; i < m_lenght; ++i)
				{
					Map_Coordinate l_tempCoord = m_body[i];
					m_body[i] = l_frontPart;
					l_frontPart = l_tempCoord;
				}
			}

			Game_Manager::GameState = IsGameOver;

			timerCountMove = Time::clockFromStart.getElapsedTime();
		}
	}
}

void Snake::InputProcess(sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (m_direction != goDown)
			m_direction = goUp;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (m_direction != goUp)
			m_direction = goDown;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (m_direction != goLeft)
			m_direction = goRight;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (m_direction != goRight)
			m_direction = goLeft;
	}
}

void Snake::GrowUp(int p_num)
{
	while(p_num--)
	{
		if (m_body.back().y < m_map._line - 3)
			m_body.emplace_back(Map_Coordinate(m_body.back().x, m_body.back().y + 1));
		
		m_lenght++;
	}
}

void Snake::Draw(sf::RenderWindow* p_window)
{
	for (int i = 0; i < m_lenght; ++i)
	{
		m_bodyPart.setPosition(m_map._mapGrid[m_body[0].x][m_body[0].y]);
		p_window->draw(m_bodyPart);
	}
}

bool Snake::IsAlive()
{
	return m_isAlive;
}
