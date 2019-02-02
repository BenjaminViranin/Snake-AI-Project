
#include "manager/Map_Manager.h"
#include "tools/Random.h"

float Map_Manager::m_caseSize = 0.0f;

Map_Manager::Map_Manager() : m_width(0), m_height(0), m_headerheight(0), m_drawGrid(false)
{
	/* Substract 1 to start index at 0 */
	m_map._column = 60;
	m_map._line = 24;
}

Map_Manager::~Map_Manager()
{
}

void Map_Manager::GenerateMap(int p_witdh, int p_height)
{
	m_caseSize = (float)p_witdh / (float)m_map._column;
	m_headerheight = static_cast<int>(p_height - (m_map._line + 1) * m_caseSize);

	m_width = p_witdh;
	m_height = p_height - m_headerheight;

	m_caseSize = (float)m_width / ((float)m_map._column + 1);

	for (int x = 0; x <= m_map._column; ++x)
	{
		for (int y = 0; y <= m_map._line; ++y)
		{
			m_map._mapGrid[x][y]._pos = (sf::Vector2f(x * m_caseSize,
									m_headerheight + y * m_caseSize));
			m_map._mapGrid[x][y]._isFree = true;

			if (x != 0 && x != m_map._column
				&& y != 0 && y != m_map._line)
				m_mapCases[x * m_map._line + y] = &m_map._mapGrid[x][y]._isFree;
		}
	}

	/* Generate Grid Lines */
	for (int i = 0; i <= m_map._line; i++)
	{
		m_GridLines.emplace_back(sf::Vertex(sf::Vector2f(0, m_headerheight + m_caseSize * i), sf::Color(127, 127, 127)));
		m_GridLines.emplace_back(sf::Vertex(sf::Vector2f(static_cast<float>(m_width), static_cast<float>(m_headerheight + m_caseSize * i)), sf::Color::White));
	}
	for (int i = 0; i <= m_map._column; i++)
	{
		m_GridLines.emplace_back(sf::Vertex(sf::Vector2f(m_caseSize * i, static_cast<float>(m_headerheight)), sf::Color(127, 127, 127)));
		m_GridLines.emplace_back(sf::Vertex(sf::Vector2f(m_caseSize * i, static_cast<float>(m_headerheight + m_map._line * m_caseSize)), sf::Color::White));
	}

	/* Generate Map Border */
	sf::RectangleShape l_mapBorder;
	l_mapBorder.setFillColor(sf::Color(127, 127, 127));

	l_mapBorder.setPosition(sf::Vector2f(0, m_headerheight - ((p_height - m_headerheight) - (m_map._line + 1)* m_caseSize)));
	l_mapBorder.setSize(sf::Vector2f(static_cast<float>(m_width), static_cast<float>(m_caseSize + ((p_height - m_headerheight) - (m_map._line + 1)* m_caseSize))));
	m_mapBorder.push_back(l_mapBorder);

	l_mapBorder.setPosition(sf::Vector2f(static_cast<float>(0), static_cast<float>(m_headerheight)));
	l_mapBorder.setSize(sf::Vector2f(static_cast<float>(m_caseSize), static_cast<float>(m_height)));
	m_mapBorder.push_back(l_mapBorder);

	l_mapBorder.setPosition(sf::Vector2f(static_cast<float>(m_width - m_caseSize), static_cast<float>(m_headerheight)));
	l_mapBorder.setSize(sf::Vector2f(static_cast<float>(m_caseSize), static_cast<float>(m_height)));
	m_mapBorder.push_back(l_mapBorder);

	l_mapBorder.setPosition(sf::Vector2f(0, p_height - m_caseSize - ((p_height - m_headerheight) - (m_map._line + 1)* m_caseSize)));
	l_mapBorder.setSize(sf::Vector2f(static_cast<float>(m_width), static_cast<float>(m_caseSize + ((p_height - m_headerheight) - (m_map._line + 1)* m_caseSize))));
	m_mapBorder.push_back(l_mapBorder);

	/* Generate Apple */
	InitAppleShape();
	GenerateApple();
	m_map._Apple.isAlive = true;
}

void Map_Manager::InitAppleShape()
{
	m_apple._body.setPointCount(8);
	float l_curve = m_caseSize * 0.225f;
	m_apple._body.setPoint(0, sf::Vector2f(l_curve, 0));
	m_apple._body.setPoint(1, sf::Vector2f(0, l_curve));
	m_apple._body.setPoint(2, sf::Vector2f(0, m_caseSize - l_curve));
	m_apple._body.setPoint(3, sf::Vector2f(l_curve, m_caseSize));
	m_apple._body.setPoint(4, sf::Vector2f(m_caseSize - l_curve, m_caseSize));
	m_apple._body.setPoint(5, sf::Vector2f(m_caseSize, m_caseSize - l_curve));
	m_apple._body.setPoint(6, sf::Vector2f(m_caseSize, l_curve));
	m_apple._body.setPoint(7, sf::Vector2f(m_caseSize - l_curve, 0));
	m_apple._body.setFillColor(sf::Color::Red);
	m_apple._body.setOutlineColor(sf::Color::Black);
	m_apple._body.setOutlineThickness(1.0f);

	m_apple._leaf.setPointCount(4);
	float l_radius = m_caseSize * 0.25f;
	m_apple._leaf.setPoint(0, sf::Vector2f(0, l_radius * 2));
	m_apple._leaf.setPoint(1, sf::Vector2f(l_radius, l_radius));
	m_apple._leaf.setPoint(2, sf::Vector2f(l_radius, 0));
	m_apple._leaf.setPoint(3, sf::Vector2f(0, l_radius * 0.5f));
	m_apple._leaf.setOrigin(sf::Vector2f(l_radius * 0.5f, l_radius));
	m_apple._leaf.setFillColor(sf::Color::Green);
}

void Map_Manager::ClearMap()
{
	for (int x = 0; x <= m_map._column; ++x)
	{
		for (int y = 0; y <= m_map._line; ++y)
			m_map._mapGrid[x][y]._isFree = true;
	}
}

void Map_Manager::ResetMap()
{
	ClearMap();

	GenerateApple();
	m_map._Apple.isAlive = true;
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

	DrawAppleShape(p_window);
}

void Map_Manager::DrawAppleShape(sf::RenderWindow* p_window)
{
	m_apple._leaf.setPosition(sf::Vector2f(m_apple._body.getPosition().x + m_caseSize * 0.5f, m_apple._body.getPosition().y));
	p_window->draw(m_apple._body);
	p_window->draw(m_apple._leaf);
}

void Map_Manager::Update()
{
	if (!m_map._Apple.isAlive)
	{
		GenerateApple();
		m_map._Apple.isAlive = true;
	}
}

void Map_Manager::GenerateApple()
{
	/* Random only between free case  =>  Fast */
	std::vector<int> l_availableCase;
	for (int i = 0; i < m_map._line * m_map._column; ++i)
	{
		if (m_mapCases[i])
			l_availableCase.push_back(i);
	}

	const int l_randomIndex = Tools::Random::GenerateInt(0, static_cast<int>(l_availableCase.size()) - 1);
	const int l_freeCaseIndex = l_availableCase[l_randomIndex];

	m_map._Apple._coord.x = l_freeCaseIndex / m_map._line;
	m_map._Apple._coord.y = l_freeCaseIndex - (m_map._line * m_map._Apple._coord.x);
	m_apple._body.setPosition(m_map._mapGrid[m_map._Apple._coord.x][m_map._Apple._coord.y]._pos);
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