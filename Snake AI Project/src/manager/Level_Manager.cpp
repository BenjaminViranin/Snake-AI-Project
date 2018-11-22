//#include "../../include/manager/Level_Manager.h"
//#include <SFML/Window/Keyboard.hpp>
//
//float Level_Manager::m_levelSpeedAcceleration = 1.0f;
//
//Level_Manager::Level_Manager() : m_resetLevel(false),
//								 m_timeToResetLevel{ sf::seconds(0) }
//{
//}
//
//void Level_Manager::InitLevel(int p_witdh, int p_height)
//{
//	std::cout << "Timer Started\n";
//	std::cout << "Map Generation\n";
//	float timeAtStart = Time::clockFromStart.getElapsedTime().asSeconds();
//
//	m_map_manager.GenerateMap(p_witdh, p_height, 11);
//	m_castle.Init(1000);
//
//	std::cout << "Elapsed Time : " << Time::clockFromStart.getElapsedTime().asSeconds() - timeAtStart << "s\n\n";
//
//	GenerateEnemy(true);
//}
//
//void Level_Manager::Reset()
//{
//	m_castle.Reset();
//	m_skeletonManager.Clear();
//	this->GenerateEnemy(false);
//	m_resetLevel = false;
//}
//
//void Level_Manager::Run(sf::Event& event, sf::RenderWindow* p_window)
//{
//	m_map_manager.inputProcess(event, p_window);
//	this->InputProcess(event, p_window);
//
//	m_skeletonManager.Update(&m_castle);
//}
//
//void Level_Manager::Draw(sf::RenderWindow* p_window)
//{
//	/* Draw Map */
//	m_map_manager.DrawMap(p_window);
//
//	/* Draw Enemy */
//	m_skeletonManager.Draw(p_window);
//}
//
//void Level_Manager::GenerateEnemy(bool p_firstGeneration)
//{
//	if (p_firstGeneration)
//		m_skeletonManager.InitData(&m_map_manager.GetRoadPath(), m_map_manager.GetCaseSize(), 
//								    m_map_manager.GetWorldSize());
//	m_skeletonManager.AddEntity(1);
//}
//
//sf::Time resetLevelTimer = sf::milliseconds(0);
//void Level_Manager::InputProcess(sf::Event& event, sf::RenderWindow* p_window)
//{
//	/* Reset Map */
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
//	{
//		if (Time::clockFromStart.getElapsedTime() - resetLevelTimer >= m_timeToResetLevel)
//		{
//			m_resetLevel = true;
//			resetLevelTimer = Time::clockFromStart.getElapsedTime();
//		}
//	}
//	if (m_resetLevel)
//	{
//		Reset();
//	}
//
//	/* Accelerate Time */
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
//	{
//		m_levelSpeedAcceleration = 4;
//	}
//	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
//	{
//		m_levelSpeedAcceleration = 0;
//	}
//	else
//		m_levelSpeedAcceleration = 1;
//}
