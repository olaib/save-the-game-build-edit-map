#pragma once 
#include<vector>
#include <SFML/Graphics.hpp>
const auto CALM_COMPILER = -1;

class Board {
public:
	Board();
	bool openBoard();
	void readBoard();
	const unsigned int& getHeight()const;
	const unsigned int& getWidth()const;
	void drawBrd(sf::RenderWindow& window, const bool mousePressed, const sf::Vector2f loc);
	void saveLevel();
	bool isLocValid(const sf::Vector2f& loc) const;
	char getCell(const size_t row, const size_t col);
	bool boardisExist()const;
	void clearBoard();
	void printMsg();
	sf::Vector2f getObjectLoc(const sf::Vector2f& loc, size_t &row, size_t &col);
	void setCell(const size_t& row, const size_t& col, const char value);
	int char2int(const char& c) const;

private:
	unsigned int m_height, m_weidth;
	sf::RectangleShape m_WhtBoard;
	std::vector<std::vector<char>> m_holdBoard;
	bool m_BoardisExist = true;
	void newWindow();
};
