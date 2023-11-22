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
          _gameover = false;
  



         
          
          _debug = true;


       cells.resize(_rows, std::vector<Cell*>(_columns, nullptr));
       for (int a =0;a<_rows;a++){
          for(int b=0;b<_columns;b++){
           int cell_width = _width/_columns;
           int cell_height= (_height-100)/_rows;
           cells[a][b] = new Cell(b*cell_width, a*cell_height , tileHiddenTexture);
         //  std::cout<<a<<", "<<b<<std::endl;
        
         /*working cells
            Cell* right = (j>0) ? cells[i][j-1] :nullptr;
            Cell* downleft =(j<_columns-1 && i>0) ? cells[i-1][j+1] : nullptr;
            Cell* downright = (j>0 && i>0) ? cells[i-1][j-1] : nullptr;
            Cell* down = (i>0) ? cells[i-1][j] : nullptr;

           //not working
            Cell* up = (j < _columns - 1) ? cells[i][j + 1] : nullptr;

            Cell* left = (j<_columns-1) ? cells[i][j+1] : nullptr;
            Cell*  upleft = (i<_rows-1 && j<_columns-1) ? cells[i+1][j+1] : nullptr;
            Cell* upright = (j<_rows-1 && i>0) ? cells[i-1][j+1] : nullptr;
            std::cout<<"right: "<<right << ", left: "<< left<< ", up: "<<up<<" down: "<<std::endl;
            std::cout<<down<<", upright: "<<upright<< ", upleft: "<<upleft<<", downright: "<<downright<<", downleft:"<<std::endl;


          cells[i][j]->adjacent.push_back(down); //not working
           cells[i][j]->adjacent.push_back( right); //not working
           cells[i][j]->adjacent.push_back( downright); //not working 
           cells[i][j]->adjacent.push_back( downleft); //not working
           cells[i][j]->adjacent.push_back(up); //working, down:)
          cells[i][j]->adjacent.push_back(upright); //working, downleft:)
          cells[i][j]->adjacent.push_back( left); //working on the right lol
           cells[i][j]->adjacent.push_back( upleft); //working  downright
        */
       
          }}
         

    }


void Board::debugCells(){  
    for (int i=0;i<_rows;i++){
        for (int j=0;j<_columns;j++){
            if (cells[i][j] ==nullptr){
                std::cout<<i<<", "<<j<<"  is nullptr"<<std::endl;

            }
            else {
                std::cout<<i<<", "<<j<<std::endl;

        }
        std::cout<<std::endl;

        }}
    std::cout<<"rows: "<<_rows<<std::endl;
    std::cout<<"columns: "<<_columns<<std::endl;


}
     

