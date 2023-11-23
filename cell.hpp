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
    


public:
  void addMines();
   void reset();

  // std::vector<Cell*> adjacent;
   bool isRevealed();
   bool isFlagged();
   bool isMine();
    ~Cell();
    Cell(int x , int y );
    std::vector<Cell*> adjacent;
    void makeMine( );
    void flagSwitch( );
    int getY();
    int getX();
    void revealCell();
    int countAdjacent();


    





};