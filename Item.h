#ifndef ITEM_H
#define ITEM_H

class Item {
private:
    bool isMine;
    bool isRevealed;
    bool isFlagged;
    int adjacentMines;
    int flaggedCells;

public:
    Item(); // Constructor

    void setFlag(bool isFlagged);
    void setAdjacentMines(int num);
    void setMine(bool mineStatus);
    void setRevealed(bool revealedStatus);

    bool isMineCell() const;
    bool isRevealedCell() const;
    bool isFlaggedCell() const;
    int getAdjacentMines() const;

    void reset();
    bool isEmpty() const;
};

#endif // ITEM_H