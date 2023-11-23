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
    std::vector<std::vector<int> > _numbers;
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
    bool _test;

    bool _gamestart;
    bool _gamewin;
    int _gameStatus;
    bool _revealMines;
    bool _checkIfMine;
    bool _gameRunning;





public:
void Initialize();

bool gameRunning();
   int getCellWidth();
   int getCellHeight();

   void SwitchDebug(sf::RenderWindow& window);
    void revealAdjacent(int row, int col);  

    void debugCells();

    void flagCell(int row, int col);
    sf::Sprite DebugButton;
    sf::Sprite WinButton;
    sf::Sprite DigitsButton0;
    sf::Sprite DigitsButton1;
    sf::Sprite DigitsButton2;
    sf::Sprite Test1Button;
    sf::Sprite Test2Button;
    sf::Sprite Test3Button;




    void Test(int option);
    void Modify(int cols, int rows, int width, int height, std::vector<std::vector<int> > numbers);
    ~Board();

    std::vector<std::vector<Cell*> > cells;
    Board(int columns, int rows, int mines, int width, int height);
    void addMines(int i, int j);
    void drawBoard(sf::RenderWindow& window);

    void setRevealedTexture(int i, int j, sf::Sprite& sprite);
    void GameLoop(int row, int col, sf::RenderWindow& window);
    std::vector<std::pair<int, int> > generateRandomNumbers(std::vector<std::pair<int, int>>& excluded);
    int checkMines();
    void reset();
    void checkWin();

void WinOn();
bool checkIfMine(int i,int j);
void gameRunningFalse();




    







};
