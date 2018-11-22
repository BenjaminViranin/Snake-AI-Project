
//#include <SFML/Window/Keyboard.hpp>
//#include <SFML/Window.hpp>
//#include "../../include/manager/GameManager.h"
//#include "../../include/tools/Text_Manager.h"
//#include "../../include/tools/Time.h"
//
//GameManager::GameManager() : m_isFullScreen(false), m_windowWidth(1200), m_windowHeight(675)
//{
//	m_gameState = IsNotSet;
//}
//
//GameManager::~GameManager()
//{
//
//}
//
//void GameManager::Init()
//{
//	if (m_isFullScreen)
//	{
//		m_windowWidth = sf::VideoMode::getDesktopMode().width;
//		m_windowHeight = sf::VideoMode::getDesktopMode().height;
//		m_window.create(sf::VideoMode(m_windowWidth, m_windowHeight), "-- SNAKE GAME --",
//			sf::Style::Fullscreen);
//	}
//	else
//		m_window.create(sf::VideoMode(m_windowWidth, m_windowHeight), "-- SNAKE GAME --");
//
//	m_window.setMouseCursorVisible(true);
//
//	m_window.display();
//	m_gameState = IsRunning;
//
//	m_mapManager.GenerateMap(m_windowWidth, m_windowHeight, 20);
//}
//
//void GameManager::Loop()
//{
//	sf::Event event;
//	while (m_gameState == IsRunning)
//	{
//		m_window.pollEvent(event);
//
//		ExitGame(event);
//
//		Time::UpdateTime();
//
//		// Draw FPS
//		Text_Manager::Print(18, sf::Color::Red, sf::Vector2f(m_windowWidth - 177, 2), "FPS : ", Time::GetFPS());
//
//		this->Update();
//	}
//}
//
//void GameManager::Close()
//{
//}
//
//int GameManager::Run()
//{
//	Init();
//	Loop();
//	Close();
//
//	return EXIT_SUCCESS;
//}
//
//void GameManager::ExitGame(sf::Event& event)
//{
//	if (event.type == sf::Event::Closed)
//	{
//		Close();
//		m_window.close();
//	}
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
//	{
//		Close();
//		m_window.close();
//	}
//}
//
//void GameManager::Update()
//{
//	if (m_gameState != Pause)
//	{
//		this->m_window.clear();
//
//		Text_Manager::Draw(&m_window);
//		m_mapManager.Draw(&m_window);
//
//		this->m_window.display();
//	}
//}
//
