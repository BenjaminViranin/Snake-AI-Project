//#include "..\..\include\tools\Animation_Manager.h"
//#include "../../include/manager/Level_Manager.h"
//
//Animation_Manager::Animation_Manager() : m_disolveAlpha(255)
//{
//}
//
//Animation_Manager::~Animation_Manager()
//{
//}
//
//void Animation_Manager::InitAnimationSheet(SpriteSheet* p_animSprite, std::string p_name, sf::Vector2f p_pos, sf::Time p_timeBetweenFrame, char p_spriteNumber, char p_heightSpriteNumber)
//{
//	AnimationSheet as;
//	as._spriteSheet = p_animSprite;
//	as._position = p_pos;
//	as._spriteNumber = p_spriteNumber;
//	as._currentSpriteNumber = 1;
//	as._heightSpriteNumber = p_heightSpriteNumber;
//	as._currentWidthSprite = 1;
//	as._currentHeightSptite = 1;
//	as._timeBetweenFrame = p_timeBetweenFrame;
//	as._frameTimer = sf::seconds(0);
//	m_AnimationSheetPack.emplace(p_name, as);
//}
//
//bool Animation_Manager::PlayAnimation(std::string p_name, sf::Vector2f p_pos, sf::RenderWindow* p_window)
//{
//	if (Level_Manager::m_levelSpeedAcceleration > 0)
//	{
//		if (Time::clockFromStart.getElapsedTime() - m_AnimationSheetPack[p_name]._frameTimer >= m_AnimationSheetPack[p_name]._timeBetweenFrame / Level_Manager::m_levelSpeedAcceleration)
//		{
//			m_AnimationSheetPack[p_name]._currentWidthSprite++;
//			m_AnimationSheetPack[p_name]._currentSpriteNumber++;
//			if (m_AnimationSheetPack[p_name]._currentWidthSprite > m_AnimationSheetPack[p_name]._spriteSheet->_widthSpriteNumber
//				|| m_AnimationSheetPack[p_name]._currentSpriteNumber > m_AnimationSheetPack[p_name]._spriteNumber)
//			{
//				m_AnimationSheetPack[p_name]._currentWidthSprite = 1;
//				m_AnimationSheetPack[p_name]._currentSpriteNumber = 1;
//				if (m_AnimationSheetPack[p_name]._heightSpriteNumber > 1)
//				{
//					m_AnimationSheetPack[p_name]._currentHeightSptite++;
//					if (m_AnimationSheetPack[p_name]._currentHeightSptite > m_AnimationSheetPack[p_name]._spriteSheet->_heightSpriteNumber)
//					{
//						m_AnimationSheetPack[p_name]._currentHeightSptite = 1;
//					}
//				}
//			}
//			m_AnimationSheetPack[p_name]._frameTimer = Time::clockFromStart.getElapsedTime();
//		}
//	}
//
//	m_AnimationSheetPack[p_name]._spriteSheet->_sprite.GetSprite().setTextureRect(
//			sf::IntRect(m_AnimationSheetPack[p_name]._position.x + (m_AnimationSheetPack[p_name]._currentWidthSprite - 1) 
//					    * m_AnimationSheetPack[p_name]._spriteSheet->_individualTextureSize.x,
//					    m_AnimationSheetPack[p_name]._position.y + (m_AnimationSheetPack[p_name]._currentHeightSptite - 1) 
//						* m_AnimationSheetPack[p_name]._spriteSheet->_individualTextureSize.y,
//						m_AnimationSheetPack[p_name]._spriteSheet->_individualTextureSize.x,
//						m_AnimationSheetPack[p_name]._spriteSheet->_individualTextureSize.y));
//
//	m_AnimationSheetPack[p_name]._spriteSheet->_sprite.SetPosition(p_pos);
//
//	m_AnimationSheetPack[p_name]._spriteSheet->_sprite.GetSprite().setOrigin(m_AnimationSheetPack[p_name]._spriteSheet->_individualTextureSize.x * 0.5f, 
//																				m_AnimationSheetPack[p_name]._spriteSheet->_individualTextureSize.y * 0.5f);
//
//	p_window->draw(m_AnimationSheetPack[p_name]._spriteSheet->_sprite.GetSprite());
//
//	return m_AnimationSheetPack[p_name]._currentSpriteNumber == 1 ? true : false;
//}
//
//bool Animation_Manager::PlayAnimWithDisolveEffect(std::string p_name, sf::Vector2f p_pos, sf::Time p_disolveTime, sf::RenderWindow * p_window)
//{
//	if (m_AnimationSheetPack[p_name]._currentSpriteNumber < m_AnimationSheetPack[p_name]._spriteNumber)
//	{
//		if (Level_Manager::m_levelSpeedAcceleration > 0)
//		{
//			if (Time::clockFromStart.getElapsedTime() - m_AnimationSheetPack[p_name]._frameTimer >= m_AnimationSheetPack[p_name]._timeBetweenFrame / Level_Manager::m_levelSpeedAcceleration)
//			{
//				m_AnimationSheetPack[p_name]._currentWidthSprite++;
//				m_AnimationSheetPack[p_name]._currentSpriteNumber++;
//				if (m_AnimationSheetPack[p_name]._currentWidthSprite > m_AnimationSheetPack[p_name]._spriteSheet->_widthSpriteNumber)
//				{
//					m_AnimationSheetPack[p_name]._currentWidthSprite = 1;
//					if (m_AnimationSheetPack[p_name]._heightSpriteNumber > 1)
//					{
//						m_AnimationSheetPack[p_name]._currentHeightSptite++;
//						if (m_AnimationSheetPack[p_name]._currentHeightSptite > m_AnimationSheetPack[p_name]._spriteSheet->_heightSpriteNumber)
//						{
//							m_AnimationSheetPack[p_name]._currentHeightSptite = 1;
//						}
//					}
//				}
//				m_AnimationSheetPack[p_name]._frameTimer = Time::clockFromStart.getElapsedTime();
//			}
//		}
//	}
//	else
//	{
//		if (Level_Manager::m_levelSpeedAcceleration > 0)
//		{
//			if (Time::clockFromStart.getElapsedTime() - m_AnimationSheetPack[p_name]._frameTimer 
//				>= (sf::milliseconds( p_disolveTime.asMilliseconds() / 255)) / Level_Manager::m_levelSpeedAcceleration)
//			{
//				--m_disolveAlpha;
//				m_AnimationSheetPack[p_name]._spriteSheet->_sprite.GetSprite().setColor(sf::Color(255, 255, 255, m_disolveAlpha));
//
//				m_AnimationSheetPack[p_name]._frameTimer = Time::clockFromStart.getElapsedTime();
//			}
//		}
//	}
//
//	m_AnimationSheetPack[p_name]._spriteSheet->_sprite.GetSprite().setTextureRect(
//		sf::IntRect(m_AnimationSheetPack[p_name]._position.x + (m_AnimationSheetPack[p_name]._currentWidthSprite - 1)
//			* m_AnimationSheetPack[p_name]._spriteSheet->_individualTextureSize.x,
//			m_AnimationSheetPack[p_name]._position.y + (m_AnimationSheetPack[p_name]._currentHeightSptite - 1)
//			* m_AnimationSheetPack[p_name]._spriteSheet->_individualTextureSize.y,
//			m_AnimationSheetPack[p_name]._spriteSheet->_individualTextureSize.x,
//			m_AnimationSheetPack[p_name]._spriteSheet->_individualTextureSize.y));
//
//	m_AnimationSheetPack[p_name]._spriteSheet->_sprite.SetPosition(p_pos);
//
//	m_AnimationSheetPack[p_name]._spriteSheet->_sprite.GetSprite().setOrigin(m_AnimationSheetPack[p_name]._spriteSheet->_individualTextureSize.x * 0.5f,
//		m_AnimationSheetPack[p_name]._spriteSheet->_individualTextureSize.y * 0.5f);
//
//	p_window->draw(m_AnimationSheetPack[p_name]._spriteSheet->_sprite.GetSprite());
//
//	return m_disolveAlpha == 0 ? true : false;
//}
