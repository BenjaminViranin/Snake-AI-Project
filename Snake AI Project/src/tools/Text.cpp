
#include <iostream>

#include "include/tools/Text.h"

using namespace Tools;

sf::Text Text::__TEXT;
sf::Font Text::__FONT;
std::string Text::__STRING;
std::vector<sf::Text> Text::__TEXT_PACK;

bool Text::__SIZE_DEFINED = false;
bool Text::__COLOR_DEFINED = false;
bool Text::__POSITION_DEFINED = false;

Text::Text()
{
	if (!__FONT.loadFromFile("ressource/text/font/SAOUITT-Regular.ttf"))
	{
		std::cout << "ERROR : can't load Font \n";
	}
}

Tools::Text::~Text()
{
	__TEXT_PACK.clear();
}

std::vector<sf::Text>& Text::Get_textPack()
{
	return __TEXT_PACK;
}

void Text::ResetTextPack()
{
	__TEXT_PACK.clear();
}

sf::Text Tools::Text::GetText(std::string p_text)
{
	for (auto element : __TEXT_PACK)
	{
		if (element.getString() == p_text)
			return element;
	}
	std::cout << "error in 'GetText' : text not found \n";
	return sf::Text();
}

sf::Text Tools::Text::GetLastText()
{
	return __TEXT_PACK.back();
}

sf::FloatRect Tools::Text::GetLastTextBounds()
{
	return __TEXT_PACK.back().getGlobalBounds();
}

sf::FloatRect Tools::Text::GetTextBounds(std::string p_text)
{
	for (auto element : __TEXT_PACK)
	{
		if (element.getString() == p_text)
			return element.getGlobalBounds();
	}
	std::cout << "error in 'GetTextBounds' : text not found \n";
	return sf::FloatRect();
}

sf::FloatRect Tools::Text::GetTextBounds(std::string p_text, float p_size)
{
	__TEXT.setCharacterSize(p_size);
	__TEXT.setString(p_text);
	__TEXT.setFont(__FONT);
	__TEXT.setStyle(sf::Text::Bold);

	return __TEXT.getGlobalBounds();
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
	for (uint16_t i = 0; i < __TEXT_PACK.size(); i++)
	{
		p_window->draw(__TEXT_PACK[i]);
	}

	ResetTextPack();
}

void Tools::Text::DrawTextsBounds(sf::RenderWindow* p_window)
{
	sf::RectangleShape boundsShape;
	boundsShape.setFillColor(sf::Color(255, 0, 0, 25));
	boundsShape.setOutlineColor(sf::Color::Red);
	boundsShape.setOutlineThickness(1.0f);

	for (uint16_t i = 0; i < __TEXT_PACK.size(); i++)
	{
		sf::FloatRect bounds = __TEXT_PACK[i].getGlobalBounds();
		boundsShape.setSize(sf::Vector2f(bounds.width, bounds.height));
		boundsShape.setPosition(sf::Vector2f(__TEXT_PACK[i].getPosition().x + bounds.width * 0.025f,
											 __TEXT_PACK[i].getPosition().y + bounds.height * 0.225));
		p_window->draw(boundsShape);
	}
}
