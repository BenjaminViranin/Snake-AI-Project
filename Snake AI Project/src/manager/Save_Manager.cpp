
#include "manager/Save_Manager.h"

#include <iostream>
#include <fstream>

Save_Manager::Save_Manager(Snake& p_snake) :
m_snake(p_snake),
m_saveLength(20)
{
}

Save_Manager::~Save_Manager()
{
}

void Save_Manager::SaveScore()
{
	const std::string name = m_snake.IsAIActive() ? "AI" : "Player";
	const int score = m_snake.GetScore();

	LoadSave();

	if (m_AI_Data.size() + m_playerData.size() < m_saveLength)
	{
		AddScore(name, score);
	}
	else
	{
		auto& currentDataPack = m_snake.IsAIActive() ? m_AI_Data : m_playerData;

		if (score > currentDataPack.back().second)
		{
			currentDataPack.back().first = name;
			currentDataPack.back().second = score;

			RewriteFile();
		}
	}
}

void Save_Manager::AddScore(const std::string& p_name, const int& p_score)
{
	std::ofstream writeFile;

	writeFile.open("Save/HighScores.txt", std::fstream::app);
	if (writeFile.is_open())
	{
		std::string data = "\n" + p_name + ":" + std::to_string(p_score);
		writeFile << data;

		writeFile.close();
	}
	else std::cout << "Unable to open file";
}

void Save_Manager::RewriteFile()
{
	std::ofstream writeFile;

	writeFile.open("Save/HighScores.txt", std::fstream::app);
	if (writeFile.is_open())
	{
		for (auto element : m_playerData)
		{
			std::string data = "\n" + element.first + ":" + std::to_string(element.second);
			writeFile << data;
		}

		for (auto element : m_AI_Data)
		{
			std::string data = "\n" + element.first + ":" + std::to_string(element.second);
			writeFile << data;
		}

		writeFile.close();
	}
	else std::cout << "Unable to open file";
}

void Save_Manager::LoadSave()
{
	std::ifstream readFile;
	std::string line;

	std::string name;
	int score;

	readFile.open("Save/HighScores.txt");
	if (readFile.is_open())
	{
		while (getline(readFile, line))
		{
			bool isName = true;

			for (auto c : line)
			{
				if (c == ':')
				{
					isName = false;
					continue;
				}
				if (isName)
					name += c;
				else
					score = 0;
			}

			if (name == "AI")
				m_AI_Data.emplace_back(std::pair<std::string, int>(name, score));
			else
				m_playerData.emplace_back(std::pair<std::string, int>(name, score));
		}

		std::sort(m_AI_Data.begin(), m_AI_Data.end());
		std::sort(m_playerData.begin(), m_playerData.end());

		readFile.close();
	}
	else std::cout << "Unable to open file";
}

const std::vector<std::pair<std::string, int>>& Save_Manager::GetPlayerData()
{
	return m_playerData;
}

const std::vector<std::pair<std::string, int>>& Save_Manager::GetAIData()
{
	return m_AI_Data;
}
