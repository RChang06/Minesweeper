#include "Item.h"

// Constructor
Item::Item() {
    isMine = false;
    isRevealed = false;
    isFlagged = false;
    
    adjacentMines = 0;
}

void Item::setFlag(bool isFlagged) {
    this->isFlagged = isFlagged;
}

void Item::setAdjacentMines(int num) {
    adjacentMines = num;
}

void Item::setMine(bool mineStatus) {
    isMine = mineStatus;
}

void Item::setRevealed(bool revealedStatus) {
    isRevealed = revealedStatus;
}

bool Item::isMineCell() const {
    return isMine;
}

bool Item::isRevealedCell() const {
    return isRevealed;
}

bool Item::isFlaggedCell() const {
    return isFlagged;
}

int Item::getAdjacentMines() const {
    return adjacentMines;
}

void Item::reset() {
    isMine = false;
    isRevealed = false;
    isFlagged = false;
    adjacentMines = 0;
}
//it's empty if there is no mine or number
bool Item::isEmpty() const {
    return (getAdjacentMines() == 0 && !isMine); 
}