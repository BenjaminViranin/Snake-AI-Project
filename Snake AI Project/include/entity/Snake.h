#pragma once

#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <SFML/System/Vector2.hpp>
#include <vector>
#include "../manager/map_manager.h"

enum Direction
{
	idle,
	goUp,
	goDown,
	goRight,
	goLeft
};

class Snake
{
private:
	int m_lenght;
	bool m_isAlive;
	bool m_AI_Active;
	/* move speed have to be between 0 and 100 */
	float m_moveSpeed;

	Map& m_map;
	Direction m_direction;

	sf::RectangleShape m_bodyPart;
	std::vector<Map_Coordinate> m_body;

public:
	Snake(Map& p_map);
	~Snake();

	void Init();
	void Move();
	void InputProcess(sf::Event& event);
	void GrowUp(int p_num);

	void Draw(sf::RenderWindow* p_window);

	bool IsAlive();
};

#endif
