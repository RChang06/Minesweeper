#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Board.h"
#include "GameView.h"

Board:: Board(int rows, int cols) : rows(rows), cols(cols), grid(rows, std::vector<Item> (cols)), revealed(0), totalMines(5)  {}
// Board:: Board(int rows, int cols) {
//     this->rows = rows;
//     this->cols = cols;
//     this->grid = std::vector<std::vector<Item>>(rows, std::vector<Item>(cols));

// }

std::vector<std::vector<Item>> &Board::getGrid()  {
    return grid;
}
void Board::resetBoard() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {  // Fix: j++ instead of i++
            grid[i][j].reset();
        }
    }
}
// void Board::updateFlagCount(int row, int col){
//     //check if its on a mine grid for correctFlag validility
    
//     //just got flagged
//     if (grid[row][col].isFlaggedCell()){
//         totalFlags++;
//         if (grid[row][col].isMineCell()){
//             totalCorrectFlags++; 
//         }
//     }
//     //just got unflagged
//     else{
//         if (grid[row][col].isMineCell()){
//             totalCorrectFlags--; 
//         }
//         totalFlags--; 
//     }

//     std::cout<<"total Correct Flag: "<<totalCorrectFlags;
//     std::cout<<"\ntotalFlags: "<<totalFlags;
    
// }
bool Board::isSuccess() {
    revealed++;
    std::cout<<"\nRevealed flag: "<<revealed;
    return (rows*cols-revealed == totalMines);
}

void Board::setMines(int numOfMines) {
    totalMines = numOfMines;
    int placedMines = 0;
    int row, col;

    while (placedMines < numOfMines) {
        row = rand() % rows;
        col = rand() % cols;
        if (!grid[row][col].isMineCell()) {
            grid[row][col].setMine(true);
            placedMines++;
        }
    }
}

void Board::revealCell(int row, int col, GameView* GameView) {
    if (row < 0 || row >= rows || col < 0 || col >= cols || grid[row][col].isRevealedCell()) {
        return;
    }
    grid[row][col].setRevealed(true);
    

    if (grid[row][col].isEmpty()) {
        for (int i = row - 1; i <= row + 1; i++) {
            for (int j = col - 1; j <= col + 1; j++) {
                if (i >= 0 && i < rows && j >= 0 && j < cols) {  // Fix: Check bounds
                    GameView->leftClick(i, j);
                }
            }
        }
    }
    
}

void Board::countNumber(int row, int col) {
    int countAdjacent = 0;
    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {
            if (i >= 0 && i < rows && j >= 0 && j < cols) {  // Fix: Check bounds
                if (grid[i][j].isMineCell()) {  // Fix: Check grid[i][j], not grid[row][col]
                    countAdjacent++;
                }
            }
        }
    }
    grid[row][col].setAdjacentMines(countAdjacent);
}

void Board::countAll(){
    
    for (int row = 0; row<this->rows;row++){
        for (int col = 0; col<this->cols; col++){
            countNumber(row,col);
        }
    }
}

int Board::countFlag(int row, int col) {
    int flagAdjacent = 0;
    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {
            if (i >= 0 && i < rows && j >= 0 && j < cols) {  // Fix: Check bounds
                if (grid[i][j].isFlaggedCell()) {  // Fix: Check grid[i][j], not grid[row][col]
                    flagAdjacent++;
                }
            }
        }
    }
    return flagAdjacent;
}

void Board::revealSurrounding(int row, int col, GameView *GameView){
    //reveal surrounding if the flag matches up with the grid number, and the grid needs to be revealed first
    if ((countFlag(row, col) == grid[row][col].getAdjacentMines()) && grid[row][col].isRevealedCell()){
        std::cout<<"condition met";

        for (int i = row - 1; i <= row + 1; i++) {
            for (int j = col - 1; j <= col + 1; j++) {
                std::cout<<"row: "<<i<<"col: "<< j; 
                if (i >= 0 && i < rows && j >= 0 && j < cols && !grid[i][j].isRevealedCell()&&!grid[i][j].isFlaggedCell()) {  // Fix: Check bounds
                    std::cout<<"\nasd";
                    //processLeftClick needs index val;
                    GameView->leftClick(i, j);
                }
            }
        }
    }
}

int Board::getRow() const {
    return rows; 
}
int Board::getCol() const{
    return cols;
}

