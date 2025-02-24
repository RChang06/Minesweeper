#include <iostream>
#include "Board.h"
#include "GameView.h"
class Game {
public:
    void test() {

        Board board(8, 8);
        Board aaa = Board(8,8);

        board.resetBoard();

        board.setMines(10);
        board.countAll();


        view.displayBoard(board);
    }
};

int main() {
    
    Game game;
    game.test();

    return 0;
}
