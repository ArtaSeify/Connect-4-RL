import communicator
import manual_play

if __name__ == "__main__":
    human_play = True
    
    if human_play:
        manual_play.start()
    else:
        communicator.start()