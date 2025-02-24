#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include "item.h"
class GameView; 

class Board {
private:
    int rows;      
    std::vector<std::vector<Item>>grid;
    int cols;  
    // int totalFlags;
    // int totalCorrectFlags;
    int revealed;
    int totalMines;
    GameView* gameView;
    
public:
    Board(int rows, int cols);
    void revealSurrounding(int row, int col, GameView* GameView);      
    void resetBoard();              
    void setMines(int numMines);    
    void revealCell(int row, int col, GameView* GameView);
    void countAll();
    bool isGameOver() const;        
    void countNumber(int row, int col);
    int countFlag(int row, int col);
    bool isSuccess() ;
   // void updateFlagCount(int row, int col);
    int getRow() const;
    int getCol() const; 

    std::vector<std::vector<Item>>& getGrid() ; 
};
#endif
