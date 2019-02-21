
#include <iostream>

#include "include/tools/SfLogger.h"

Tools::SfText Tools::SfLogger::__DEFAULT_TEXT;
std::map<std::string, sf::Font> Tools::SfLogger::__FONT_MAP;
std::vector<Tools::SfText> Tools::SfLogger::__TEMPORARY_TEXT_PACK;
std::vector<std::reference_wrapper<Tools::SfText>> Tools::SfLogger::__STATIC_TEXT_PACK;

Tools::SfLogger::SfLogger()
{
	LoadFont("SAO" ,"ressource/text/font/SAOUITT-Regular.ttf");
}

Tools::SfLogger::~SfLogger()
{
	__TEMPORARY_TEXT_PACK.clear();
	__STATIC_TEXT_PACK.clear();
}

void Tools::SfLogger::Save(SfText& p_text)
{
	__STATIC_TEXT_PACK.emplace_back(p_text);
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
	for (auto element : __TEMPORARY_TEXT_PACK)
	{
		if (element.GetText().getString() == p_text)
			return element;
	}
	for (auto element : __STATIC_TEXT_PACK)
	{
		if (element.get().GetText().getString() == p_text)
			return element;
	}

	std::cout << "error in 'GetText' : text not found \n";
	return SfText();
}

void Tools::SfLogger::Draw(sf::RenderWindow* p_window)
{
	for (uint16_t i = 0; i < __STATIC_TEXT_PACK.size(); i++)
	{
		if (__STATIC_TEXT_PACK[i].get().IsDrawable())
			p_window->draw(__STATIC_TEXT_PACK[i].get().GetText());
	}
	for (uint16_t i = 0; i < __TEMPORARY_TEXT_PACK.size(); i++)
	{
		if (__TEMPORARY_TEXT_PACK[i].IsDrawable())
			p_window->draw(__TEMPORARY_TEXT_PACK[i].GetText());
	}

	if(!__TEMPORARY_TEXT_PACK.empty())
		__TEMPORARY_TEXT_PACK.clear();
}

void Tools::SfLogger::DrawTextsBounds(sf::RenderWindow* p_window)
{
	sf::RectangleShape boundsShape;
	boundsShape.setFillColor(sf::Color(255, 0, 0, 25));
	boundsShape.setOutlineColor(sf::Color::Red);
	boundsShape.setOutlineThickness(1.0f);

	for (uint16_t i = 0; i < __STATIC_TEXT_PACK.size(); i++)
	{
		if (__STATIC_TEXT_PACK[i].get().IsDrawable())
		{
			sf::FloatRect bounds = __STATIC_TEXT_PACK[i].get().GetBounds();
			boundsShape.setSize(sf::Vector2f(bounds.width, bounds.height));
			boundsShape.setPosition(sf::Vector2f(bounds.left, bounds.top));

			p_window->draw(boundsShape);
		}
	}
	for (uint16_t i = 0; i < __TEMPORARY_TEXT_PACK.size(); i++)
	{
		if (__TEMPORARY_TEXT_PACK[i].IsDrawable())
		{
			sf::FloatRect bounds = __TEMPORARY_TEXT_PACK[i].GetBounds();
			boundsShape.setSize(sf::Vector2f(bounds.width, bounds.height));
			boundsShape.setPosition(sf::Vector2f(bounds.left, bounds.top));

			p_window->draw(boundsShape);
		}
	}
}
