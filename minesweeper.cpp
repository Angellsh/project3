#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "board.cpp"
using namespace std;


struct TestStruct{
    int columns;
    int rows;
    int height;
    int width;
    vector<vector<int>> cells;
};


void readfile(int option, TestStruct& test );


int main() {
    ifstream file("boards/config.cfg");
    if (!file.is_open()){
        cout<<"Config file is not open..";}
    int columns, rows, mines;
    file>>columns>>rows>>mines;
    int width = columns*32;
    int height = (rows*32)+100;
    sf::RenderWindow window(sf::VideoMode(width,height), "Minesweeper");
    Board board(columns, rows, mines, width, height);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) {
                window.close();

            }if(event.type ==sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Left){
                    sf::Vector2i mouseCords =sf::Mouse::getPosition(window);
                    if(board.DebugButton.getGlobalBounds().contains(static_cast<float>(mouseCords.x), static_cast<float>(mouseCords.y))){
                        board.SwitchDebug(window);
                    }else if(board.WinButton.getGlobalBounds().contains(static_cast<float>(mouseCords.x),  static_cast<float>(mouseCords.y))){
                        board.reset();
                    }else if(board.Test1Button.getGlobalBounds().contains(static_cast<float>(mouseCords.x), static_cast<float>(mouseCords.y))){
                        window.close();
                        TestStruct test;
                        readfile(1, test);
                        window.create(sf::VideoMode(test.width, test.height), "Minesweeper");
                        board.Modify(test.columns, test.rows, test.width, test.height, test.cells);
                    }else if(board.Test2Button.getGlobalBounds().contains(static_cast<float>(mouseCords.x), static_cast<float>(mouseCords.y))){
                        window.close();
                        TestStruct test;
                        readfile(2, test);
                        window.create(sf::VideoMode(test.width, test.height), "Minesweeper");
                        board.Modify(test.columns, test.rows, test.width, test.height, test.cells);
                    }else if(board.Test3Button.getGlobalBounds().contains(static_cast<float>(mouseCords.x), static_cast<float>(mouseCords.y))){
                        window.close();
                        TestStruct test;
                        readfile(3, test);
                        window.create(sf::VideoMode(test.width, test.height), "Minesweeper");
                        board.Modify(test.columns, test.rows, test.width, test.height, test.cells);

                    }for(int i=0;i<rows;i++){
                        for (int j=0; j<columns;j++){
                            sf::FloatRect cellBounds(board.cells[i][j]->getX(), board.cells[i][j]->getY(), board.getCellWidth(), board.getCellHeight());
                            if (cellBounds.contains(static_cast<float>(mouseCords.x), static_cast<float>(mouseCords.y))){
                                if(board.gameRunning()){
                                    board.GameLoop(i, j, window);
                                    board.checkIfMine(i, j);
                                    board.drawBoard(window);
                                }
                            }
                        }
                    }
                }
            }else if(event.mouseButton.button ==sf::Mouse::Right){
                sf::Vector2i mouseCords =sf::Mouse::getPosition(window);
                for(int i=0;i<rows;i++){
                    for (int j=0; j<columns;j++){
                        sf::FloatRect cellBounds(board.cells[i][j]->getX(), board.cells[i][j]->getY(), board.getCellWidth(), board.getCellHeight());
                        if(cellBounds.contains(mouseCords.x, mouseCords.y)){
                            board.flagCell(i, j);
                        }
                    }
                }
            }
        }
        board.drawBoard(window);
        window.display();
    }
    return 0;
}


void readfile(int option, TestStruct& test ){
    ifstream file;
    if(option==1){ file.open("boards/testboard1.brd");
    if (!file.is_open()){std::cout<<"Board 1 is not open..";}}
    else if(option==2){ file.open("boards/testboard2.brd");
    if (!file.is_open()){std::cout<<"Board 2 is not open..";}}
    else if(option==3){ file.open("boards/testboard3.brd");
    if (!file.is_open()){std::cout<<"Board 3 is not open..";}}
    std::vector<std::vector<int>> rowsVector;;
    std::string line;
    int rows=0;
    int cols=0;
    while(std::getline(file,line )){
        std::vector<int> row;
        cols = 0;
        rows++;
        for (char digit: line){
            row.push_back(digit-'0');
            cols++;
        }
        rowsVector.push_back(row);
    }
    file.close();
    test.rows = rows;
    test.columns =cols;
    test.width = cols*32;
    test.height =(rows*32)+100;
    test.cells = rowsVector;

}