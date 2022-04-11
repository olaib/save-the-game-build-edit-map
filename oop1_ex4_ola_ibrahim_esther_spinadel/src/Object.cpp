#include "Object.h"
#include <iostream>

const auto CALM_COMPILER = -1;

Object::Object() : m_location(sf::Vector2f::Vector2()) {}
Object::Object(const int& indx, const sf::Vector2f& pos, const char &chr):m_location(pos), m_indx(indx), m_chr(chr) {}

void Object::drawTo(sf::RenderWindow& window, const sf::Texture& txtr)const
{
	auto sprt = sf::Sprite(txtr);
	sprt.setPosition(m_location);
	window.draw(sprt);
}

bool Object::isMouseOver(const sf::Vector2f& loc)
{
	auto rect = sf::RectangleShape({ 50.f, 50.f });
	rect.setPosition(m_location);
	if(rect.getGlobalBounds().contains(loc)) {
		return true;
	}
	return false;
}

sf::Vector2f Object::getLoc() const
{
	return m_location;
}

void Object::setLoc(const sf::Vector2f& pos)
{
	m_location = pos;
}

int Object::getIndx() const
{
	return m_indx;
}

char Object::getChar() const
{
	return m_chr;
}

