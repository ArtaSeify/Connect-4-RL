import communicator
import manual_play

if __name__ == "__main__":
    human_play = False
    
    if human_play:
        manual_play.start()
    else:
        communicator.start()