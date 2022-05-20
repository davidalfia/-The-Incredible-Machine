#include "baseImg.h"
#include <iostream>

BaseImg::BaseImg(const sf::Vector2f center, const Type_t objTexture)
{
	sf::Texture *texture = ResourceManager::instance().getTexture(objTexture);
	m_sprite.setTexture(*texture);
	m_sprite.setOrigin(float(texture->getSize().x / 2), float(texture->getSize().y / 2));
	setPosition(center);
}

void BaseImg::setRotation(const float angle)
{
	m_sprite.setRotation(float((angle * 180) / 3.14));
}

sf::FloatRect BaseImg::getGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

void BaseImg::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

sf::Vector2f BaseImg::getLocation() const
{
	return m_sprite.getPosition();
}

void BaseImg::setColor(const sf::Color color)
{
	m_sprite.setColor(color);
}

void BaseImg::setSize(const sf::Vector2u size)
{
	m_sprite.scale((size.x / m_sprite.getGlobalBounds().width), (size.y / m_sprite.getGlobalBounds().height));
}

void BaseImg::setPosition(const sf::Vector2f loc)
{
	m_sprite.setPosition(loc);
}

sf::Vector2f BaseImg::getSize() const
{
	return sf::Vector2f(float(m_sprite.getTextureRect().width),float( m_sprite.getTextureRect().height));
}

void BaseImg::setIntRect(const sf::IntRect newRect)
{
	m_sprite.setTextureRect(newRect);
	m_sprite.setOrigin(getSize().x / 2, getSize().y / 2);
}

void BaseImg::setOrigin(const float x, const float y)
{
	m_sprite.setOrigin(x,y);
}

void BaseImg::setScale(const float scale)
{
	m_sprite.setScale(sf::Vector2f(scale, scale));
}

void BaseImg::drawSmall (sf::RenderTexture& tinyBoard)
{
	auto pos = m_sprite.getPosition();
	auto scale = m_sprite.getScale();
	m_sprite.setScale(sf::Vector2f(BOARDS_RATIO_X,BOARDS_RATIO_Y));
	m_sprite.setPosition(sf::Vector2f(pos.x*BOARDS_RATIO_X, pos.y*BOARDS_RATIO_Y));
	tinyBoard.draw(m_sprite);
	m_sprite.setScale(scale);
	m_sprite.setPosition(pos);
}

void BaseImg::nextIntRect(const int x, const int y)
{
	sf::IntRect newRect = m_sprite.getTextureRect();

	if(x == 0 && y == 0) //no arguments passed
	{
		if(unsigned(newRect.left + newRect.width) < m_sprite.getTexture()->getSize().x)
			newRect.left += newRect.width;
	}
	else
	{
		if(unsigned(newRect.left + newRect.width) < m_sprite.getTexture()->getSize().x)
		{
			newRect.left += newRect.width;
			newRect.width = x;
			newRect.height = y;
		}
		else
			setEndAnimation(true);	
	}
	setIntRect(newRect);
}

void BaseImg::prevIntRect()
{
	sf::IntRect newRect = m_sprite.getTextureRect();
	if (newRect.left - newRect.width >= 0)
		newRect.left -= newRect.width;

	setIntRect(newRect);
}

void BaseImg::setTextureRect(const sf::IntRect intrect)
{
	m_sprite.setTextureRect(intrect);
}

const sf::IntRect& BaseImg::getTextureRect() const
{
	return m_sprite.getTextureRect();
}
