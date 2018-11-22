#pragma once

#ifndef __MAP_MANAGER_H__
#define __MAP_MANAGER_H__

#include <random>
#include "../tools/Sprite.h"
#include "../tools/Time.h"
#include "../../include/tools/Text_Manager.h"

struct Map_Coordinate
{
	int x;
	int y;

	Map_Coordinate(int p_x = 0, int p_y = 0) : x(p_x), y(p_y) {}

	Map_Coordinate& operator=(const Map_Coordinate& p_other)
	{
		this->x = p_other.x;
		this->y = p_other.y;
		return *this;
	}

	Map_Coordinate operator+(const Map_Coordinate& p_other)
	{
		Map_Coordinate result;

		result.x = this->x + p_other.x;
		result.y = this->y + p_other.y;

		return result;
	}

	Map_Coordinate& operator+=(const Map_Coordinate& p_other)
	{
		this->x += p_other.x;
		this->y += p_other.y;

		return *this;
	}

	bool IsOutsideOfBounds(int p_mapWidth, int p_mapHeight)
	{
		return (x <= 0 || x >= p_mapWidth || y <= 0 || y >= p_mapHeight);
	}
};

struct Food
{
	Map_Coordinate _coord;
	bool isAlive;

	Food() : isAlive(false) {}
};

struct Map
{
	int _colunm;
	int _line;

	Food _food;

	sf::Vector2f _mapGrid[61][25];
};

class Map_Manager
{
public:
	static float m_caseSize;

private:
	int m_width;
	int m_height;
	int m_headerheight;

	Map m_map;

	bool m_drawGrid;
	std::vector<sf::Vertex> m_GridLines;
	sf::RectangleShape m_food;
	std::vector<sf::RectangleShape> m_mapBorder;

public:
	Map_Manager();
	~Map_Manager();

	void GenerateMap(int p_witdh, int p_height);
	void DestroyMap();
	void ResetMap();
	void DrawMap(sf::RenderWindow* p_window);
	void Update();
	void GenerateFood();
	void inputProcess(sf::Event& event);

	Map& GetMap();
	bool IsDrawGrid();
};

#endif
