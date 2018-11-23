
#include "include/tools/Text.h"

using namespace Tools;

sf::Text Text::m_text;
sf::Font Text::m_font;
std::string Text::m_string;
std::vector<sf::Text> Text::m_textPack;

bool Text::m_sizeDefined = false;
bool Text::m_colorDefined = false;
bool Text::m_positionDefined = false;

Text::Text()
{
	if (!m_font.loadFromFile("ressource/text/font/arial.ttf"))
	{
		std::cout << "ERROR : can't load Font \n";
	}
}

std::vector<sf::Text>& Text::Get_textPack()
{
	return m_textPack;
}

void Text::ResetTextPack()
{
	m_textPack.clear();
}

sf::FloatRect Tools::Text::GetLastTextBounds()
{
	return m_textPack.back().getGlobalBounds();
}

sf::FloatRect Tools::Text::GetTextBounds(std::string p_text)
{
	for (auto element : m_textPack)
	{
		std::string t = element.getString();
		if (t == p_text)
			return element.getGlobalBounds();
	}
	std::cout << "error: text not found \n";
	return sf::FloatRect();
}

void Text::Draw(sf::RenderWindow* p_window)
{
	for (uint16_t i = 0; i < m_textPack.size(); i++)
	{
		p_window->draw(m_textPack[i]);
	}

	ResetTextPack();
}

void Tools::Text::DrawTextsBounds(sf::RenderWindow* p_window)
{
	sf::RectangleShape boundsShape;
	boundsShape.setFillColor(sf::Color(255, 0, 0, 25));
	boundsShape.setOutlineColor(sf::Color::Red);
	boundsShape.setOutlineThickness(1.0f);

	for (uint16_t i = 0; i < m_textPack.size(); i++)
	{
		sf::FloatRect bounds = m_textPack[i].getGlobalBounds();
		boundsShape.setSize(sf::Vector2f(bounds.width, bounds.height));
		boundsShape.setPosition(sf::Vector2f(m_textPack[i].getPosition().x + 1, m_textPack[i].getPosition().y + bounds.height * 0.3));
		p_window->draw(boundsShape);
	}
}
