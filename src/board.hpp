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
    int _cell_width;
    int _cell_height;
    bool _test;
    bool _gamestart;
    bool _gamewin;
    int _gameStatus;
    bool _revealMines;
    bool _checkIfMine;
    bool _gameRunning;
    int _tempMines;
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
public:
    void Initialize();
    void SwitchDebug(sf::RenderWindow& window);
    void addMinesAdjacent(int row, int col);
    void revealAdjacent(int row, int col);  
    void flagCell(int row, int col);
    void Modify(int cols, int rows, int width, int height, std::vector<std::vector<int> > numbers);
    void addMines(int i, int j);
    void drawBoard(sf::RenderWindow& window);
    void setRevealedTexture(int i, int j, sf::Sprite& sprite);
    void GameLoop(int row, int col, sf::RenderWindow& window);
    void reset();
    void checkWin();
    bool gameRunning();
    bool checkIfMine(int i,int j);
    int getCellWidth();
    int getCellHeight();
    sf::Sprite DebugButton;
    sf::Sprite WinButton;
    sf::Sprite DigitsButton0;
    sf::Sprite DigitsButton1;
    sf::Sprite DigitsButton2;
    sf::Sprite Test1Button;
    sf::Sprite Test2Button;
    sf::Sprite Test3Button;
    std::vector<std::vector<Cell*> > cells;
    std::vector<std::pair<int, int> > generateRandomNumbers(std::vector<std::pair<int, int>>& excluded);
    Board(int columns, int rows, int mines, int width, int height);
    ~Board();
};
