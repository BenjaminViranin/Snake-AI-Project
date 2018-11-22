
//#include "../../include/manager/MapManager.h"
//
//float MapManager::m_caseSize = 0.0f;
//
//MapManager::MapManager() : m_width(0), m_height(0), m_size(0), m_headerheight(100)
//{
//
//}
//
//MapManager::~MapManager()
//{
//
//}
//
//void MapManager::GenerateMap(int p_witdh, int p_height, int p_size)
//{
//	m_width = p_witdh;
//	m_height = p_height - m_headerheight;
//	m_size = p_size;
//
//	m_caseSize = (float)m_width / (float)m_size;
//	const int colunm = m_size;
//	const int line = m_height / m_caseSize;
//
//	m_mapGrid = new sf::Vector2f[(line - 2) * (colunm - 2)];
//
//	for (int i = 0; i < line - 2; ++i)
//	{
//		for (int j = 0; j < colunm - 2; ++j)
//		{
//			m_mapGrid[i * m_size + j] = sf::Vector2f(m_caseSize + (j * m_caseSize),
//				m_headerheight + m_caseSize + (i * m_caseSize));
//		}
//	}
//
//	m_case.setSize(sf::Vector2f(m_caseSize - 1, m_caseSize - 1));
//}
//
//void MapManager::Draw(sf::RenderWindow* p_window)
//{
//}
//
//void MapManager::Destroy()
//{
//	free(m_mapGrid);
//}
