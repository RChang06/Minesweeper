#include <iostream>
#include "Item.h"
#include "GameView.h"
#include <functional>
#include <vector>
#include <string>
#include <sstream>
#include <windows.h>

// Constructor to initialize the board
// currentButton to global maybe?
GameView::GameView(HWND hwnd) : hwnd(hwnd), board(11, 11), startXPos(0), startYPos(0), buttonHeight(30), buttonLength(30)  {}

int GameView::calcIndex(int xPos, int yPos){
    
    int index = ((yPos-startYPos)/buttonHeight*board.getCol()+(xPos-startXPos)/buttonLength+1);
    return index; 
}
void GameView::initialBoard()
{
    // Reset and set up the board
    board.resetBoard();
    board.setMines(15);
    board.countAll();

    // Set up the UIP
    setupBoard();

    // Display the board in the console
    displayBoard();
}

void GameView::revealAll(){
    int row = board.getRow();
    int col = board.getCol();
    for (int i = 0; i<row; i++){
        for (int j = 0; j<col; j++){
            revealSingle(i, j);
        }
    }
}

void GameView::revealSingle(int row, int col){
    std::vector<std::vector<Item>> grid = board.getGrid();
    Item currentButton = grid[row][col];
    int buttonID = (row)*board.getCol() + col+1;
    HWND hwndButton = GetDlgItem(hwnd,buttonID);


    if(currentButton.isMineCell()){
        SetWindowTextW(hwndButton, L"x");
    }

    else if(currentButton.getAdjacentMines()>0){
        std::wstringstream captionNum;
        captionNum << currentButton.getAdjacentMines();
        std::wstring wideNumber = captionNum.str();
        

        SetWindowTextW(hwndButton, wideNumber.c_str());

    }
    else if(currentButton.isEmpty()){

        // Destroy the button
        DestroyWindow(hwndButton);

        // Create a static control with a background color
        HWND hwndStatic = CreateWindow(TEXT("STATIC"), TEXT(""),
            WS_VISIBLE | WS_CHILD | SS_GRAYRECT| WS_BORDER, // SS_GRAYRECT will fill the area with a gray color
            startXPos+ col * 30, startYPos+ row * 30, 30, 30, hwnd, NULL, 0, 0);
    }
        
}

void GameView::rightClick(int row, int col){

    std::vector<std::vector<Item>> &grid = board.getGrid(); 
    Item &currentButton = grid[row][col];
    //calculate the id, Ie first grid = 1 and last grid for an 8*8 grid is 64
    

    int buttonID = (board.getCol()*row + col+1);
    std::cout<<"\nthis is real button Id: "<< buttonID; 
    HWND hwndButton = GetDlgItem(hwnd, buttonID);

    //if the cell isn't revealed, you can toggle flag however you like
    if(!currentButton.isRevealedCell()){ 

        if(!currentButton.isFlaggedCell() ){
            std::cout<<"\nflagged";
            SetWindowTextW(hwndButton, L"F");
            currentButton.setFlag(true);
        }
        else if (currentButton.isFlaggedCell()){
            std::cout<<"\nunflag";
            SetWindowTextW(hwndButton, L"");
            currentButton.setFlag(false);
        }
        //update flag counts
        //board.updateFlagCount(row, col);
    }
}

void GameView::setupBoard()
{   //retrieve the dimensions of the board
    int rows = board.getRow();
    int cols = board.getCol();
    // Creating buttons
    for (int row = 0; row<rows; row++){
        for (int col = 0; col<cols ; col++){
            int buttonID = row * cols + col + 1;
                CreateWindow(TEXT("BUTTON"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER, startXPos + col * 30, startYPos + row * 30, buttonHeight, buttonLength, hwnd, (HMENU)buttonID, 0, 0);
        }
    }
}

void GameView::leftClick(int row, int col){
    std::vector<std::vector<Item>> grid = board.getGrid(); 

    Item currentButton = grid[row][col];
    //to reveal a cell, it can't already be revealed or flagged
    if (!currentButton.isRevealedCell() && !currentButton.isFlaggedCell()){
        if (currentButton.isMineCell()){
            
            revealAll();

            MessageBox(NULL, TEXT("Game Over"), TEXT("Game Over!!"), MB_OK);

        }

        revealSingle(row, col);
        if (board.isSuccess()){
            revealAll();
            MessageBox(NULL, TEXT("You won"), TEXT("Success!!"), MB_OK);

        }
        
        board.revealCell(row, col, this);
    }
    
}

// void GameView::rightClick(int row, int col){
// }
//very redundant update later, possible combine all the clicks together by passing a function
void GameView::processRightClick(int xPos, int yPos){
    int index = calcIndex(xPos, yPos);
    int row = (index - 1) / board.getCol(); // Calculate row
    int col = (index - 1) % board.getCol(); // Calculate column

    if (index>=1 && index<=board.getRow()*board.getCol()){
        rightClick(row, col);
    }
    else {
        std::cout << "Invalid button ID: " << index << std::endl;
    }

}
void GameView::processLeftClick(int index){
    std::vector<std::vector<Item>> grid = board.getGrid();
    int row = (index - 1) / board.getCol(); // Calculate row
    int col = (index - 1) % board.getCol(); // Calculate column

    if (index>=1 && index<=board.getRow()*board.getCol()){
        leftClick(row, col); // Call leftClick with the calculated coordinates
    }
    else {
        std::cout << "Invalid button ID: " << index << std::endl;
    }
}
void GameView::doubleClick(int row, int col){
    board.revealSurrounding(row, col, this);
}
void GameView::processDoubleClick(int index){
 
    int row = (index-1) / board.getCol();
    int col = (index-1) %board.getCol();

    if (index>=1 && index<=board.getRow()*board.getCol()){
        doubleClick(row, col); // Call leftClick with the calculated coordinates
    }
    else {
        std::cout << "Invalid button ID: " << index << std::endl;
    }
}

void GameView::displayBoard()
{
    std::vector<std::vector<Item>> grid = board.getGrid();
    int rows = board.getRow();
    int cols = board.getCol();

    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            Item item = grid[row][col];
            int number = item.getAdjacentMines();
            bool flag = item.isFlaggedCell();
            bool bomb = item.isMineCell();

            if (flag)
            {
                std::cout << 'f';
            }
            else if (bomb)
            {
                std::cout << 'B';
            }
            else
            {
                std::cout << number;
            }
        }
        std::cout << std::endl;
    }
}
