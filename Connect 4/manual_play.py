import environment
import network
import random_agent

def start():
    env = environment.environment()
    #agent = network.agent(env.CSIZE, env.RSIZE, env.action_size, 1, True, True, None)
    agent = network.agent(env.CSIZE, env.RSIZE, env.action_size, 1, True, True, None, False)

    while True:
        env.printBoard()
        if env.turn == 1:
            action = int(input("move:"))
        else:
            action = agent.step(env.response, env.legal_moves)
        response, legal_moves = env.step(action)
    
        #while env.over is False:
        while True:
            env.printBoard()
            if response[3] == 1:
                action = int(input("move:"))
            else:
                action = agent.step(response, legal_moves)
            response, legal_moves = env.step(action)

            # game is over
            if response[2] is True:
                break

        agent.reset(response)
        env.reset()
