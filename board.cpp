#include "board.hpp"
#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <utility>
#include <memory>


Board::Board(int cols, int rows, int mines, int width, int height)
    : _width(width),_columns(cols),_rows(rows),_height (height), _mines(mines){
          flagTexture.loadFromFile("images/flag.png");
          mineTexture.loadFromFile("images/mine.png");
          tileHiddenTexture.loadFromFile("images/tile_hidden.png");
          tileRevealedTexture.loadFromFile("images/tile_revealed.png");
          num1Texture.loadFromFile("images/number_1.png");
          num2Texture.loadFromFile("images/number_2.png");
          num3Texture.loadFromFile("images/number_3.png");
          num4Texture.loadFromFile("images/number_4.png");
          num5Texture.loadFromFile("images/number_5.png");
          num6Texture.loadFromFile("images/number_6.png");
          num7Texture.loadFromFile("images/number_7.png");
          num8Texture.loadFromFile("images/number_8.png");
          faceLostTexture.loadFromFile("images/face_lose.png");
          faceWinTexture.loadFromFile("images/face_win.png");
          faceHappyTexture.loadFromFile("images/face_happy.png");
          digitsTexture.loadFromFile("images/digits.png");
          debugTexture.loadFromFile("images/debug.png");
          test1.loadFromFile("images/test_1.png");
          test2.loadFromFile("images/test_2.png");
          test3.loadFromFile("images/test_3.png");
           _cell_width = _width/_columns;
           _cell_height= (_height-100)/_rows;
           _gamestart = false;
           _gamewin = false;
           _debug = false;
           _gameStatus=1;
           _revealMines=false;
           _gameRunning=true;


       cells.resize(_rows, std::vector<Cell*>(_columns, nullptr));
          for (int a =0;a<_rows;a++){
          for(int b=0;b<_columns;b++){
           cells[a][b] = new Cell(b*_cell_width, a*_cell_height );
          }}
         

    }


void Board::debugCells(){  
    for (int i=0;i<_rows;i++){
        for (int j=0;j<_columns;j++){
            if (cells[i][j] ==nullptr){

            }
            else {
                std::cout<<i<<", "<<j<<std::endl;

        }
        std::cout<<std::endl;

        }}
    std::cout<<"rows: "<<_rows<<std::endl;
    std::cout<<"columns: "<<_columns<<std::endl;


}
     

void Board::addMines(int i, int j){
     //debugCells();
     std::cout<<"adding mines"<<std::endl;
    float cell_width=_width/_columns;
    float cell_height=(_height-100)/_rows;
    std::vector<std::pair<int,int>> excluded;
    if (i > 0 && i < _rows && j > 0 && j < _rows)
    if(i>0) excluded.push_back(std::make_pair(i-1, j));
    if(j>0) excluded.push_back(std::make_pair(i, j-1));
    if(j<_columns-1 && j<_rows-1) excluded.push_back(std::make_pair(i+1, j+1));
    if(i>0 && j>0) excluded.push_back(std::make_pair(i-1, j-1));
    if(j< _columns-1) excluded.push_back(std::make_pair(i, j+1));
    if(i<_rows-1) excluded.push_back(std::make_pair(i+1,j ));
    excluded.push_back(std::make_pair(i, j));
    if(j<_columns-1 && i>0)excluded.push_back(std::make_pair(i-1, j+1));
    if(i>0 && j<_rows-1) excluded.push_back(std::make_pair(i+1, j-1)); 
     std::vector<std::pair<int, int> > randoms = generateRandomNumbers(excluded);
     for(int a; a<randoms.size(); a++){
       std::cout<< randoms[a].first<<", ";
    std::cout<<randoms[a].second<<std::endl;
     }
    for (int row=0;row<_rows;row++){
        for (int col=0;col<_columns;col++){
         // if(std::find(randoms.begin(), randoms.end(), std::make_pair(col,row))!=randoms.end()){
                   // if(cells[row][col]!=cells[i][j]){
                    auto iter = std::find(randoms.begin(), randoms.end(), std::make_pair(row, col));
                    if(iter!=randoms.end()){
                    if(row>0){cells[row-1][col]->addMines();} //else{std::cout<<"no"<<row<<col<<std::endl;}
                     if(row<_rows-1){cells[row+1][col]->addMines();} //else{std::cout<<"no"<<row<<col<<std::endl;}
                     if(col>0){cells[row][col-1]->addMines();} //else{std::cout<<"no"<<row<<col<<std::endl;}//left
                     if(col< _columns-1){cells[row][col+1]->addMines();} //else{std::cout<<"no"<<row<<col<<std::endl;}//right
                     if(col<_columns-1 && row>0){cells[row-1][col+1]->addMines();} // else{std::cout<<"no"<<row<<col<<std::endl;}//leftdown
                     if(col>0 && row>0){cells[row-1][col-1]->addMines();} //else{std::cout<<"no"<<row<<col<<std::endl;}//upper left
                     if(col<_columns-1 && row<_rows-1){cells[row+1][col+1]->addMines();}// else{std::cout<<"no"<<row<<col<<std::endl;}//rightdown
                     if(col>0 && row<_rows-1){cells[row+1][col-1]->addMines();} //else{std::cout<<"no"<<row<<col<<std::endl;}
                     
                    cells[row][col]->makeMine();}  
                  
                     } }
                     _gamestart=true;
            revealAdjacent(i, j);
                
        
                   }
            
