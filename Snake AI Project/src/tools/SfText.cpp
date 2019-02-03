
#include <tools/SfLogger.h>

#include "tools/SfText.h"

Tools::SfText::SfText()
{
	TEXT.setCharacterSize(16);
	TEXT.setFillColor(sf::Color::Yellow);
	TEXT.setPosition(sf::Vector2f());
	TEXT.setString("");
	TEXT_ENCRAGE = ETextEncrage::UpLeft;
}

Tools::SfText::SfText(int p_size, sf::Font p_font, sf::Color p_color, sf::Vector2f p_position, std::string p_text)
{
	TEXT.setCharacterSize(p_size);
	FONT = p_font;
	TEXT.setFont(p_font);
	TEXT.setFillColor(p_color);
	TEXT.setPosition(p_position);
	TEXT.setString(p_text);
}

Tools::SfText::~SfText()
{
}

void Tools::SfText::SetSize(int p_size)
{
	TEXT.setCharacterSize(p_size);
}

void Tools::SfText::SetFont(sf::Font p_font)
{
	FONT = p_font;
	TEXT.setFont(p_font);
}

void Tools::SfText::SetColor(sf::Color p_color)
{
	TEXT.setFillColor(p_color);
}

void Tools::SfText::SetPosition(sf::Vector2f p_position)
{
	sf::Vector2f position;

	switch (TEXT_ENCRAGE) 
	{ 
	case ETextEncrage::UpLeft: 
		position = p_position;
		break;
	case ETextEncrage::UpRight: 
		position = sf::Vector2f(p_position.x + Tools::SfLogger::GetTextBounds("PAUSE", 50).width,
								p_position.y);
		break;
	case ETextEncrage::DownLeft: 
		position = sf::Vector2f(p_position.x,
								p_position.y + Tools::SfLogger::GetTextBounds("PAUSE", 50).height);
		break;
	case ETextEncrage::DownRight: 
		position = sf::Vector2f(p_position.x + Tools::SfLogger::GetTextBounds("PAUSE", 50).width,
								p_position.y + Tools::SfLogger::GetTextBounds("PAUSE", 50).height);
		break;
	case ETextEncrage::Middle: 
		position = sf::Vector2f(p_position.x + Tools::SfLogger::GetTextBounds("PAUSE", 50).width * 0.5f,
								p_position.y + Tools::SfLogger::GetTextBounds("PAUSE", 50).height * 0.5f);
		break;
	default: ;
	}

	TEXT.setPosition(position);
}

void Tools::SfText::SetTextEncrage(ETextEncrage p_textEncrage)
{
	TEXT_ENCRAGE = p_textEncrage;
}

int Tools::SfText::GetSize()
{
	return TEXT.getCharacterSize();
}

sf::Font Tools::SfText::GetFont()
{
	return FONT;
}

sf::Color Tools::SfText::GetColor()
{
	return TEXT.getFillColor();
}

sf::Vector2f Tools::SfText::GetPosition()
{
	return TEXT.getPosition();
}
