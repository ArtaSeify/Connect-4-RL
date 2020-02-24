#pragma once
#include "Constants.h"
#include <iostream>

namespace Connect4
{
class Board
{
    static Board*   instance;
    BoardType       emptyBoard;
    BoardType       playerOneBoard;
    BoardType       playerTwoBoard;
    CharArray       currRows;
    BoolArray       legalMoves;
    bool            playerOneTurn;
    char            state;  // 0: not over, 1: player 1 won, 2: player 2 won, 3: tie

    Board();

    // initializes all indices of board with value
    void initializeBoard(BoardType & board, bool value);

    // prints the content of a specific board
    void printBoardDebug(const BoardType & board) const;
    
    // prints whos turn it is
    void printTurn() const;

    // checks whether the move at column is legal
    bool moveLegal(int column) const;

    // checks whether we the game is over (four in a row)
    bool gameOver() const;

    // checks whether the current player has 4 in a horizontal row
    bool gameOverHorizontal() const;
    
    // checks whether the current player has 4 in a vertical row
    bool gameOverVertical() const;
    
    // checks whether the current player has 4 in a positive slope row
    bool gameOverPosSlope() const;
    
    // checks whether the current player has 4 in a negative slope row
    bool gameOverNegSlope() const;

    // checks whether the game is a tie
    bool gameOverTie() const;

    // prints the results of the game (game must be over)
    void showResult() const;

    // sets the state of the game
    void setState();

public:
    static Board* Instance();

    // prints all the boards and the whos turn it is
    void printBoardsDebug() const;
    
    // prints the current game board
    void printBoard(bool printPlayerTurn) const;

    // play a piece at the specified column. returns true if game is over, else false
    bool playPiece(int column);   

    // resets the game
    void reset();

    char getState() const { return state; }
    bool getTurn() const { return playerOneTurn; }
    const BoardType & getEmptyBoard() const { return emptyBoard; }
    const BoardType & getPlayerOneBoard() const { return playerOneBoard; }
    const BoardType & getPlayerTwoBoard() const { return playerTwoBoard; }
    const BoolArray & getLegalMoves() const { return legalMoves; }
};
}

