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

	const std::vector<std::pair<std::string, int>>& GetPlayerData();
	const std::vector<std::pair<std::string, int>>& GetAIData();

private:
	void AddScore(const std::string& p_name, const int& p_score);
	void RewriteFile();

	Snake& m_snake;

	int m_saveLength;
	std::vector<std::pair<std::string, int>> m_playerData;
	std::vector<std::pair<std::string, int>> m_AI_Data;
};

#endif // __SAVE_MANAGER_H__