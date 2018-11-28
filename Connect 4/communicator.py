import environment
import network
import random_agent

num_runs = 1
num_episodes = 1000000
num_moves = 60

save_model_episode = min(5000, num_episodes/10)
episode_print = 1000
load_model = False

second_agent = "random"

def start():
    for run in range(num_runs):
        print("run: " + str(run))
        env = environment.environment()
        agent_one = network.agent(env.CSIZE, env.RSIZE, env.action_size, 1, load_model, False, None)
        
        if second_agent == "random":
            agent_two = random_agent.agent()
        elif second_agent == "nn":
            agent_two = network.agent(env.CSIZE, env.RSIZE, env.action_size, 2, False, False, agent_one.get_model())

        results = []
        
        for episode in range(num_episodes):
            if episode%episode_print == 0:
                print("episode: " + str(episode))

            if episode%save_model_episode == 0 and episode != 0:
                agent_one.save_model(run, episode, 1)

            if env.turn == 0:
                action = agent_one.step(env.response, env.legal_moves)
            else:
                action = agent_two.step(env.response, env.legal_moves)
            response, legal_moves = env.step(action)

            #while env.over is False:
            for num_move in range(num_moves):
                if response[3] == 0:
                    action = agent_one.step(response, legal_moves)
                else:
                    action = agent_two.step(response, legal_moves)
                response, legal_moves = env.step(action)

                # game is over
                if response[2] is True:
                    break

            #if agent_one.eps <= agent_one.eps_min:
            #    env.printBoard()

            result = env.game_result
            results.append(result)
            
            if result == 1:
                agent_one.reset(response)
                response[0] = -response[0]
                agent_two.reset(response)
            elif result == 2:
                agent_two.reset(response)
                response[0] = -response[0]
                agent_one.reset(response)

            env.reset()
