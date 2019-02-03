#pragma once

#ifndef __SF_LOGGER_H__
#define __SF_LOGGER_H__

#include <sstream>
#include <vector>
#include <map>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "tools/SfText.h"

namespace Tools
{
	enum class ETextPosition
	{
		Up,
		Down,
		Left,
		Right
	};

	class SfLogger
	{
	public:
		SfLogger();
		~SfLogger();

		template<typename P1, typename ... Param>
		static void Print(int p_size, const sf::Color p_color, const sf::Vector2f p_position,
			const P1 &p1, const Param& ... param)
		{
			DEFAULT_TEXT.SetSize(p_size);
			DEFAULT_TEXT.SetColor(p_color);

			DEFAULT_TEXT.SetPosition(p_position);

			DEFAULT_TEXT.SetText(p1, param...);

			//__TEXT.setString(__STRING);

			DEFAULT_TEXT.SetFont(__FONT_MAP["SAO"]);

			__TEXT_PACK.push_back(DEFAULT_TEXT);
		}

		static void Print(SfText p_text)
		{
			__TEXT_PACK.push_back(p_text);
		}

		static void LoadFont(std::string p_name, std::string p_path);
		static sf::Font& GetFont(std::string p_name);

		static SfText GetText(std::string p_text);
		static SfText GetLastText();
		//static sf::FloatRect GetLastTextBounds();
		//static sf::FloatRect GetTextBounds(std::string p_text);
		//static sf::FloatRect GetTextBounds(std::string p_text, float p_size);
		static sf::Vector2f GetPositionByOtherText(SfText p_otherText, ETextPosition p_pos, float p_offset, float p_secondOffset = 0.0f);

		/* Draw and clear */
		static void Draw(sf::RenderWindow* p_window);
		/* Must be call before method Draw */
		static void DrawTextsBounds(sf::RenderWindow* p_window);

	private:
		/*static void ParamToString() {}

		template<typename P1, typename ... Param>
		static void ParamToString(const P1 &p1, const Param& ... param)
		{
			std::stringstream ss;
			ss << p1;
			__STRING += ss.str();

			ParamToString(param...);
		}
*/
		static void ResetTextPack();

	private:

		static SfText DEFAULT_TEXT;
		/*static sf::Text __TEXT;
		static std::string __STRING;*/

		static std::map<std::string, sf::Font> __FONT_MAP;
		static std::vector<SfText> __TEXT_PACK;
	};
}

#endif // __SF_LOGGER_H__