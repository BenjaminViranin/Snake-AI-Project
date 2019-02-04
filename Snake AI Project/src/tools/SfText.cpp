
#include "tools/SfText.h"

Tools::SfText::SfText()
{
	TEXT.setCharacterSize(16);
	TEXT.setFillColor(sf::Color::Yellow);
	TEXT.setStyle(sf::Text::Bold);
	TEXT.setPosition(sf::Vector2f());
	TEXT.setString("");
	TEXT_ENCRAGE = ETextEncrage::UpLeft;
	IS_DRAWABLE = true;
}

Tools::SfText::SfText(int p_size, sf::Font p_font, sf::Color p_color, sf::Vector2f p_position, std::string p_text, ETextEncrage p_textEncrage)
{
	TEXT.setCharacterSize(p_size);
	FONT = p_font;
	TEXT.setFont(p_font);
	TEXT.setFillColor(p_color);
	TEXT.setStyle(sf::Text::Bold);
	TEXT.setPosition(p_position);
	TEXT.setString(p_text);
	TEXT_ENCRAGE = p_textEncrage;
	IS_DRAWABLE = true;
}

Tools::SfText::~SfText()
{
}

void Tools::SfText::SetSize(int p_size)
{
	TEXT.setCharacterSize(p_size);
}

void Tools::SfText::SetFont(sf::Font& p_font)
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
		position = sf::Vector2f(p_position.x - TEXT.getGlobalBounds().width,
								p_position.y);
		break;
	case ETextEncrage::DownLeft: 
		position = sf::Vector2f(p_position.x,
								p_position.y - TEXT.getGlobalBounds().height);
		break;
	case ETextEncrage::DownRight: 
		position = sf::Vector2f(p_position.x - TEXT.getGlobalBounds().width,
								p_position.y - TEXT.getGlobalBounds().height);
		break;
	case ETextEncrage::Middle: 
		position = sf::Vector2f(p_position.x - TEXT.getGlobalBounds().width * 0.5f,
								p_position.y - TEXT.getGlobalBounds().height * 0.5f);
		break;
	}

	TEXT.setPosition(position);
}

void Tools::SfText::SetPositionWithOtherText(SfText p_otherText, ETextPosition p_pos, float p_offset, float p_secondOffset)
{
	const sf::Vector2f otherTextPos = p_otherText.GetPosition();
	const sf::FloatRect otherTextBounds = p_otherText.GetBounds();

	switch (p_pos) 
	{ 
	case ETextPosition::Up: 
		SetPosition(sf::Vector2f(otherTextPos.x + p_secondOffset, otherTextPos.y - otherTextBounds.height - p_offset));
		break;
	case ETextPosition::Down: 
		SetPosition(sf::Vector2f(otherTextPos.x + p_secondOffset, otherTextPos.y + otherTextBounds.height + p_offset));
		break;
	case ETextPosition::Left: 
		SetPosition(sf::Vector2f(otherTextPos.x - p_offset, otherTextPos.y + p_secondOffset));
		break;
	case ETextPosition::Right: 
		SetPosition(sf::Vector2f(otherTextPos.x + otherTextBounds.width + p_offset, otherTextPos.y + p_secondOffset));
		break;
	}
}

void Tools::SfText::SetOrigin(ETextEncrage p_textEncrage)
{
	TEXT_ENCRAGE = p_textEncrage;
}

const int& Tools::SfText::GetSize()
{
	return TEXT.getCharacterSize();
}

const sf::Font& Tools::SfText::GetFont()
{
	return FONT;
}

const sf::Color& Tools::SfText::GetColor()
{
	return TEXT.getFillColor();
}

const sf::Vector2f& Tools::SfText::GetPosition()
{
	return TEXT.getPosition();
}

const sf::Text& Tools::SfText::GetText()
{
	return TEXT;
}

const sf::FloatRect Tools::SfText::GetBounds()
{
	return TEXT.getGlobalBounds();
}

bool& Tools::SfText::IsDrawable()
{
	return IS_DRAWABLE;
}
