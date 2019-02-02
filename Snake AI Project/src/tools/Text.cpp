
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
	if (!m_font.loadFromFile("ressource/text/font/SAOUITT-Regular.ttf"))
	{
		std::cout << "ERROR : can't load Font \n";
	}
}

Tools::Text::~Text()
{
	m_textPack.clear();
}

std::vector<sf::Text>& Text::Get_textPack()
{
	return m_textPack;
}

void Text::ResetTextPack()
{
	m_textPack.clear();
}

sf::Text Tools::Text::GetText(std::string p_text)
{
	for (auto element : m_textPack)
	{
		if (element.getString() == p_text)
			return element;
	}
	std::cout << "error in 'GetText' : text not found \n";
	return sf::Text();
}

sf::Text Tools::Text::GetLastText()
{
	return m_textPack.back();
}

sf::FloatRect Tools::Text::GetLastTextBounds()
{
	return m_textPack.back().getGlobalBounds();
}

sf::FloatRect Tools::Text::GetTextBounds(std::string p_text)
{
	for (auto element : m_textPack)
	{
		if (element.getString() == p_text)
			return element.getGlobalBounds();
	}
	std::cout << "error in 'GetTextBounds' : text not found \n";
	return sf::FloatRect();
}

sf::FloatRect Tools::Text::GetTextBounds(std::string p_text, float p_size)
{
	m_text.setCharacterSize(p_size);
	m_text.setString(p_text);
	m_text.setFont(m_font);
	m_text.setStyle(sf::Text::Bold);

	return m_text.getGlobalBounds();
}

sf::Vector2f Tools::Text::GetPositionByOtherText(std::string p_otherText, std::string p_pos, float p_offset, float p_secondOffset)
{
	const sf::Vector2f l_otherTextPos = GetText(p_otherText).getPosition();
	const sf::FloatRect l_otherTextBounds = GetTextBounds(p_otherText);

	if (p_pos == UP)
		return sf::Vector2f(l_otherTextPos.x + p_secondOffset, l_otherTextPos.y - l_otherTextBounds.height - p_offset);
	if (p_pos == DOWN)
		return sf::Vector2f(l_otherTextPos.x + p_secondOffset, l_otherTextPos.y + l_otherTextBounds.height + p_offset);
	if (p_pos == LEFT)
		return sf::Vector2f(l_otherTextPos.x - p_offset, l_otherTextPos.y + p_secondOffset);
	if (p_pos == RIGHT)
		return sf::Vector2f(l_otherTextPos.x + l_otherTextBounds.width + p_offset, l_otherTextPos.y + p_secondOffset);

	std::cout << "Error in 'GetPositionByOtherText' \n";
	return sf::Vector2f();
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
		boundsShape.setPosition(sf::Vector2f(m_textPack[i].getPosition().x + bounds.width * 0.025f,
											 m_textPack[i].getPosition().y + bounds.height * 0.225));
		p_window->draw(boundsShape);
	}
}
