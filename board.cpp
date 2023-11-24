#include "board.hpp"
#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <utility>
#include <memory>
#include <sstream>
#include <iomanip>
#include <chrono>


void Board::Initialize(){
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
        _test=false;
        _tempMines =_mines;
        cells.resize(_rows, std::vector<Cell*>(_columns, nullptr));


}
void Board::Modify(int cols, int rows, int width, int height, std::vector<std::vector<int> > numbers){
    reset();
    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < _columns; ++j) {
            delete cells[i][j];
        }
    }
    cells.clear();
    _mines =0;
    _width = width;
    _columns = cols;
    _rows = rows;
    _height = height;
    _cell_width = _width/_columns;
    _cell_height= (_height-100)/_rows;
    cells.resize(_rows, std::vector<Cell*>(_columns, nullptr));

    //creating new cells* vector
    for (int i =0;i<_rows;i++){
        for(int j=0;j<_columns;j++){
            cells[i][j] = new Cell(j*_cell_width, i*_cell_height );
        }
    } 

    //populating vector with mines according to provided layout
    for (int i =0;i<_rows;i++){
        for(int j=0;j<_columns;j++){ 
            if (numbers[i][j]==1){
                    _mines++;
                    addMinesAdjacent(i, j);
     
            }
        }
    } 
    _gamestart=true;
    _test =true;
}
void Board::addMinesAdjacent(int row, int col){
     if(row>0){cells[row-1][col]->addMines();} 
    if(row<_rows-1){cells[row+1][col]->addMines();} 
    if(col>0){cells[row][col-1]->addMines();} 
    if(col< _columns-1){cells[row][col+1]->addMines();}
    if(col<_columns-1 && row>0){cells[row-1][col+1]->addMines();}
    if(col>0 && row>0){cells[row-1][col-1]->addMines();} 
    if(col<_columns-1 && row<_rows-1){cells[row+1][col+1]->addMines();}
    if(col>0 && row<_rows-1){cells[row+1][col-1]->addMines();} 
    cells[row][col]->makeMine();}  
                  
         
Board::Board(int cols, int rows, int mines, int width, int height)
    : _width(width),_columns(cols),_rows(rows),_height (height), _mines(mines){
        Initialize();
        for (int a =0;a<_rows;a++){
            for(int b=0;b<_columns;b++){
              cells[a][b] = new Cell(b*_cell_width, a*_cell_height );
            }
        }
 }


     

