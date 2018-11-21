if __name__ == "__main__":
    import connect4 as c4

    over = False;
    while not over:
        c4.printBoard()
        column = int(input())
        over = c4.playPiece(column)