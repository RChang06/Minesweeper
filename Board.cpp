#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Board.h"
#include "GameView.h"

// Constructor for the Board class. Initializes the board with given rows and columns.
// Also initializes the grid, revealed cell count, and total mines.
Board::Board(int rows, int cols) : rows(rows), cols(cols), grid(rows, std::vector<Item>(cols)), revealed(0), totalMines(5) {}

// Alternative constructor (commented out). Initializes the board using manual assignment.
// Board::Board(int rows, int cols) {
//     this->rows = rows;
//     this->cols = cols;
//     this->grid = std::vector<std::vector<Item>>(rows, std::vector<Item>(cols));
// }

// Returns the grid (2D vector of Item objects) for external access.
std::vector<std::vector<Item>> &Board::getGrid() {
    return grid;
}

// Resets the board by resetting all cells in the grid.
void Board::resetBoard() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {  // Fix: j++ instead of i++
            grid[i][j].reset();
        }
    }
}

// Checks if the game is successful by comparing revealed cells to total mines.
bool Board::isSuccess() {
    revealed++;
    std::cout << "\nRevealed flag: " << revealed;
    return (rows * cols - revealed == totalMines);
}

// Randomly places the specified number of mines on the board.
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

// Reveals a cell at the specified row and column. If the cell is empty, recursively reveals adjacent cells.
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

// Counts the number of adjacent mines for a given cell and updates its adjacent mine count.
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

// Counts the number of adjacent mines for all cells on the board.
void Board::countAll() {
    for (int row = 0; row < this->rows; row++) {
        for (int col = 0; col < this->cols; col++) {
            countNumber(row, col);
        }
    }
}

// Counts the number of adjacent flags for a given cell.
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

// Reveals surrounding cells if the number of adjacent flags matches the cell's mine count.
void Board::revealSurrounding(int row, int col, GameView* GameView) {
    if ((countFlag(row, col) == grid[row][col].getAdjacentMines()) && grid[row][col].isRevealedCell()) {
        std::cout << "condition met";

        for (int i = row - 1; i <= row + 1; i++) {
            for (int j = col - 1; j <= col + 1; j++) {
                std::cout << "row: " << i << "col: " << j;
                if (i >= 0 && i < rows && j >= 0 && j < cols && !grid[i][j].isRevealedCell() && !grid[i][j].isFlaggedCell()) {  // Fix: Check bounds
                    std::cout << "\nasd";
                    GameView->leftClick(i, j);
                }
            }
        }
    }
}

// Returns the number of rows in the board.
int Board::getRow() const {
    return rows;
}

// Returns the number of columns in the board.
int Board::getCol() const {
    return cols;
}