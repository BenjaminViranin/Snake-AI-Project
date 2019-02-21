#pragma once

#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <SFML/System/Vector2.hpp>
#include <vector>

#include "manager/map_manager.h"

enum class EPrimitiveDirection
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
	EPrimitiveDirection	_primitive;

	Direction(EPrimitiveDirection p_primitive = EPrimitiveDirection::Idle) : 
			  _isTreated(false), _primitive(p_primitive) {}
};

struct HeadShape
{
	sf::CircleShape _leftEye;
	sf::CircleShape _rightEye;
	sf::ConvexShape _skull;
};

class Snake
{
private:
	int		m_lenght;
	bool	m_isAlive;
	bool	m_AI_Active;
	float	m_moveSpeed;
	int		m_score;

	/* Map, Direction */
	Map&							m_map;
	sf::Time						m_timeSinceLastMovement;
	sf::Vector2i					m_movementDirection;
	std::pair<Direction, Direction> m_direction;
	EPrimitiveDirection				m_oldFirst;

	/* Body, Color */
	sf::RectangleShape			m_bodyPart;
	HeadShape					m_head;
	sf::ConvexShape				m_tail;
	std::vector<Map_Coordinate> m_body;
	sf::Color					m_bodyColor;

public:
	Snake(Map& p_map);
	~Snake();

	void Init();
	void InitHeadShape();
	void InitTailShape();
	void Update(sf::Event& event);
	void Reset();
	void Draw(sf::RenderWindow* p_window);
	void DrawHead(sf::RenderWindow* p_window);
	void DrawTail(sf::RenderWindow* p_window);
	void SetBodyColor(int p_index, std::string p_mode, float p_frequency);

	void InputProcess(sf::Event& event);
	void ProcessUpInput();
	void ProcessDownInput();
	void ProcessRightInput();
	void ProcessLeftInput();

	void Move();
	void MoveBody(const Map_Coordinate& p_previousHeadPosition);
	bool ShouldMove();
	bool CheckCollision(const Map_Coordinate& p_head);
	void UpdateMapGridCase(const Map_Coordinate& p_previousTailPos);
	void TryToEat();
	void Eat();
	bool IsOnFood();
	void GrowUp(int p_num);
	void Die();

	sf::Vector2i	GetMovementDirection();
	Map_Coordinate	GetHead();
	Map_Coordinate	GetTail();
	void			SetHead(const Map_Coordinate& p_newHeadCoordinate);
	float&			GetSpeed();
	int&			GetScore();
	bool			IsAlive();
	bool			IsAIActive();
};

#endif
