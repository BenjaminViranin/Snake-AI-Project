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
	class SfLogger
	{
	public:
		SfLogger();
		~SfLogger();

		template<typename P1, typename ... Param>
		static void Save(int p_size, const sf::Color p_color, const sf::Vector2f p_position,
			const P1 &p1, const Param& ... param)
		{
			__DEFAULT_TEXT.SetSize(p_size);
			__DEFAULT_TEXT.SetColor(p_color);
			__DEFAULT_TEXT.SetPosition(p_position);
			__DEFAULT_TEXT.SetText(p1, param...);
			__DEFAULT_TEXT.SetFont(__FONT_MAP["SAO"]);

			__TEMPORARY_TEXT_PACK.push_back(__DEFAULT_TEXT);
		}

		static void			Save(SfText& p_text);

		static void			LoadFont(std::string p_name, std::string p_path);
		static sf::Font&	GetFont(std::string p_name);

		static SfText		GetText(std::string p_text);

		/* Draw and clear */
		static void			Draw(sf::RenderWindow* p_window);
		/* Must be call before method Draw */
		static void			DrawTextsBounds(sf::RenderWindow* p_window);

	private:
		static SfText										__DEFAULT_TEXT;
		static std::map<std::string, sf::Font>				__FONT_MAP;
		static std::vector<SfText>							__TEMPORARY_TEXT_PACK;
		static std::vector<std::reference_wrapper<SfText>>	__STATIC_TEXT_PACK;
	};
}

#endif // __SF_LOGGER_H__