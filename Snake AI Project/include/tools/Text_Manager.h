#pragma once

#ifndef __TEXT_MANAGER_H__
#define __TEXT_MANAGER_H__

#include <iostream>
#include <sstream>
#include <vector>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class Text_Manager
{
public:

	static sf::Text m_text;
	static sf::Font m_font;
	static std::string m_string;
	static std::vector<sf::Text> m_textPack;

	static bool m_sizeDefined;
	static bool m_colorDefined;
	static bool m_positionDefined;

public:
	Text_Manager();
	~Text_Manager() {}

	static std::vector<sf::Text>& Get_textPack();

	static void ParamToString() {}

	template<typename P1, typename ... Param>
	static void ParamToString(const P1 &p1, const Param& ... param)
	{
		std::stringstream ss;
		ss << p1;
		m_string += ss.str();

		ParamToString(param...);
	}

	template<typename P1, typename ... Param>
	static void Print(int p_size, const sf::Color p_color, const sf::Vector2f p_position,
			   const P1 &p1, const Param& ... param)
	{
		m_text.setCharacterSize(p_size);
		m_text.setFillColor(p_color);
		
		m_text.setPosition(p_position);

		ParamToString(p1, param...);

		m_text.setString(m_string);

		m_text.setFont(m_font);
		m_text.setStyle(sf::Text::Bold);

		m_textPack.push_back(m_text);

		m_string = "";
	}

	template<typename P1, typename ... Param>
	static void PrintDebug(const P1 &p1, const Param& ... param)
	{
		ParamToString(p1, param...);

		if (!m_textPack.empty())
		{
			if (m_textPack.back().getPosition().x != 0)
			{
				for (int i = m_textPack.size() - 1; i >= 0; i--)
				{
					if (m_textPack[i].getPosition().x == 0)
					{
						m_text.setPosition(sf::Vector2f(0, m_textPack[i].getPosition().y + m_textPack[i].getCharacterSize()));
						break;
					}
					else
						m_text.setPosition(sf::Vector2f(0, 0));
				}
			}
			else
				m_text.setPosition(sf::Vector2f(0, m_textPack.back().getPosition().y + m_textPack.back().getCharacterSize()));
		}
		else
			m_text.setPosition(sf::Vector2f(0, 0));

		m_text.setCharacterSize(18);
		m_text.setFillColor(sf::Color::Yellow);

		m_text.setString(m_string);

		m_text.setFont(m_font);
		m_text.setStyle(sf::Text::Bold);

		m_textPack.push_back(m_text);

		m_string = "";
	}

	static void ResetTextPack();
	static void Draw(sf::RenderWindow* p_window);
};

#endif