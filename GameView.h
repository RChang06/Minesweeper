#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <windows.h>
#include "Board.h"
#include <functional>
class GameView
{
private:
    HWND hwnd;       // Window handle
    Board board; 
    std::vector<std::vector<Item>> grid; 
    int startYPos;
    int startXPos; 
    int buttonHeight;
    int buttonLength; 
    // Global board object

public:
    GameView(HWND hwnd); // Constructor
    
    void revealAll();
    void leftClick(int row, int col);//single click
    void rightClick(int row, int col);
    void initialBoard(); // Initialize the board
    void setupBoard();   // Set up the UI
    void processRightClick(int xPos, int yPos); //process right click (all potential logic)
    void processDoubleClick(int index);
    void processLeftClick(int index); // Process left click(all potential logic)
    void displayBoard(); // Display the board in the console
    void revealSingle(int row, int col);
    int calcIndex(int xPos, int yPos);
    void doubleClick(int row, int col);
};

#endif