int Board::checkMines(){
    int mines=0;
    for (int i=0;i<_rows;i++){
        for (int j=0;j<_columns;j++){
           if  ( cells[i][j]->isMine())
            mines++;

        }}
        return mines;

}

void Board::setRevealedTexture(int i, int j, sf::Sprite& sprite){
        switch(cells[i][j]->countAdjacent()){
        case 0:sprite.setTexture(tileRevealedTexture); break;
        case 1:sprite.setTexture(num1Texture); break;
        case 2:sprite.setTexture(num2Texture); break;
        case 3:sprite.setTexture(num3Texture); break;
        case 4:sprite.setTexture(num4Texture); break;
        case 5:sprite.setTexture(num5Texture); break;
        case 6:sprite.setTexture(num6Texture); break;
        case 7:sprite.setTexture(num7Texture); break;
        case 8:sprite.setTexture(num8Texture); break;
        
        
        }
}
void Board::GameLoop(int row, int col, sf::RenderWindow& window){

   if (_gameRunning){
     if( !_gamestart){
       addMines(row, col);
       }
       else{
           if (!cells[row][col]->isMine()){
           revealAdjacent(row, col);
           }
           else{
            for (int i =0; i<_rows; i++){
               for (int j=0;j<_columns;j++){
                   if(cells[i][j]->isMine()){ cells[i][j]->revealCell();}
                }
           }_gameStatus=3;
           drawBoard(window);
           _gameRunning=false;
        }
    }
}
}
void Board::revealAdjacent(int row, int col){
       if (row < 0 || row >= _rows || col < 0 || col >= _columns || cells[row][col]->isRevealed()) {
        return;}
       if(cells[row][col]->countAdjacent()!=0) {
        cells[row][col]->revealCell();
        return;
       }
       else{
        cells[row][col]->revealCell();
       if (col < _columns - 1 && row > 0){
            if (cells[row - 1][col + 1]->countAdjacent() == 0) {
            revealAdjacent(row - 1, col + 1);}
            else{
                cells[row - 1][col + 1]->revealCell();}
        }//works!!!
        if (col > 0) {
            if ( cells[row][col - 1]->countAdjacent() == 0) {
            revealAdjacent(row, col - 1);}
        else{ cells[row][col - 1]->revealCell();}
        }
         //works!!!
        if (col < _columns-1 ){
            if ( cells[row][col+1]->countAdjacent() == 0) {
            revealAdjacent(row, col + 1); }
         else{cells[row][col+1]->revealCell(); }
         }          
        if (col < _columns - 1 && row < _rows - 1 ){
            if ( cells[row + 1][col + 1]->countAdjacent() == 0) {
            revealAdjacent(row + 1, col + 1);
            }else{cells[row + 1][col + 1]->revealCell();}           
        }
        if (col > 0 && row > 0 ) {
            if ( cells[row - 1][col - 1]->countAdjacent() == 0) {
            revealAdjacent(row - 1, col - 1);
            }else{cells[row - 1][col - 1]->revealCell();}  
        }
       if (row < _rows - 1 ) {
        if ( cells[row + 1][col]->countAdjacent() == 0) {
            revealAdjacent(row + 1, col);
            }else{cells[row + 1][col]->revealCell();} 

            }
       if (col > 0 && row < _rows - 1 ) {
          if ( cells[row + 1][col - 1]->countAdjacent() == 0) {
            revealAdjacent(row + 1, col - 1);   
            }else{cells[row + 1][col - 1]->revealCell();} 

            }
         if (row > 0 ) {
            if ( cells[row - 1][col]->countAdjacent() == 0) {
            revealAdjacent(row - 1, col);
            }else{cells[row - 1][col]->revealCell();} 
        }
     }

    }
               
                //setTexture( row,  col);
        


                
           // }
      //  }}



