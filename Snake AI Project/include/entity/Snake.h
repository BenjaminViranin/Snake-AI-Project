#pragma once

#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <SFML/System/Vector2.hpp>
#include <vector>
#include "../manager/map_manager.h"
#include <mutex>

enum class PrimitiveDirection
{
	Idle,
	GoUp,
	GoDown,
	GoRight,
	GoLeft
};

struct Direction
{
	bool				_isTreated;
	PrimitiveDirection	_primitive;

	Direction(PrimitiveDirection p_primitive = PrimitiveDirection::Idle) : 
			  _isTreated(false), _primitive(p_primitive) {}
};

class Snake
{
private:
	int m_lenght;
	bool m_isAlive;
	bool m_AI_Active;
	float m_moveSpeed;
	int m_score;

	/* Input Thread */
	bool		m_takeMovementInput;
	std::mutex	m_mutex;
	std::thread m_upThread;
	std::thread m_downThread;
	std::thread m_rightThread;
	std::thread m_leftThread;

	/* Map, Direction */
	Map& m_map;
	sf::Time m_timeSinceLastMovement;
	sf::Vector2i m_movementDirection;
	std::pair<Direction, Direction> m_direction;
	PrimitiveDirection m_oldFirst;

	/* Body, Color */
	sf::RectangleShape m_bodyPart;
	std::vector<Map_Coordinate> m_body;
	sf::Color m_bodyColor;

public:
	Snake(Map& p_map);
	~Snake();

	void Init();
	void Update(sf::Event& event);
	void Reset();
	void Draw(sf::RenderWindow* p_window);
	void SetBodyColor(int p_index, std::string p_mode, float p_frequency);

	void InputProcess(sf::Event& event);
	void StartMovementInputThread();
	void TakeUpInput();
	void TakeDownInput();
	void TakeRightInput();
	void TakeLeftInput();

	void Move();
	void MoveBody(const Map_Coordinate& p_previousHeadPosition);
	bool ShouldMove();
	void TryToEat();
	void Eat();
	bool IsOnFood();
	void GrowUp(int p_num);
	void Die();

	sf::Vector2i	GetMovementDirection();
	Map_Coordinate	GetHead();
	void			SetHead(const Map_Coordinate& p_newHeadCoordinate);
	float&			GetSpeed();
	int&			GetScore();
	bool			IsAlive();
};

#endif
