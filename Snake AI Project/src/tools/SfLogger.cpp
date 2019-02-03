
#include <iostream>

#include "include/tools/SfLogger.h"

//sf::Text Tools::SfLogger::__TEXT;
Tools::SfText Tools::SfLogger::DEFAULT_TEXT;
std::map<std::string, sf::Font> Tools::SfLogger::__FONT_MAP;
//std::string Tools::SfLogger::__STRING;
std::vector<Tools::SfText> Tools::SfLogger::__TEXT_PACK;

Tools::SfLogger::SfLogger()
{
	LoadFont("SAO" ,"ressource/text/font/SAOUITT-Regular.ttf");
}

Tools::SfLogger::~SfLogger()
{
	__TEXT_PACK.clear();
}

void Tools::SfLogger::ResetTextPack()
{
	__TEXT_PACK.clear();
}

void Tools::SfLogger::LoadFont(std::string p_name, std::string p_path)
{
	sf::Font font;
	if (!font.loadFromFile(p_path))
	{
		std::cout << "ERROR : can't load Font \n";
	}
	else
	{
		__FONT_MAP.emplace(p_name, font);
	}
}

sf::Font& Tools::SfLogger::GetFont(std::string p_name)
{
	return __FONT_MAP[p_name];
}

Tools::SfText Tools::SfLogger::GetText(std::string p_text)
{
	for (auto element : __TEXT_PACK)
	{
		if (element.GetText().getString() == p_text)
			return element;
	}
	std::cout << "error in 'GetText' : text not found \n";
	return SfText();
}

Tools::SfText Tools::SfLogger::GetLastText()
{
	return __TEXT_PACK.back();
}

//sf::FloatRect Tools::SfLogger::GetLastTextBounds()
//{
//	return __TEXT_PACK.back().getGlobalBounds();
//}
//
//sf::FloatRect Tools::SfLogger::GetTextBounds(std::string p_text)
//{
//	for (auto element : __TEXT_PACK)
//	{
//		if (element.getString() == p_text)
//			return element.getGlobalBounds();
//	}
//	std::cout << "error in 'GetTextBounds' : text not found \n";
//	return sf::FloatRect();
//}
//
//sf::FloatRect Tools::SfLogger::GetTextBounds(std::string p_text, float p_size)
//{
//	__TEXT.setCharacterSize(p_size);
//	__TEXT.setString(p_text);
//	__TEXT.setFont(__FONT_MAP["SAO"]);
//	__TEXT.setStyle(sf::Text::Bold);
//
//	return __TEXT.getGlobalBounds();
//}

sf::Vector2f Tools::SfLogger::GetPositionByOtherText(SfText p_otherText, ETextPosition p_pos, float p_offset, float p_secondOffset)
{
	const sf::Vector2f l_otherTextPos = p_otherText.GetPosition();
	const sf::FloatRect l_otherTextBounds = p_otherText.GetBounds();

	if (p_pos == ETextPosition::Up)
		return sf::Vector2f(l_otherTextPos.x + p_secondOffset, l_otherTextPos.y - l_otherTextBounds.height - p_offset);
	if (p_pos == ETextPosition::Down)
		return sf::Vector2f(l_otherTextPos.x + p_secondOffset, l_otherTextPos.y + l_otherTextBounds.height + p_offset);
	if (p_pos == ETextPosition::Left)
		return sf::Vector2f(l_otherTextPos.x - p_offset, l_otherTextPos.y + p_secondOffset);
	if (p_pos == ETextPosition::Right)
		return sf::Vector2f(l_otherTextPos.x + l_otherTextBounds.width + p_offset, l_otherTextPos.y + p_secondOffset);
	
	return sf::Vector2f();
}

void Tools::SfLogger::Draw(sf::RenderWindow* p_window)
{
	for (uint16_t i = 0; i < __TEXT_PACK.size(); i++)
	{
		p_window->draw(__TEXT_PACK[i].GetText());
	}

	ResetTextPack();
}

void Tools::SfLogger::DrawTextsBounds(sf::RenderWindow* p_window)
{
	sf::RectangleShape boundsShape;
	boundsShape.setFillColor(sf::Color(255, 0, 0, 25));
	boundsShape.setOutlineColor(sf::Color::Red);
	boundsShape.setOutlineThickness(1.0f);

	for (uint16_t i = 0; i < __TEXT_PACK.size(); i++)
	{
		sf::FloatRect bounds = __TEXT_PACK[i].GetBounds();
		boundsShape.setSize(sf::Vector2f(bounds.width, bounds.height));
		boundsShape.setPosition(sf::Vector2f(__TEXT_PACK[i].GetPosition().x + bounds.width * 0.025f,
											 __TEXT_PACK[i].GetPosition().y + bounds.height * 0.225));
		p_window->draw(boundsShape);
	}
}
