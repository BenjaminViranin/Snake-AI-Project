#pragma once

#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <SFML/System/Vector2.hpp>
#include <vector>
#include "../manager/map_manager.h"

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
	bool _isTreated;
	PrimitiveDirection _primitive;

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

	sf::Time m_timeSinceLastMovement;

	Map& m_map;
	std::vector<Direction> m_directions;

	sf::RectangleShape m_bodyPart;
	std::vector<Map_Coordinate> m_body;

public:
	Snake(Map& p_map);
	~Snake();

	void Init();
	void Update(sf::Event& event);
	void InputProcess(sf::Event& event);
	void Reset();
	void Draw(sf::RenderWindow* p_window);

	void Move();
	void MoveBody(const Map_Coordinate& p_previousHeadPosition);
	bool ShouldMove();
	void TryToEat();
	void Eat();
	bool IsOnFood();
	void GrowUp(int p_num);
	void Die();

	sf::Vector2i GetMovementDirection();
	Map_Coordinate GetHead();
	void SetHead(const Map_Coordinate& p_newHeadCoordinate);
	float& GetSpeed();
	int& GetScore();
	bool IsAlive();
};

#endif
