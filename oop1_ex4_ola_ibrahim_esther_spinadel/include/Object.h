#pragma once 
#include <SFML/Graphics.hpp>


class Object {
public:
	Object();
	Object(const int& indx, const sf::Vector2f& pos, const char &chr);
	void drawTo(sf::RenderWindow& windows, const sf::Texture& txtr)const;
	bool isMouseOver(const sf::Vector2f& loc);
	sf::Vector2f getLoc() const;
	void setLoc(const sf::Vector2f& pos);
	int getIndx() const;
	char getChar()const;
private:
	int m_indx = -1;
	sf::Vector2f m_location;
	char m_chr;
};