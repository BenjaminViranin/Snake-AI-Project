
#include <iostream>

#include "include/tools/SfLogger.h"

Tools::SfText Tools::SfLogger::__DEFAULT_TEXT;
std::map<std::string, sf::Font> Tools::SfLogger::__FONT_MAP;
std::vector<std::reference_wrapper<Tools::SfText>> Tools::SfLogger::__TEXT_PACK;

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

void Tools::SfLogger::Save(SfText& p_text)
{
	__TEXT_PACK.emplace_back(p_text);
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
		if (element.get().GetText().getString() == p_text)
			return element;
	}
	std::cout << "error in 'GetText' : text not found \n";
	return SfText();
}

Tools::SfText Tools::SfLogger::GetLastText()
{
	return __TEXT_PACK.back().get();
}

void Tools::SfLogger::Draw(sf::RenderWindow* p_window)
{
	for (uint16_t i = 0; i < __TEXT_PACK.size(); i++)
	{
		p_window->draw(__TEXT_PACK[i].get().GetText());
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
		sf::FloatRect bounds = __TEXT_PACK[i].get().GetBounds();
		boundsShape.setSize(sf::Vector2f(bounds.width, bounds.height));
		boundsShape.setPosition(sf::Vector2f(__TEXT_PACK[i].get().GetPosition().x + bounds.width * 0.025f,
											 __TEXT_PACK[i].get().GetPosition().y + bounds.height * 0.225));
		p_window->draw(boundsShape);
	}
}
