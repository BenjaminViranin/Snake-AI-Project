#pragma once

#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <SFML/System/Vector2.hpp>
#include <vector>
#include "../manager/map_manager.h"

enum class Direction
{
	Idle,
	GoUp,
	GoDown,
	GoRight,
	GoLeft
};

class Snake
{
private:
	int m_lenght;
	bool m_isAlive;
	bool m_AI_Active;
	/* move speed have to be between 0 and 100 */
	float m_moveSpeed;
	int m_score;
	sf::Time m_timeSinceLastMovement;

	Map& m_map;
	Direction m_direction;

	sf::RectangleShape m_bodyPart;
	std::vector<Map_Coordinate> m_body;

public:
	Snake(Map& p_map);
	~Snake();

	void Init();
	void Move();
	bool ShouldMove();
	void InputProcess(sf::Event& event);
	bool IsOnFood();
	void TryToEat();
	void Eat();
	void MoveBody(const Map_Coordinate& p_previousHeadPosition);
	void Die();
	void GrowUp(int p_num);
	void Reset();
	Map_Coordinate GetHead();
	void SetHead(const Map_Coordinate& p_newHeadCoordinate);
	std::pair<int, int> GetMovementDirection(Direction p_direction);

	void Draw(sf::RenderWindow* p_window);

	float& GetSpeed();
	int& GetScore();
	bool IsAlive();
};

#endif
