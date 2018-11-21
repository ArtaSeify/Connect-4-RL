import connect4 

def step(self, move):
    self.over = playPiece(move)
    #self.state = [getEmptyBoard(), getPlayerOneBoard(), getPlayerTwoBoard()]

    # reward is 1 if game is over after move is made (current player made winning move)
    if self.over:
       self.reward = 1
       self.terminal = True
    else:
       self.reward = 0
       self.terminal = False


        
