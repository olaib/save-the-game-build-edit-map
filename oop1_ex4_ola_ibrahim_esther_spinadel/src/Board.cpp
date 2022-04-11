#include "Board.h"
#include <fstream>
#include <iostream>
#include <string>

const auto FILE_NAME = "Board.txt";

Board::Board() {
	m_WhtBoard.setFillColor(sf::Color::White);
	m_WhtBoard.setSize({ 50.f,50.f });
	if (!openBoard()) {
		newWindow();
		m_WhtBoard.setSize({ 50.f, 50.f });
		m_WhtBoard.setFillColor(sf::Color::White);
		for (size_t i = 0; i < m_height; i++)
		{
			m_holdBoard.push_back(std::vector<char>());
			for (size_t j = 0; j < m_weidth; j++)
				m_holdBoard.back().push_back(' ');
		}
	}
	else
		readBoard();
}

int Board::char2int(const char& c) const {

	switch (c) {
	case 'K': return 0;
	case 'W': return 1;
	case 'M': return 2;
	case 'T': return 3;
	case '#': return 4;
	case '@': return 5;
	case '*': return 6;
	case 'X': return 7;
	case 'F': return 8;
	case '!': return 9;
	case '=': return 10;
	}
	return CALM_COMPILER;

}

void Board::newWindow()
{
	auto window = sf::RenderWindow(sf::VideoMode(600, 100), "msg");
	auto font = sf::Font();
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
	auto msg = sf::Text("enter height and width to create board\n", font);
	msg.setPosition({ 0,0 });

	while (window.isOpen())
	{
		window.clear();
		window.draw(msg);
		window.display();
		std::cin >> m_height >> m_weidth;
		window.close();

		if (auto event = sf::Event{}; window.waitEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
	}
}

char Board::getCell(const size_t row, const size_t col)
{
	return m_holdBoard[row][col];
}

bool Board::boardisExist() const
{
	return m_BoardisExist;
}


void Board::clearBoard()
{
	for (auto i = size_t(0); i < m_height; i++)
		for (auto j = size_t(0); j < m_weidth; j++)
			m_holdBoard[i][j] = ' ';
}

void Board::printMsg()
{
	auto window = sf::RenderWindow(sf::VideoMode(700, 100), "msg");
	auto font = sf::Font();
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
	auto msg = sf::Text("impossible ):,you have to delete the prev one\n", font);
	msg.setPosition({ 0,0 });
	while (window.isOpen())
	{
		window.clear();
		window.draw(msg);
		window.display();
		if (auto event = sf::Event{}; window.waitEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
	}
}

bool Board::isLocValid(const sf::Vector2f& loc) const
{
	return(loc.x > -1 && loc.x < (m_weidth * 53 - 3) && loc.y > 53 && loc.y < ((m_weidth + 1) * 53 - 3)) ? true : false;
}

sf::Vector2f Board::getObjectLoc(const sf::Vector2f& loc, size_t& row, size_t& col)
{
	auto rect = sf::RectangleShape({ 50.f, 50.f });
	for (row = 0; row < m_height; row++)
		for (col = 0; col < m_weidth; col++) {
			rect.setPosition({ row * 53.f, (col + 1) * 53.f + 3 });
			if (rect.getGlobalBounds().contains(loc) && m_holdBoard[row][col] == ' ')
				return rect.getPosition();
		}
	return sf::Vector2f( -1.f,-1.f );
}

void Board::setCell(const size_t& row, const size_t& col, const char value)
{
	m_holdBoard[row][col] = value;
}

bool Board::openBoard()
{
	std::ifstream file(FILE_NAME);
	if (file.is_open())
		return true;
	return false;
}

void Board::readBoard()
{
	std::ifstream file;
	auto line = std::string();
	file.open(FILE_NAME);
	if (!file.is_open())
	{
		std::cerr << "Cannot open FILE_NAME" << std::endl;
		return;
	}
	auto j = size_t(0);
	for (; std::getline(file, line); j++)
	{
		m_holdBoard.push_back(std::vector<char>());
		for (size_t i = 0; i < line.size(); i++)

			m_holdBoard.back().push_back(line[i]);
	}
	m_height =(unsigned int) m_holdBoard.size();
	m_weidth =(unsigned int) m_holdBoard[0].size();
}

const unsigned int& Board::getHeight() const
{
	return m_height;
}

const unsigned int& Board::getWidth() const
{
	return m_weidth;
}

//draw white board
void Board::drawBrd(sf::RenderWindow& window, const bool mousePressed,const sf::Vector2f loc)
{
	for (auto i = size_t(0); i < m_height; i++)
		for (auto j = size_t(0); j < m_weidth; j++) {
			m_WhtBoard.setPosition({ i * 53.f, (j + 1) * 53.f + 3 });
			if (loc != sf::Vector2f{ -1,-1 })
				if (m_WhtBoard.getGlobalBounds().contains(loc)&& mousePressed)
					m_WhtBoard.setFillColor(sf::Color::Cyan);
			window.draw(m_WhtBoard);
			m_WhtBoard.setFillColor(sf::Color::White);
		}
}

void Board::saveLevel()
{
	std::ofstream file;
	file.open(FILE_NAME);
	if (!file.is_open())
	{
		std::cerr << "Cannot open FILE_NAME" << std::endl;
		return;
	}
	for (size_t i = 0; i < m_height; i++) {
		for (size_t j = 0; j < m_weidth; j++)
			file << m_holdBoard[i][j];
		file << std::endl;
	}
}