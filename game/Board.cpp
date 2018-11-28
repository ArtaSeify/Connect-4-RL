#include "Board.h"

using namespace Connect4;

Board* Board::instance = NULL;

Board::Board()
{
    playerOneTurn = true;
    state = 0;

    initializeBoard(emptyBoard, true);
    initializeBoard(playerOneBoard, false);
    initializeBoard(playerTwoBoard, false);

    for (int i = 0; i < CSIZE; ++i)
    {
        currRows[i] = RSIZE - 1;
        legalMoves[i] = true;
    }
}

void Board::reset()
{
    playerOneTurn = true;
    state = 0;

    initializeBoard(emptyBoard, true);
    initializeBoard(playerOneBoard, false);
    initializeBoard(playerTwoBoard, false);

    for (int i = 0; i < CSIZE; ++i)
    {
        currRows[i] = RSIZE - 1;
        legalMoves[i] = true;
    }
}

Board* Board::Instance()
{
    if (!instance)
    {
        instance = new Board();
    }

    return instance;
}

void Board::initializeBoard(BoardType & board, bool value)
{
    for (int column = 0; column < CSIZE; ++column)
    {
        for (int row = 0; row < RSIZE; ++row)
        {
            board[column][row] = value;
        }
    }
}

void Board::printBoardDebug(const BoardType & board) const
{
    for (int row = 0; row < RSIZE; ++row)
    {
        for (int column = 0; column < CSIZE; ++column)
        {
            std::cout << board[column][row] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Board::printBoardsDebug() const
{
    std::cout << "Empty board" << std::endl;
    printBoardDebug(emptyBoard);

    std::cout << "Player 1 board" << std::endl;
    printBoardDebug(playerOneBoard);

    std::cout << "Player 2 board" << std::endl;
    printBoardDebug(playerTwoBoard);

    printTurn();
}

void Board::printBoard(bool printPlayerTurn) const
{
    std::cout << std::endl;

    if (printPlayerTurn)
    {
        printTurn();
    }

    for (int row = 0; row < RSIZE; ++row)
    {
        for (int column = 0; column < CSIZE; ++column)
        {
            std::cout << "|";
            if (playerOneBoard[column][row])
            {
                std::cout << PLAYER_ONE;
            }
            else if (playerTwoBoard[column][row])
            {
                std::cout << PLAYER_TWO;
            }
            else
            {
                std::cout << " ";
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << std::endl;
}

void Board::printTurn() const
{
    std::cout << "Turn: ";
    playerOneTurn ? std::cout << PLAYER_ONE << std::endl
        : std::cout << PLAYER_TWO << std::endl;
}

bool Board::playPiece(int column)
{
    // check if the move is legal
    if (!moveLegal(column))
    {
        std::cerr << "Illegal move! " << column << std::endl;
        printBoard(true);
        return false;
    }

    // play the move
    int row = currRows[column];
    if (playerOneTurn)
    {
        playerOneBoard  [column][row] = true;
        emptyBoard      [column][row] = false;
    }

    else
    {
        playerTwoBoard  [column][row] = true;
        emptyBoard      [column][row] = false;
    }

    // increase number of pieces at the column, change turns
    currRows[column]--;
    if (currRows[column] == -1)
    {
        legalMoves[column] = false;
    }

    // check whether the game is over
    if (gameOver())
    {
        setState();
        //showResult();
        return true;
    }

    playerOneTurn = !playerOneTurn;

    return false;
}

bool Board::moveLegal(int column) const
{
    // move is outside the bounds of the game
    if (column < 0 || column >= CSIZE)
    {
        return false;
    }

    // the column is full
    if (legalMoves[column] == false)
    {
        return false;
    }

    return true;
}

bool Board::gameOver() const
{
    return (gameOverHorizontal() || gameOverVertical() ||
            gameOverPosSlope()   || gameOverNegSlope() ||
            gameOverTie());
}

bool Board::gameOverHorizontal() const
{
    // go through whole board, check if current player has
    // 4 in a horizontal row
    for (int row = RSIZE - 1; row >= 0; --row)
    {
        for (int column = 0; column < CSIZE - 3; ++column)
        {
            // 4 in a row for red
            if (playerOneTurn)
            {
                if (playerOneBoard[column][row]     &&
                    playerOneBoard[column + 1][row] &&
                    playerOneBoard[column + 2][row] &&
                    playerOneBoard[column + 3][row])
                {
                    return true;
                }
            }

            // 4 in a row for blue
            else
            {
                if (playerTwoBoard[column][row]     &&
                    playerTwoBoard[column + 1][row] &&
                    playerTwoBoard[column + 2][row] &&
                    playerTwoBoard[column + 3][row])
                {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Board::gameOverVertical() const
{
    // go through whole board, check if current player has
    // 4 in a vertical row
    for (int column = 0; column < CSIZE; ++column)
    {
        for (int row = RSIZE - 1; row >= 3; --row)
        {
            // 4 in a row for red
            if (playerOneTurn)
            {
                if (playerOneBoard[column][row]     &&
                    playerOneBoard[column][row - 1] &&
                    playerOneBoard[column][row - 2] &&
                    playerOneBoard[column][row - 3])
                {
                    return true;
                }
            }

            // 4 in a row for blue
            else
            {
                if (playerTwoBoard[column][row]     &&
                    playerTwoBoard[column][row - 1] &&
                    playerTwoBoard[column][row - 2] &&
                    playerTwoBoard[column][row - 3])
                {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Board::gameOverPosSlope() const
{
    // go through whole board, check if current player has
    // 4 in a positive slope row
    for (int row = RSIZE - 1; row >= 3; --row)
    {
        for (int column = 0; column < CSIZE - 3; ++column)
        {
            // 4 in a row for red
            if (playerOneTurn)
            {
                if (playerOneBoard[column]    [row]     &&
                    playerOneBoard[column + 1][row - 1] &&
                    playerOneBoard[column + 2][row - 2] &&
                    playerOneBoard[column + 3][row - 3])
                {
                    return true;
                }
            }

            // 4 in a row for blue
            else
            {
                if (playerTwoBoard[column]    [row]     &&
                    playerTwoBoard[column + 1][row - 1] &&
                    playerTwoBoard[column + 2][row - 2] &&
                    playerTwoBoard[column + 3][row - 3])
                {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Board::gameOverNegSlope() const
{
    // go through whole board, check if current player has
    // 4 in a negative slope row
    for (int row = RSIZE - 4; row >= 0; --row)
    {
        for (int column = 0; column < CSIZE - 3; ++column)
        {
            // 4 in a row for red
            if (playerOneTurn)
            {
                if (playerOneBoard[column][row] &&
                    playerOneBoard[column + 1][row + 1] &&
                    playerOneBoard[column + 2][row + 2] &&
                    playerOneBoard[column + 3][row + 3])
                {
                    return true;
                }
            }

            // 4 in a row for blue
            else
            {
                if (playerTwoBoard[column][row] &&
                    playerTwoBoard[column + 1][row + 1] &&
                    playerTwoBoard[column + 2][row + 2] &&
                    playerTwoBoard[column + 3][row + 3])
                {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Board::gameOverTie() const
{
    for (bool playable : legalMoves)
    {
        if (playable)
        {
            return false;
        }
    }

    return true;
}

void Board::setState()
{
    if (playerOneTurn)
    {
        state = 1;
    }

    else
    {
        state = 2;
    }

    // check if game is tie
    if (gameOverTie())
    {
        state = 3;
    }
}

void Board::showResult() const
{
    std::cout << std::endl;
    std::cout << "Game over. ";

    if (state == 1)
    {
        std::cout << "Player 1 wins!";
    }
    else if (state == 2)
    {
        std::cout << "Player 2 wins!";
    }
    else if (state == 3)
    {
        std::cout << "Tie!";
    }

    printBoard(false);
}