void Board::drawBoard(sf::RenderWindow& window){
   // std::cout<<"drawing.."<<std::endl;
    for (int i =0; i<_rows; i++){
        for (int j=0;j<_columns;j++){
            sf::Sprite sprite;
            Cell* cell = cells[i][j];
           sprite.setPosition(cells[i][j]->getX(), cells[i][j]->getY());
            if(_debug==false){
                if(!cell->isRevealed()){
                    if(!cell->isMine()){
                        sprite.setTexture(tileHiddenTexture);
                    }
                    else{
                        if(!_revealMines){
                           sprite.setTexture(tileHiddenTexture);
                           }
                        else{
                            sprite.setTexture(mineTexture);
                            }

                    }
                }
            
                else{
                    if(cell->isMine()){
                    sprite.setTexture(mineTexture);
                    }
                    else{
                        setRevealedTexture(i, j, sprite);
                    }
                }
            }
            else{
                if(!cell->isRevealed()){
                    if(cell->isMine()){
                       sprite.setTexture(mineTexture);
                    }
                }
                else{
                    if(cell->isMine()){
                        sprite.setTexture(mineTexture);

                    }else{
                        setRevealedTexture(i, j, sprite);

                    }

                }
            }
            if(!cell->isRevealed() && cell->isFlagged()){
                sprite.setTexture(flagTexture);
            }
            window.draw(sprite);

        }
    }
          DebugButton.setTexture(debugTexture);
          DebugButton.setPosition(_width/2+100, _height-100);
         if(_gameStatus==1){WinButton.setTexture(faceHappyTexture);}
         else if(_gameStatus==2){WinButton.setTexture(faceWinTexture);}
         else if(_gameStatus==3){WinButton.setTexture(faceLostTexture);}

          WinButton.setPosition(_width/2, _height-100);
          MinesCountButton.setTexture(digitsTexture);
          MinesCountButton.setPosition(_width/2-250, _height-100);

    window.draw(DebugButton);
    window.draw(WinButton);
    window.draw(MinesCountButton);
}


std::vector<std::pair<int, int> > Board::generateRandomNumbers(std::vector<std::pair<int, int>>& excluded){
    std::vector<std::pair<int, int> > numbers;
    std::random_device rd;
    std:: mt19937 gen(rd());
    std::uniform_int_distribution<int> x(0, _rows-1);
    std::uniform_int_distribution<int> y(0, _columns-1);
    int size=0;
    while(size<_mines){
        int random_x=x(gen);
        int random_y = y(gen); 
        auto iter = std::find(numbers.begin(), numbers.end(), std::make_pair(random_x, random_y));
        auto iter2 = std::find(excluded.begin(), excluded.end(), std::make_pair(random_x, random_y));
        if(iter==numbers.end() && iter2==excluded.end() ){
            numbers.push_back(std::make_pair(random_x, random_y));
            size++;
            }
        

    }

    return numbers;
}

void Board::SwitchDebug(sf::RenderWindow& window){
    if (_debug==false)
   { _debug =true;
    std::cout<<"debugging on"<<std::endl;
}else{
    _debug=false;
     std::cout<<"debugging off"<<std::endl;
   }
   
}
void Board::flagCell(int row, int col){
    cells[row][col]->flagSwitch();
    }





int Board::getCellWidth(){
    return _cell_width;
}
int Board::getCellHeight(){
    return _cell_height;
}
void Board::reset(){
    std::cout<<"resetting"<<std::endl;
           _gamestart = false;
           _gamewin = false;
           _debug = false;
           _gameRunning=true;
           _gameStatus=1;
    for (int a =0;a<_rows;a++){
       for(int b=0;b<_columns;b++){
           cells[a][b]->reset();
       }
       
    }
    
}
bool Board::checkWin(){
   int safecells=( _columns*_rows)-_mines;;
     for (int row=0;row<_rows;row++){
        for (int col=0;col<_columns;col++){
            if (cells[row][col]->isRevealed()){
                safecells--;
            }


        }
     }
   //  std::cout<<"safe cells:"<<safecells<<std::endl;
     return safecells;
}
void Board::WinOn(){
    WinButton.setTexture(faceWinTexture);
    _gameRunning=false;

}

bool Board::checkIfMine(int i, int j){
    if(cells[i][j]->isMine()){
        sf::Sprite sprite;
        std::cout<<"found mine"<<std::endl;
        sprite.setPosition(i, j);
        sprite.setTexture(mineTexture);

        return true;
    }return false;

    

}


bool Board::gameRunning(){
    return _gameRunning;
}
