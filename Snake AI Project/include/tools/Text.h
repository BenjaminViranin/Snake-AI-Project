#pragma once

#ifndef __TEXT_MANAGER_H__
#define __TEXT_MANAGER_H__

#include <sstream>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

namespace Tools
{
	enum class ETextPosition
	{
		Up,
		Down,
		Left,
		Right
	};

	enum class ETextEncrage
	{
		UpLeft,
		UpRight,
		DownLeft,
		DownRight,
		Middle
	};

	class SfLogger
	{
	public:
		SfLogger();
		~SfLogger();

		static std::vector<sf::Text>& Get_textPack();

		static void ParamToString() {}

		template<typename P1, typename ... Param>
		static void ParamToString(const P1 &p1, const Param& ... param)
		{
			std::stringstream ss;
			ss << p1;
			__STRING += ss.str();

			ParamToString(param...);
		}

		template<typename P1, typename ... Param>
		static void Print(int p_size, const sf::Color p_color, const sf::Vector2f p_position,
			const P1 &p1, const Param& ... param)
		{
			__TEXT.setCharacterSize(p_size);
			__TEXT.setFillColor(p_color);

			__TEXT.setPosition(p_position);

			ParamToString(p1, param...);

			__TEXT.setString(__STRING);

			__TEXT.setFont(__FONT);
			__TEXT.setStyle(sf::Text::Bold);

			__TEXT_PACK.push_back(__TEXT);

			__STRING = "";
		}

		template<typename P1, typename ... Param>
		static void PrintDebug(const P1 &p1, const Param& ... param)
		{
			ParamToString(p1, param...);

			if (!__TEXT_PACK.empty())
			{
				if (__TEXT_PACK.back().getPosition().x != 0)
				{
					for (int i = __TEXT_PACK.size() - 1; i >= 0; i--)
					{
						if (__TEXT_PACK[i].getPosition().x == 0)
						{
							__TEXT.setPosition(sf::Vector2f(0, __TEXT_PACK[i].getPosition().y + __TEXT_PACK[i].getCharacterSize()));
							break;
						}
						else
							__TEXT.setPosition(sf::Vector2f(0, 0));
					}
				}
				else
					__TEXT.setPosition(sf::Vector2f(0, __TEXT_PACK.back().getPosition().y + __TEXT_PACK.back().getCharacterSize()));
			}
			else
				__TEXT.setPosition(sf::Vector2f(0, 0));

			__TEXT.setCharacterSize(18);
			__TEXT.setFillColor(sf::Color::Yellow);

			__TEXT.setString(__STRING);

			__TEXT.setFont(__FONT);
			__TEXT.setStyle(sf::Text::Bold);

			__TEXT_PACK.push_back(__TEXT);

			__STRING = "";
		}

		static void ResetTextPack();
		static sf::Text GetText(std::string p_text);
		static sf::Text GetLastText();
		static sf::FloatRect GetLastTextBounds();
		static sf::FloatRect GetTextBounds(std::string p_text);
		static sf::FloatRect GetTextBounds(std::string p_text, float p_size);
		static sf::Vector2f GetPositionByOtherText(std::string p_otherText, ETextPosition p_pos, float p_offset, float p_secondOffset = 0.0f);

		/* Draw and clear */
		static void Draw(sf::RenderWindow* p_window);
		/* Must be call before method Draw */
		static void DrawTextsBounds(sf::RenderWindow* p_window);

	private:

		static sf::Text __TEXT;
		static sf::Font __FONT;
		static std::string __STRING;
		static std::vector<sf::Text> __TEXT_PACK;

		static bool __SIZE_DEFINED;
		static bool __COLOR_DEFINED;
		static bool __POSITION_DEFINED;
	};
}

#endif