from connect4 import *
import numpy as np

class environment:
    def __init__(self):
        self.state = np.array([getEmptyBoard(), getPlayerOneBoard(), getPlayerTwoBoard()])
        self.over = False
        self.CSIZE = CSIZE()
        self.RSIZE = RSIZE()
        self.action_size = action_size()
        self.legal_moves = getLegalMoves()
        player_one_turn = getTurn()
        if player_one_turn:
            self.turn = 0
        else:
            self.turn = 1

        self.response = [0, self.state, False, self.turn]

    def step(self, move):
        self.over = playPiece(move)

        player_one_turn = getTurn()
        if player_one_turn:
            self.turn = 0
        else:
            self.turn = 1

        self.state = np.array([getEmptyBoard(), getPlayerOneBoard(), getPlayerTwoBoard()])

        # game is over
        if self.over:
            self.game_result = getResult()

            # tie game
            if self.game_result == 3:
                self.reward = 0

            # the player that made the move won
            elif self.game_result == 1 or self.game_result == 2:
                self.reward = 1

            self.terminal = True
        else:
            self.reward = 0
            self.terminal = False

        self.legal_moves = getLegalMoves()

        return [self.reward, self.state, self.over, self.turn], self.legal_moves

    def reset(self):
        reset()
        self.over = False
        player_one_turn = getTurn()
        if player_one_turn:
            self.turn = 0
        else:
            self.turn = 1

    def printBoard(self):
        printBoard()


        
