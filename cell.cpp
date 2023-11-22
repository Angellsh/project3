#include "cell.hpp"
#include <iostream>


Cell::Cell(int  x, int y, sf::Texture& texture){
    _x = x;
    _y= y;
    mine=false;
    revealed=false;
    flagged=false;
    hidden=false;
    minesCount= 0;
    mainSprite.setTexture(texture);
    mainSprite.setPosition(x, y);
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
void Cell::setPosition(int x , int y ){
    mainSprite.setPosition(x, y);

}
sf::Sprite Cell::Sprite(){
    return mainSprite;
}
int Cell:: getY(){
        return _y;

    }
int Cell:: getX(){
        return _x;
    }
void Cell::setTexture(sf::Texture& texture){
        mainSprite.setTexture(texture);

}

int Cell::countAdjacent(){
     return minesCount;


   /*minesCount=0;
    for(const auto& i : adjacent ){
        if (i!= nullptr && i->isMine() ){
            minesCount++;
        }
    }return minesCount;*/ 
}