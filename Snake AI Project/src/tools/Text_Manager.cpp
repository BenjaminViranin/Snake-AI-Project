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
	for (uint16_t i = 0; i < m_textPack.size(); i++)
	{
		p_window->draw(m_textPack[i]);

		/*
		This piece of code show the bounds of the text to print

		sf::FloatRect bounds = m_textPack[i].getGlobalBounds();
		sf::RectangleShape rectShape(sf::Vector2f(bounds.width, bounds.height));
		rectShape.setPosition(m_textPack[i].getPosition());
		p_window->draw(rectShape);
		*/
	}

	ResetTextPack();
}
