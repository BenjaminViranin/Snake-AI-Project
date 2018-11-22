#ifndef __SPRITE_H__
#define __SPRITE_H__

#define WHITE 255, 255, 255
#define BLACK 0, 0, 0
#define RED 255, 0, 0
#define GREEN 0, 255, 0
#define BLUE 0, 0, 255
#define YELLOW 255, 255, 0

#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Sprite
{
private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;

public:
	Sprite() = default;
	Sprite(const std::string& p_filename);

	void SetSprite(const std::string & p_filename);
	sf::Sprite& GetSprite();
	
	void SetPosition(sf::Vector2f position);
	void SetPosition(int x, int y);
	sf::Vector2f GetPosition();

	sf::Texture& GetTexture();
	void SetRectangle(sf::IntRect rectangle);
	void SetRectangle(int x, int y, int w, int h);
	
};

struct SpriteSheet
{
	Sprite _sprite;
	char _widthSpriteNumber;
	char _heightSpriteNumber;
	sf::Vector2f _individualTextureSize;

	void Init(std::string p_path, int p_Wnb, int p_Hnb, float p_scalePurpose)
	{
		_sprite.SetSprite(p_path);
		_sprite.GetSprite().scale(p_scalePurpose / _sprite.GetSprite().getTexture()->getSize().x * p_Wnb,
								  p_scalePurpose / _sprite.GetSprite().getTexture()->getSize().y * p_Hnb);
		_widthSpriteNumber = p_Wnb;
		_heightSpriteNumber = p_Hnb;
		_individualTextureSize.x = _sprite.GetSprite().getTexture()->getSize().x / static_cast<float>(p_Wnb);
		_individualTextureSize.y = _sprite.GetSprite().getTexture()->getSize().y / static_cast<float>(p_Hnb);
	}
};

struct LifeSprite
{
	sf::RectangleShape _bar;
	sf::RectangleShape _box;

	void Init(sf::Vector2f p_textureSize)
	{
		_box.setSize(sf::Vector2f(p_textureSize.x, p_textureSize.x / 12));
		_box.setFillColor(sf::Color(0, 0, 0, 0));
		_box.setOutlineColor(sf::Color(169, 169, 169));
		_box.setOutlineThickness(2);
		_bar.setSize(sf::Vector2f(p_textureSize.x, p_textureSize.x / 12));
		_bar.setFillColor(sf::Color::Red);
	}

	void SetPosition(sf::Vector2f pos)
	{
		_box.setPosition(sf::Vector2f(pos.x, pos.y - _box.getSize().y));
		_bar.setPosition(sf::Vector2f(pos.x, pos.y - _box.getSize().y));
	}
};

#endif