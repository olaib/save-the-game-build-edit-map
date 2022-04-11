#include "ToolBar.h"
#include <string>
#include <iostream>

const auto CALM_COMPILER = -1;

ToolBar::ToolBar()
{
	for (auto i = int(0); i < NUM_OF_BUTTONS; i++)
	{
		//create buttons
		m_buttons[i]= Object(i, sf::Vector2f(i * 53.f, 3.f), int2char(i));
		m_rectangles[i] = sf::RectangleShape({ 50.f,50.f });
		m_rectangles[i].setFillColor(sf::Color::White);
		m_rectangles[i].setPosition(m_buttons[i].getLoc());
	}
}

//draw the button
void ToolBar::draw(sf::RenderWindow& window, const size_t& indx, const sf::Texture& txtr) const
{
	m_buttons[indx].drawTo(window, txtr);

}

void ToolBar::drawRectangles(sf::RenderWindow& window)
{
	for (auto i = int(0); i < NUM_OF_BUTTONS; i++)
	{
		window.draw(m_rectangles[i]);
	}
}

void ToolBar::setExistence(const size_t index)
{
	m_existsInBoard[index] = (m_existsInBoard[index] == true) ? false : true;
}

bool ToolBar::existsInBoard(const unsigned index) const
{
	if (index < NUM_OF_PLAYERS)
		return m_existsInBoard[index];
	return false;
}


bool ToolBar::mouseOverBtn(const int& indx,const sf::Vector2f& loc)
{
	return m_buttons[indx].isMouseOver(loc);
}

int ToolBar::getIndx(const size_t& indx) const
{
	return m_buttons[indx].getIndx();
}

bool ToolBar::getExistence(const size_t indx) const
{
	return m_existsInBoard[indx];
}

void ToolBar::setExistence(const bool value, const size_t& indx)
{
	m_existsInBoard[indx] = value;
}

void ToolBar::selectedButton(int indx)
{
	for (size_t i = 0; i < NUM_OF_BUTTONS; i++)
	{
		if (i == indx)
			m_rectangles[i].setFillColor(sf::Color::Cyan);
		else
			m_rectangles[i].setFillColor(sf::Color::White);
	}
}

char ToolBar::int2char(const int& indx) const {
	switch (indx) {
	case 0: return 'K';
	case 1: return 'W';
	case 2: return 'M';
	case 3: return 'T';
	case 4: return '#';
	case 5: return '@';
	case 6: return '*';
	case 7: return 'X';
	case 8: return 'F';
	case 9: return '!';
	case 10: return '=';
	}
}
