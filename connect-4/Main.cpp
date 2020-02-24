#include "Linker.h"
#include "Board.h"

using namespace Connect4;

int main()
{
    Py_Initialize();
    np::initialize();

    Board* board = Board::Instance();

    bool over = false;
    while (!over)
    {
        board->printBoard(true);
        int column;

        std::cin >> column;

        over = board->playPiece(column);
    }

    system("pause");
}