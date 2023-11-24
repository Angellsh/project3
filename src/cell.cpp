#include "cell.hpp"
#include <iostream>


Cell::Cell(int  x, int y){
    _x = x;
    _y= y;
    mine=false;
    revealed=false;
    flagged=false;
    hidden=false;
    minesCount= 0;
}
void Cell::addMines(){
    minesCount++;

}
Cell::~Cell(){}
void Cell::makeMine(){
    mine=true;
}
bool Cell::isFlagged(){
    return flagged;
}
void Cell::flagSwitch(){
    if(flagged==false){
    flagged=true;}
    else{flagged=false;}

}
bool Cell::isMine(){
   return mine;
}
bool Cell::isRevealed(){
    return revealed;
}

void Cell::revealCell(){
    revealed=true;
}

int Cell:: getY(){
    return _y;

    }
int Cell:: getX(){
    return _x;
    }


int Cell::countAdjacent(){
     return minesCount;
}
void Cell::reset(){
    mine=false;
    revealed=false;
    flagged=false;
    hidden=false;
    minesCount= 0;

}