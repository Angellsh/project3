#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "board.cpp"



using namespace std;
int main() {
  
    ifstream file("boards/config.cfg");
    if (!file.is_open()){
        cout<<"not open";}
    int columns, rows, mines;
    file>>columns>>rows>>mines;
    int width = columns*32;
   std:: cout<<"real width"<<width;

    int height = (rows*32)+100;
    sf::RenderWindow window(sf::VideoMode(width,height), "Angel's Minesweeper");
    std:: cout<<"width"<<width;
    Board board(columns, rows, mines, width, height);
    board.addMines();
    board.checkMines();




   // board.boardSet();

  


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }else if(event.type ==sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left){
                    sf::Vector2i mouseCords =sf::Mouse::getPosition(window);
                    if(board.DebugButton.getGlobalBounds().contains(static_cast<float>(mouseCords.x), static_cast<float>(mouseCords.y))){
                            board.SwitchDebug();
                    }
                    for(int i=0;i<rows;i++){
                        for (int j=0; j<columns;j++){
                            sf::FloatRect cellBounds =board.cells[i][j]->Sprite().getGlobalBounds();
                        if (cellBounds.contains(static_cast<float>(mouseCords.x), static_cast<float>(mouseCords.y))){
                            board.GameLoop(i, j);
                        }
                     
                     
                    }
                }}else if(event.mouseButton.button ==sf::Mouse::Right){
                sf::Vector2i mouseCords =sf::Mouse::getPosition(window);
                for(int i=0;i<rows;i++){
                        for (int j=0; j<columns;j++){
                            sf::FloatRect cellBounds = board.cells[i][j]->Sprite().getGlobalBounds();
                            if(cellBounds.contains(mouseCords.x, mouseCords.y)){
                                board.flagCell(i, j);
                            }

            

        
            }
        }
        }
        }else if(board.gameOver()){
           

        }
        }
        board.drawBoard(window);
        window.display();
    }
    
    
    return 0;
}
