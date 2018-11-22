#include <iostream>
#include "../../include/manager/map_manager.h"
#include <complex.h>
#include "../../include/tools/Random.h"

float Map_Manager::m_caseSize = 0.0f;

Map_Manager::Map_Manager() : m_width(0), m_height(0), m_headerheight(0), m_drawGrid(false)
{
	/* Substract 1 to start index at 0 */
	m_map._colunm = 60;
	m_map._line = 24;
}

Map_Manager::~Map_Manager()
{
}

void Map_Manager::GenerateMap(int p_witdh, int p_height)
{
	m_caseSize = (float)p_witdh / (float)m_map._colunm;
	m_headerheight = p_height - (m_map._line + 1) * m_caseSize;

	m_width = p_witdh;
	m_height = p_height - m_headerheight;

	m_caseSize = (float)m_width / ((float)m_map._colunm + 1);

	for (int x = 0; x <= m_map._colunm; ++x)
	{
		for (int y = 0; y <= m_map._line; ++y)
		{
			m_map._mapGrid[x][y] = (sf::Vector2f(x * m_caseSize,
									m_headerheight + y * m_caseSize));
		}
	}

	/* Generate Grid Lines */
	for (int i = 0; i <= m_map._line; i++)
	{
		m_GridLines.emplace_back(sf::Vertex(sf::Vector2f(0, m_headerheight + m_caseSize * i), sf::Color::White));
		m_GridLines.emplace_back(sf::Vertex(sf::Vector2f(m_width, m_headerheight + m_caseSize * i), sf::Color::White));
	}
	for (int i = 0; i <= m_map._colunm; i++)
	{
		m_GridLines.emplace_back(sf::Vertex(sf::Vector2f(m_caseSize * i, m_headerheight), sf::Color::White));
		m_GridLines.emplace_back(sf::Vertex(sf::Vector2f(m_caseSize * i, m_headerheight + m_map._line * m_caseSize), sf::Color::White));
	}

	/* Generate Map Border */
	sf::RectangleShape l_mapBorder;
	l_mapBorder.setFillColor(sf::Color(127, 127, 127));

	l_mapBorder.setPosition(sf::Vector2f(0, m_headerheight - ((p_height - m_headerheight) - (m_map._line + 1)* m_caseSize)));
	l_mapBorder.setSize(sf::Vector2f(m_width, m_caseSize + ((p_height - m_headerheight) - (m_map._line + 1)* m_caseSize)));
	m_mapBorder.push_back(l_mapBorder);

	l_mapBorder.setPosition(sf::Vector2f(0, m_headerheight));
	l_mapBorder.setSize(sf::Vector2f(m_caseSize, m_height));
	m_mapBorder.push_back(l_mapBorder);

	l_mapBorder.setPosition(sf::Vector2f(m_width - m_caseSize, m_headerheight));
	l_mapBorder.setSize(sf::Vector2f(m_caseSize, m_height));
	m_mapBorder.push_back(l_mapBorder);

	l_mapBorder.setPosition(sf::Vector2f(0, p_height - m_caseSize - ((p_height - m_headerheight) - (m_map._line + 1)* m_caseSize)));
	l_mapBorder.setSize(sf::Vector2f(m_width, m_caseSize + ((p_height - m_headerheight) - (m_map._line + 1)* m_caseSize)));
	m_mapBorder.push_back(l_mapBorder);

	/* Generate Food */
	m_food.setSize(sf::Vector2f(m_caseSize, m_caseSize));
	m_food.setFillColor(sf::Color::Red);
	m_food.setOutlineColor(sf::Color::Black);
	m_food.setOutlineThickness(1.0f);
	GenerateFood();
	m_map._food.isAlive = true;
}

void Map_Manager::DestroyMap()
{

}

void Map_Manager::ResetMap()
{
	DestroyMap();

	GenerateFood();
	m_map._food.isAlive = true;
}

void Map_Manager::DrawMap(sf::RenderWindow* p_window)
{
	if (m_drawGrid)
	{
		p_window->draw(&m_GridLines[0], m_GridLines.size(), sf::Lines);
	}

	for (int i = 0; i < 4; ++i)
	{
		p_window->draw(m_mapBorder[i]);
	}

	p_window->draw(m_food);
}

void Map_Manager::Update()
{
	if (!m_map._food.isAlive)
	{
		GenerateFood();
		m_map._food.isAlive = true;
	}
}

void Map_Manager::GenerateFood()
{
	m_map._food._coord.x = Random::GenerateInt(1, m_map._colunm - 1);
	m_map._food._coord.y = Random::GenerateInt(1, m_map._line - 1);
	m_food.setPosition(m_map._mapGrid[m_map._food._coord.x][m_map._food._coord.y]);
}

void Map_Manager::inputProcess(sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::G:
			m_drawGrid = !m_drawGrid;
			break;
		}
	}
}

Map& Map_Manager::GetMap()
{
	return m_map;
}

bool Map_Manager::IsDrawGrid()
{
	return m_drawGrid;
}

// 97