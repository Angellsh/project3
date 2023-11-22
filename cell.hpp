#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Cell{


    int minesCount;
    int _x;
    int _y;
    bool revealed;
    bool mine;
    bool flagged;
    bool hidden;
    sf::Sprite mainSprite;
    


public:
  void addMines();

  // std::vector<Cell*> adjacent;
   bool isRevealed();
   bool isFlagged();
   bool isMine();
    ~Cell();
    Cell(int x , int y, sf::Texture& texture );
    std::vector<Cell*> adjacent;
    void setTexture(sf::Texture& texture);
    void setPosition(int x , int y );
    void makeMine( );
    void flagSwitch( );
    sf::Sprite Sprite();
    int getY();
    int getX();
    void revealCell();
    int countAdjacent();


    





};