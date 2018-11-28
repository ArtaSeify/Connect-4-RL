import random

class agent:
    def __init__(self):
        return

    def step(self, response, legal_moves):
        action = random.randint(0, 6)
        while not legal_moves[action]:
            action = random.randint(0, 6)       
        
        return action

    def reset(self, response):
        return