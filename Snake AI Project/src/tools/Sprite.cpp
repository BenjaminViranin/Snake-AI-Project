#include "../../include/tools/Sprite.h"

Sprite::Sprite()
{
}

Sprite::Sprite(const std::string & p_filename)
{
	this->SetSprite(p_filename);
}

void Sprite::SetSprite(const std::string & p_filename)
{
	this->m_texture.loadFromFile(p_filename);
	this->m_sprite.setTexture(m_texture);
}

sf::Sprite& Sprite::GetSprite()
{
	return this->m_sprite;
}

void Sprite::SetPosition(sf::Vector2f position)
{
	this->m_sprite.setPosition(position.x, position.y);
}

void Sprite::SetPosition(int x, int y)
{
	this->m_sprite.setPosition(x, y);
}

sf::Vector2f& Sprite::GetPosition()
{
	sf::Vector2f s = m_sprite.getPosition();
	return s;
}

sf::Texture& Sprite::GetTexture()
{
	return m_texture;
}

void Sprite::SetRectangle(sf::IntRect rectangle)
{
	this->m_sprite.setTextureRect(rectangle);
}

void Sprite::SetRectangle(int x, int y, int w, int h)
{
	this->m_sprite.setTextureRect(sf::IntRect(x, y, w, h));
}