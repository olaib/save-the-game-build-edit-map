#include "Window.h"
#include <iostream>
const auto BACKGROUND_FILE_NAME = "background.png";


Window::Window() :m_window(sf::VideoMode(800, 600), "Save the King"),m_board(Board()),m_toolBar(ToolBar()){
    loadTxtrs();
}

void Window::clearButton()
{
    //clear the characters on board
    m_sprites.clear();
    //set vector of board to empty tile : ' '
    m_board.clearBoard();
    //clear vector
    m_sprites.clear();
    //reset boolian array to false :there are no players on the board
    for (auto i = unsigned int(0); i < NUM_OF_PLAYERS; i++)
        m_toolBar.setExistence(false, i);
}

void Window::deleteObject(sf::Vector2f loc)
{
    //one rectangle for checking if mouse on board
    auto rect = sf::RectangleShape({ 50.f,50.f });
    for (size_t indx = 0; indx < m_sprites.size(); indx++)
    {
        if (m_sprites[indx].isMouseOver(loc)) {
            if (m_sprites[indx].getIndx() < NUM_OF_PLAYERS && m_sprites[indx].getIndx() > -1)
                m_toolBar.setExistence(false, m_sprites[indx].getIndx());
            //find row and col of wanted cell to set it to empty tile
            for (size_t i = 0; i < m_board.getHeight(); i++)
                for (size_t j = 0; j < m_board.getWidth(); j++) {
                    rect.setPosition({ i * 53.f, (j + 1) * 53.f + 3 });
                    //find row and col of current cell to set it to empty tile
                    if (rect.getGlobalBounds().contains(loc))
                        m_board.setCell(i, j, ' ');
                }
            //delete object from vector
            m_sprites.erase(m_sprites.begin() + indx);
            return;

        }
    }
}

void Window::loadTxtrs()
{
    const static std::array<std::string, NUM_OF_BUTTONS> txtrName = {
        "king.png" ,
        "warrior.png",
        "mage.png",
        "theif.png",
        "gate.png",
        "throne.png",
        "fire.png",
        "teleport.png",
        "key.png",
        "orc.png",
        "wall.png",
        "delete.png",
        "clear.png",
        "save.png" 
    };

    auto txtr = sf::Texture::Texture();
    for (auto i =unsigned int(0); i < NUM_OF_BUTTONS; i++)
    {
        txtr.loadFromFile(txtrName[i]);
        if (!txtr.loadFromFile(txtrName[i]))
        {
            std::cerr << "Could not load texture/n";
            return;
        }
        //fill texture in array
        m_txtrs[i]=txtr;
    }
}


void Window::run()
{
    //fill txt file in board
    if (m_board.boardisExist())
        fillObjectInBoard();
    //drawing background
    auto background = (sf::RectangleShape());
    background.setSize(sf::Vector2f(800, 600));
    sf::Texture back_txtr;
    back_txtr.loadFromFile(BACKGROUND_FILE_NAME);
    background.setTexture(&back_txtr);
    auto indx = int();    //for storing current button index
    auto mousePressed = false;
    auto mouseLoc = sf::Vector2f();    //store current location of mouse
    auto rect = sf::RectangleShape({ 50.f, 50.f });    //for printing white floor
    rect.setFillColor(sf::Color::White);

    while (m_window.isOpen())
    {
        m_window.clear();
        m_window.draw(background);
        //draw white rectangles for buttons
        m_toolBar.drawRectangles(m_window);
        for (size_t i = 0; i < m_txtrs.size(); i++) //draw objects of current board
            m_toolBar.draw(m_window, i, m_txtrs[i]);

        m_board.drawBrd(m_window,mousePressed,mouseLoc);        //draw white rectangles for board

        for (auto i = size_t(0); i < m_sprites.size(); ++i)
            m_sprites[i].drawTo(m_window, m_txtrs[m_sprites[i].getIndx()]);
        m_window.display();

        if (auto event = sf::Event{}; m_window.waitEvent(event)){
            switch (event.type){
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::MouseButtonPressed:
                mousePressed = true;
                if (event.mouseButton.button != sf::Mouse::Button::Left)   break;
                //store mouse location
                mouseLoc = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
                for (auto i = int(0); i < NUM_OF_BUTTONS; i++) {
                    auto selected = m_toolBar.mouseOverBtn(i, mouseLoc);
                    if (selected) {
                        indx = i;
                        m_toolBar.selectedButton(i); (i);
                    }
                }
                break;
            case sf::Event::MouseButtonReleased:
                mousePressed = false;
                if (event.mouseButton.button != sf::Mouse::Button::Left)
                    break;
                if (indx == NUM_OF_BUTTONS - 1) { //save button pressed
                    m_board.saveLevel();
                    break;
                }
                if (indx == NUM_OF_BUTTONS - 2) //clear button
                    clearButton();
                if (indx == NUM_OF_BUTTONS - 3) //delete button
                    deleteObject(m_window.mapPixelToCoords(
                        { event.mouseButton.x, event.mouseButton.y }));

                if (indx > -1 && indx < NUM_OF_OBJECTS) {
                    //display message
                    if (indx < NUM_OF_PLAYERS && m_toolBar.getExistence(indx)) {
                        m_board.printMsg();
                        break;
                    }
                    if ((indx < NUM_OF_PLAYERS && !m_toolBar.getExistence(indx)) || (indx > NUM_OF_PLAYERS - 1))
                        if (m_board.isLocValid(m_window.mapPixelToCoords(
                            { event.mouseButton.x, event.mouseButton.y }))){
                            //store wanted row and col for set new object in holdBoard vector
                            auto row = size_t();
                            auto col = size_t();
                            auto wantedcellloc = m_board.getObjectLoc(m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }), row, col);
                            if (wantedcellloc != sf::Vector2f(-1.f, -1.f)) {
                                auto sprt = Object(indx, wantedcellloc, m_toolBar.int2char(indx));
                                m_sprites.push_back(sprt);
                                m_board.setCell(row, col, sprt.getChar());
                                if (indx < NUM_OF_PLAYERS) { m_toolBar.setExistence(true, indx); }
                            }
                        }
                } break;
            }
        }
    }
}

void Window::fillObjectInBoard()
{
    for (size_t i = 0; i < m_board.getHeight(); i++)
        for (size_t j = 0; j < m_board.getWidth(); j++)
            if (m_board.getCell(i, j) != ' ') {
                if (m_board.getCell(i, j) == KING || m_board.getCell(i, j) == WARRIOR ||
                    m_board.getCell(i, j) == MAGE || m_board.getCell(i, j) == THEIF)
                    m_toolBar.setExistence(m_board.char2int(m_board.getCell(i, j)));
                auto objct = Object(m_board.char2int(m_board.getCell(i, j)),
                    { i * 53.f, (j + 1) * 53.f + 3 }, m_board.getCell(i, j));
                m_sprites.push_back(objct);

            }
}
