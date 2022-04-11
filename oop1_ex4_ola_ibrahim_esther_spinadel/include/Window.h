#pragma once
#include "Board.h"
#include "ToolBar.h"
#include "Object.h"
#include "Board.h"

enum Players :char {
    KING = 'K',
    WARRIOR = 'W',
    MAGE = 'M',
    THEIF = 'T'
};

class Window {
public:
    Window();
    void clearButton();
    void deleteObject(sf::Vector2f loc);
    void loadTxtrs();
    void run();
    void fillObjectInBoard();
private:
    Board m_board;
    ToolBar m_toolBar;
    sf::RenderWindow m_window;
    std::vector<Object> m_sprites;
    std::array<sf::Texture, NUM_OF_BUTTONS> m_txtrs;

};