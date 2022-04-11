#pragma once
#include <array>
#include <SFML/Graphics.hpp>
#include "Object.h"

const auto NUM_OF_BUTTONS = 14;
const auto NUM_OF_PLAYERS = 4;
const auto NUM_OF_OBJECTS = 11;

class ToolBar {
public:
	ToolBar();
	char int2char(const int& indx) const;
	void draw(sf::RenderWindow& window, const size_t& indx, const sf::Texture& txtr) const;
	void drawRectangles(sf::RenderWindow& window);
	bool mouseOverBtn(const int& indx, const sf::Vector2f& loc);
	int getIndx(const size_t& indx) const;
	bool getExistence(const size_t indx)const;
	void setExistence(const bool value, const size_t& indx);
	void saveButton();
	void selectedButton(int indx);
	void setExistence(const size_t index);
private:
	void createBtn(const int& index);
	void addTextures();
	bool existsInBoard(const unsigned index) const;
	std::array<Object, NUM_OF_BUTTONS> m_buttons;
	std::array<bool, NUM_OF_PLAYERS> m_existsInBoard{ false };
	std::array<sf::RectangleShape, NUM_OF_BUTTONS> m_rectangles;
};