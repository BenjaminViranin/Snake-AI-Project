#pragma once

#ifndef __SAVE_MANAGER_H__
#define __SAVE_MANAGER_H__

#include <string>
#include <vector>

#include "entity/Snake.h"

class Save_Manager
{
public:
	Save_Manager(Snake& p_snake);
	~Save_Manager();

	void SaveScore();
	void LoadSave();

	std::vector<std::pair<std::string, int>>& GetData();

private:
	Snake& m_snake;

	int m_saveLength;
	std::vector<std::pair<std::string, int>> m_saveData;
};

#endif // __SAVE_MANAGER_H__