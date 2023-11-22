#pragma once
#include "cell.cpp"
#include <SFML/Graphics.hpp>
#include <vector>


class Board{
    int _columns;
    int _rows;
    int _mines;
    int _width;
    int _height;
    bool _debug;
    sf::Texture faceHappyTexture;
    sf::Sprite mainSprite;
    sf::Texture flaggedTexture;
    sf::Texture tileHiddenTexture;
    sf::Texture tileRevealedTexture;
    sf::Texture num1Texture;
    sf::Texture flagTexture;
    sf::Texture happyFaceTexture;
    sf::Texture faceWinTexture;
    sf::Texture faceLostTexture;
    sf::Texture digitsTexture;
    sf::Texture debugTexture;
    sf::Texture test1, test2, test3;
    sf::Texture mineTexture;
    sf::Texture num2Texture;
    sf::Texture num3Texture;
    sf::Texture num4Texture;
    sf::Texture num5Texture;
    sf::Texture num6Texture;
    sf::Texture num7Texture;
    sf::Texture num8Texture;
     bool _gameover;



public:
   bool gameOver();

   void SwitchDebug();
    void revealAdjacent(int row, int col);  

    void debugCells();
    void flagCell(int row, int col);
    sf::Sprite DebugButton;
    sf::Sprite WinButton;
    sf::Sprite MinesCountButton;
   
    std::vector<std::vector<Cell*> > cells;
    Board(int columns, int rows, int mines, int width, int height);
    void addMines();
    void drawBoard(sf::RenderWindow& window);

    void setTexture(int i, int j);
    void GameLoop(int row, int col);

    void boardSet();
    std::vector<std::pair<int, int> > generateRandomNumbers();
    int checkMines();

    







};