void Board::addMines(){
    debugCells();
    float cell_width=_width/_columns;
    float cell_height=(_height-100)/_rows;
    std::vector<std::pair<int, int> > randoms = generateRandomNumbers();
    std::cout<<"size: "<<randoms.size()<<std::endl;
    for (int row=0;row<_rows;row++){
        for (int col=0;col<_columns;col++){
          if(std::find(randoms.begin(), randoms.end(), std::make_pair(col,row))!=randoms.end()){
                 cells[row][col]->makeMine();
               
                    if(row>0){cells[row-1][col]->addMines();} else{std::cout<<"no"<<row<<col<<std::endl;}
                     if(row<_rows-1){cells[row+1][col]->addMines();} else{std::cout<<"no"<<row<<col<<std::endl;}
                     if(col>0){cells[row][col-1]->addMines();} else{std::cout<<"no"<<row<<col<<std::endl;}//left
                     if  (col< _columns-1){cells[row][col+1]->addMines();} else{std::cout<<"no"<<row<<col<<std::endl;}//right
                     if(col<_columns-1 && row>0){cells[row-1][col+1]->addMines();}  else{std::cout<<"no"<<row<<col<<std::endl;}//leftdown
                     if(col>0 && row>0){cells[row-1][col-1]->addMines();} else{std::cout<<"no"<<row<<col<<std::endl;}//upper left
                     if(col<_columns-1 && row<_rows-1){cells[row+1][col+1]->addMines();} else{std::cout<<"no"<<row<<col<<std::endl;}//rightdown
                     if(col>0 && row<_rows-1){cells[row+1][col-1]->addMines();} else{std::cout<<"no"<<row<<col<<std::endl;} //upper right doesnt work
                     if(_debug==true){
                   // sf::RectangleShape bg(sf::Vector2f(cell_width, cell_height));
                 //   bg.setFillColor(sf::Color::White);
                 //   bg.setPosition((cells[row][col]->getX()), (cells[row][col]->getY()));
                    cells[row][col]->setTexture(mineTexture);}
                    else{
                     cells[row][col]->setTexture(tileHiddenTexture);  }

                 

            
         }


          
} }
std::cout<<"mines:"<<checkMines()<<std::endl;
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

void Board::setTexture(int i, int j){
        switch(cells[i][j]->countAdjacent()){
        case 1:cells[i][j]->setTexture(num1Texture); break;
        case 2:cells[i][j]->setTexture(num2Texture); break;
        case 3:cells[i][j]->setTexture(num3Texture); break;
        case 4:cells[i][j]->setTexture(num4Texture); break;
        case 5:cells[i][j]->setTexture(num5Texture); break;
        case 6:cells[i][j]->setTexture(num6Texture); break;
        case 7:cells[i][j]->setTexture(num7Texture); break;
        case 8:cells[i][j]->setTexture(num8Texture); break;
        
        
        }
}
void Board::GameLoop(int row, int col){
     if (!cells[row][col]->isMine()){
        revealAdjacent(row, col);
    }
    else{

    }
}
void Board::revealAdjacent(int row, int col){
       if(cells[row][col]->countAdjacent()!=0) {
        setTexture(row, col);
        cells[row][col]->revealCell();
        return;
       }else{
        cells[row][col]->setTexture(tileRevealedTexture);    
        cells[row][col]->revealCell();
        if (col < _columns - 1 && row > 0){
            if (cells[row - 1][col + 1]->countAdjacent() == 0) {
            revealAdjacent(row - 1, col + 1);}
        }else {setTexture(row, col);} //works!!!
        if (col > 0) {if ( cells[row][col - 1]->countAdjacent() == 0) {
            revealAdjacent(row, col - 1);}
        }else{setTexture(row, col); } //works!!!
        if (col < _columns-1 ) {if ( cells[row][col+1]->countAdjacent() == 0) {
            revealAdjacent(row, col + 1); }
       }else{setTexture(row, col);} //works!!!                     

        if (col < _columns - 1 && row < _rows - 1 ) {if ( cells[row + 1][col + 1]->countAdjacent() == 0) {
            revealAdjacent(row + 1, col + 1);}
        }else{setTexture(row, col);
        if (col > 0 && row > 0 ) {if ( cells[row - 1][col - 1]->countAdjacent() == 0) {
            revealAdjacent(row - 1, col - 1);}
        }else{setTexture(row, col);} 
       if (row < _rows - 1 ) {if ( cells[row + 1][col]->countAdjacent() == 0) {
            revealAdjacent(row + 1, col);}
        }else{setTexture(row, col);}
       if (col > 0 && row < _rows - 1 ) {if ( cells[row + 1][col - 1]->countAdjacent() == 0) {
            revealAdjacent(row + 1, col - 1);}
        }else{setTexture(row, col);}
         if (row > 0 ) {if ( cells[row - 1][col]->countAdjacent() == 0) {
            revealAdjacent(row - 1, col);}
         }}
        
        }}

        
               
                //setTexture( row,  col);
        


                
           // }
      //  }}



void Board::drawBoard(sf::RenderWindow& window){
    for (int i =0; i<_rows; i++){
        for (int j=0;j<_columns;j++){
            auto sprite =  cells[i][j]->Sprite();
            window.draw(sprite);


        }
    }
          DebugButton.setTexture(debugTexture);
          DebugButton.setPosition(_width/2+100, _height-100);
          WinButton.setTexture(faceHappyTexture);
          WinButton.setPosition(_width/2, _height-100);
          MinesCountButton.setTexture(digitsTexture);
          MinesCountButton.setPosition(_width/2-250, _height-100);

    window.draw(DebugButton);
    window.draw(WinButton);
    window.draw(MinesCountButton);




}




std::vector<std::pair<int, int> > Board::generateRandomNumbers(){
    std::vector<std::pair<int, int> > numbers;
    std::random_device rd;
    std:: mt19937 gen(rd());
    std::uniform_int_distribution<int> x(0, _columns-1);
    std::uniform_int_distribution<int> y(0, _rows-1);
    int size=0;
    while(size<_mines){
        int random_x=x(gen);
        int random_y = y(gen); 
        auto iter = std::find(numbers.begin(), numbers.end(), std::make_pair(random_x, random_y));
        if(iter==numbers.end()){
            numbers.push_back(std::make_pair(random_x, random_y));
            size++;

            }
        

    }

    return numbers;
}

void Board::SwitchDebug(){

    if (_debug==false)
   { _debug =true;
       std::cout<<"debugging on"<<std::endl;
}
   else{
    _debug=false;
        std::cout<<"debugging off"<<std::endl;

   }for (int row=0;row<_rows;row++){
        for (int col=0;col<_columns;col++){
                if (cells[row][col]->isMine()){
                    if(_debug==true){
                    cells[row][col]->setTexture(mineTexture);}
                    else{
                     cells[row][col]->setTexture(tileHiddenTexture);  }
                }
            }
        }
}
void Board::flagCell(int row, int col){
    cells[row][col]->flagSwitch();
    if(cells[row][col]->isFlagged()){
        std::cout<<"flagged"<<std::endl;
       if(!flagTexture.loadFromFile("images/flag.png")){std::cout<<"error loading file"<<std::endl;};

       cells[row][col]->setTexture(flagTexture);}
    else{

       cells[row][col]->setTexture(tileHiddenTexture);
               std::cout<<"unflagged"<<std::endl;

       

    }



}
bool Board::gameOver(){
    return _gameover;
}