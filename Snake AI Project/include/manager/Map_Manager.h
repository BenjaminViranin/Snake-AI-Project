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
	Map_Coordinate& operator=(Map_Coordinate& p_other){
		this->x = p_other.x;
		this->y = p_other.y;
		return *this;
	}
};

struct Map
{
	int _colunm;
	int _line;

	Map_Coordinate _food;

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

	sf::RectangleShape m_case;
	std::vector<sf::RectangleShape> m_mapBorder;

public:
	Map_Manager();
	~Map_Manager();

	void GenerateMap(int p_witdh, int p_height);
	void DestroyMap();
	void ResetMap();
	void DrawMap(sf::RenderWindow* p_window);
	void inputProcess(sf::Event& event, sf::RenderWindow* p_window);

	Map& GetMap();
};

#endif