void Board::addMines(int i, int j){
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
    for (int row=0;row<_rows;row++){
        for (int col=0;col<_columns;col++){
                    auto iter = std::find(randoms.begin(), randoms.end(), std::make_pair(row, col));
                    if(iter!=randoms.end()){
                    if(row>0){cells[row-1][col]->addMines();} 
                    if(row<_rows-1){cells[row+1][col]->addMines();}
                    if(col>0){cells[row][col-1]->addMines();}
                    if(col< _columns-1){cells[row][col+1]->addMines();} 
                    if(col<_columns-1 && row>0){cells[row-1][col+1]->addMines();}
                    if(col>0 && row>0){cells[row-1][col-1]->addMines();}
                    if(col<_columns-1 && row<_rows-1){cells[row+1][col+1]->addMines();}
                    if(col>0 && row<_rows-1){cells[row+1][col-1]->addMines();} 
                    cells[row][col]->makeMine();}  
        } 
    }
     _gamestart=true;
    revealAdjacent(i, j);
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
   if (_gameRunning ){
        if( !_gamestart && !_test){
        addMines(row, col);
        }else{
            if (!cells[row][col]->isMine()){
            revealAdjacent(row, col);
            }
            else{
                for (int i =0; i<_rows; i++){
                for (int j=0;j<_columns;j++){
                    if(cells[i][j]->isMine()){ cells[i][j]->revealCell();}
                    }
            }
            _gameStatus=3;
            drawBoard(window);
            _gameRunning=false;
            }
        }checkWin();
            if(_gamewin){
                _gameStatus=2;
                for (int i =0;i<_rows;i++){
                    for(int j=0;j<_columns;j++){
                        cells[i][j]->revealCell();
                    }
                }
                drawBoard(window);
                _gameRunning=false;
            }
    }
}
void Board::revealAdjacent(int row, int col){
       if(row<0 || row >=_rows || col<0 || col >=_columns || cells[row][col]->isRevealed()){
            return;
        }
       if(cells[row][col]->countAdjacent()!=0) {
            cells[row][col]->revealCell();
            return;
       }
       else{cells[row][col]->revealCell();
       if (col < _columns - 1 && row > 0){
            if (cells[row - 1][col + 1]->countAdjacent() == 0) {
            revealAdjacent(row - 1, col + 1);
            }else{cells[row - 1][col + 1]->revealCell();}
        }
        if (col > 0) {
            if ( cells[row][col - 1]->countAdjacent() == 0) {
            revealAdjacent(row, col - 1);
            }else{ cells[row][col - 1]->revealCell();}
        }
        if (col < _columns-1 ){
            if (cells[row][col+1]->countAdjacent() == 0) {
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


void Board::drawBoard(sf::RenderWindow& window){
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

    //drawing debug buttons
    DebugButton.setTexture(debugTexture);
    DebugButton.setPosition(_width - test1.getSize().x*4, _height-100);

    //drawing win/control button
    if(_gameStatus==1){WinButton.setTexture(faceHappyTexture);}
    else if(_gameStatus==2){WinButton.setTexture(faceWinTexture);}
    else if(_gameStatus==3){WinButton.setTexture(faceLostTexture);}
    WinButton.setPosition(_width/2-faceWinTexture.getSize().x/2, _height-100);
    window.draw(DebugButton);
    window.draw(WinButton);
    
    //drawing test buttons
    Test1Button.setTexture(test1);
    Test2Button.setTexture(test2);
    Test3Button.setTexture(test3);
    Test1Button.setPosition(_width - test1.getSize().x*3, _height-100);
    Test2Button.setPosition(_width - test1.getSize().x*2, _height-100);
    Test3Button.setPosition(_width - test1.getSize().x, _height-100);
    window.draw(Test1Button);
    window.draw(Test2Button);
    window.draw(Test3Button);

    //drawing a mine count 
    std::map<int, sf::Sprite> digitsMap;
    for (int i=0; i<10; i++){
        sf::Sprite offsetSprite(digitsTexture);
        sf::IntRect textRect(21*i,0, 21, 32 );
        offsetSprite.setTextureRect(textRect);
        digitsMap[i]=offsetSprite;
    }
    std::stringstream str;
    str<<std::setw(3)<<std::setfill('0')<<_mines;
    std::string mineString = str.str();
    DigitsButton0=digitsMap[mineString[0]-'0'];
    DigitsButton1=digitsMap[mineString[1]-'0'];
    DigitsButton2=digitsMap[mineString[2]-'0'];
    DigitsButton0.setPosition(41, _height-100);;
    DigitsButton1.setPosition(62, _height-100);;
    DigitsButton2.setPosition(83, _height-100);;
    window.draw(DigitsButton0);
    window.draw(DigitsButton1);
    window.draw(DigitsButton2);
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
           _test=false;
           _mines =_tempMines;
    for (int a =0;a<_rows;a++){
       for(int b=0;b<_columns;b++){
           cells[a][b]->reset();
       }
       
    }
    
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

void Board::checkWin(){
    int safeCells = (_columns*_rows)-_mines;
    int totalRevealed=0;
    for (int i =0;i<_rows;i++){
          for(int j=0;j<_columns;j++){
            if(cells[i][j]->isRevealed()){
                totalRevealed++;
            }
        }
    }
   // std::cout<<"total revealed: "<<totalRevealed<<" total safe: "<<safeCells<<std::endl;
    _gamewin=(totalRevealed==safeCells);


}
Board::~Board(){
    for (int i =0;i<_rows;i++){
          for(int j=0;j<_columns;j++){
            delete cells[i][j];
          }
    }
}