#include "../../include/tools/Text_Manager.h"

sf::Text Text_Manager::m_text;
sf::Font Text_Manager::m_font;
std::string Text_Manager::m_string;
std::vector<sf::Text> Text_Manager::m_textPack;

bool Text_Manager::m_sizeDefined = false;
bool Text_Manager::m_colorDefined = false;
bool Text_Manager::m_positionDefined = false;

Text_Manager::Text_Manager()
{
	if (!m_font.loadFromFile("ressource/text/font/arial.ttf"))
	{
		std::cout << "ERROR : can't load Font \n";
	}
}

std::vector<sf::Text>& Text_Manager::Get_textPack()
{
	return m_textPack;
}

void Text_Manager::ResetTextPack()
{
	m_textPack.clear();
}

void Text_Manager::Draw(sf::RenderWindow* p_window)
{
	for (int i = 0; i < m_textPack.size(); i++)
	{
		p_window->draw(m_textPack[i]);
	}
	ResetTextPack();
}
