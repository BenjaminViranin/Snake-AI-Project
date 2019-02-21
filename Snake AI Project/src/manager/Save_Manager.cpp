
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
	int l_linesNumber = 0;

	std::ifstream readFile;
	std::ofstream writeFile;
	std::string line;

	readFile.open("Save/HighScores.txt");
	if (readFile.is_open())
	{
		while (getline(readFile, line))
			++l_linesNumber;
		readFile.close();
	}
	else std::cout << "Unable to open file";

	writeFile.open("Save/HighScores.txt", std::fstream::app);
	if (writeFile.is_open())
	{
		std::string name = "Benji";
		std::string score = ":" + std::to_string(m_snake.GetScore());
		if (l_linesNumber <= m_saveLength)
		{
			std::string data = "\n" + name + score;
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

			m_saveData.emplace_back(std::pair<std::string, int>(name, score));
		}
		readFile.close();
	}
	else std::cout << "Unable to open file";
}

std::vector<std::pair<std::string, int>>& Save_Manager::GetData()
{
	return m_saveData;
}
