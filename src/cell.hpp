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
   Cell(int x , int y );
   std::vector<Cell*> adjacent;
   bool isRevealed();
   bool isFlagged();
   bool isMine();
   void makeMine();
   void flagSwitch();
   void revealCell();
   void addMines();
   void reset();
   int getY();
   int getX();
   int countAdjacent();
   ~Cell();
};