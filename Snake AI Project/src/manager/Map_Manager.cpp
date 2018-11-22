#include <iostream>
#include "../../include/manager/map_manager.h"
#include <complex.h>

float Map_Manager::m_caseSize = 0.0f;

Map_Manager::Map_Manager() : m_width(0), m_height(0), m_headerheight(0)
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

	m_case.setSize(sf::Vector2f(m_caseSize, m_caseSize));
	m_case.setFillColor(sf::Color::Black);
	m_case.setOutlineThickness(1.0f);
}

void Map_Manager::DestroyMap()
{
}

void Map_Manager::ResetMap()
{
}

void Map_Manager::DrawMap(sf::RenderWindow* p_window)
{
	for (int x = 0; x <= m_map._colunm; ++x)
	{
		for (int y = 0; y <= m_map._line; ++y)
		{
			//Text_Manager::Print(6, sf::Color::Red, sf::Vector2f(m_map._mapGrid[x][y].x, m_map._mapGrid[x][y].y), 
			//					x,"; ", y);
			//m_case.setPosition(m_map._mapGrid[x][y]);
			//p_window->draw(m_case);
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		p_window->draw(m_mapBorder[i]);
	}
}

void Map_Manager::inputProcess(sf::Event& event, sf::RenderWindow* p_window)
{
}

Map& Map_Manager::GetMap()
{
	return m_map;
}

// 681