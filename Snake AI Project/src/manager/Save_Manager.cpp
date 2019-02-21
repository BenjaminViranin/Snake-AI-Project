
#include "manager/Save_Manager.h"

#include <iostream>
#include <fstream>

Save_Manager::Save_Manager(Snake& p_snake) :
m_snake(p_snake),
m_saveLength(10)
{
}

Save_Manager::~Save_Manager()
{
}

void Save_Manager::SaveScore()
{
	LoadSave();

	if (m_snake.IsAIActive())
		SaveAIScore();
	else
		SavePlayerScore();

}

void Save_Manager::SavePlayerScore()
{
	const std::string name = "Player";
	const int score = m_snake.GetScore();

	if (m_playerData.size() < m_saveLength)
	{
		AddScore(name, score);
	}
	else
	{
		if (score > m_playerData.back().second)
		{
			m_playerData.back().first = name;
			m_playerData.back().second = score;

			RewriteFile();
		}
	}
}

void Save_Manager::SaveAIScore()
{
	const std::string name = "AI";
	const int score = m_snake.GetScore();

	if (m_AI_Data.size() < m_saveLength)
	{
		AddScore(name, score);
	}
	else
	{
		if (score > m_AI_Data.back().second)
		{
			m_AI_Data.back().first = name;
			m_AI_Data.back().second = score;

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
		std::string data = p_name + ":" + std::to_string(p_score) + "\n";
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
	std::string score;

	m_AI_Data.clear();
	m_playerData.clear();

	readFile.open("Save/HighScores.txt");
	if (readFile.is_open())
	{
		while (getline(readFile, line))
		{
			name = line.substr(0, line.find(':'));
			score = line.substr(line.find(':') + 1);

			if (name == "AI")
				m_AI_Data.emplace_back(std::pair<std::string, int>(name, std::stoi(score)));
			else
				m_playerData.emplace_back(std::pair<std::string, int>(name, std::stoi(score)));
		}

		std::sort(m_AI_Data.begin(), m_AI_Data.end());
		std::sort(m_playerData.begin(), m_playerData.end());

		readFile.close();
	}
	else std::cout << "Unable to open file";
}

const int& Save_Manager::GetSaveLenght()
{
	return m_saveLength;
}

const std::vector<std::pair<std::string, int>>& Save_Manager::GetPlayerData()
{
	return m_playerData;
}

const std::vector<std::pair<std::string, int>>& Save_Manager::GetAIData()
{
	return m_AI_Data;
}
