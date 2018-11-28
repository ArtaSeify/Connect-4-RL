from keras import Sequential, Model
from keras.layers import Conv2D, Dense, Flatten, Input, concatenate
from keras.optimizers import Adam
from keras.models import load_model
from keras.callbacks import TensorBoard
import random
import operator
import numpy as np
from collections import deque

import tensorflow as tf
from keras import backend as K

class agent:
    def __init__(self, CSIZE, RSIZE, action_size, agent_num, load_model, human_play, copy_model, CPU_and_GPU=True):
        num_cores = 6

        if CPU_and_GPU:
            num_GPU = 1
            num_CPU = 1
        else:
            num_CPU = 1
            num_GPU = 0

        config = tf.ConfigProto(intra_op_parallelism_threads=num_cores,\
                inter_op_parallelism_threads=num_cores, allow_soft_placement=True,\
                device_count = {'CPU' : num_CPU, 'GPU' : num_GPU})
        session = tf.Session(config=config)
        K.set_session(session)


        self.CSIZE = CSIZE
        self.RSIZE = RSIZE
        self.action_size = action_size

        self.learn_times = 0
        self.prev_action = -1
        self.prev_state = None
        self.steps = 0
        self.mask_value = -5
        self.human_play = human_play
        self.tensor_log_steps = 1000
        self.agent_num = agent_num

        self.games_played = 0
        self.wins = 0
        self.all_games_played = []

        self.lr = 1e-3
        self.gamma = 0.995
        self.eps = 0.99
        self.eps_min = 0.01
        self.eps_decay = 0.0001
        self.batch_size = 32
        self.learn_after_steps = 25000
        self.train_every_steps = 5
        self.memory = deque(maxlen=100000)

        self.tensorBoard = CustomTensorBoard(self, log_dir='./logs' + str(agent_num), write_graph=False, batch_size=self.batch_size)

        if load_model:
            self.load_model(agent_num)
            if human_play:
                self.eps = 0
            return

        if copy_model is None:
            self.build_model()

        else:
            self.model = copy_model
            if human_play:
                self.eps = 0

    def build_model(self):
        boards = Input(shape=(3, self.CSIZE, self.RSIZE))
        turn = Input(shape=(1,))

        first_conv = Conv2D(filters=16, kernel_size=(6,6), \
                                    strides=(3,3), activation='relu', \
                                    data_format="channels_first", padding="same")(boards)
        second_conv = Conv2D(filters=32, kernel_size=(4,4), \
                                    strides=(2,2), activation='relu', \
                                    data_format="channels_first", padding="same")(first_conv)
        third_conv = Conv2D(filters=64, kernel_size=(2,2), \
                                    strides=(1,1), activation='relu', \
                                    data_format="channels_first", padding="same")(second_conv)

        flatten_conv = Flatten()(third_conv)
        #first_dense = Dense(8, activation='relu')()

        merge = concatenate([flatten_conv, turn])

        second_dense = Dense(512, activation='relu')(merge)
        output = Dense(self.action_size)(second_dense)

        self.model = Model(inputs=[boards, turn], outputs=output)
        self.model.compile(loss='mse', optimizer=Adam(lr=self.lr))

        return self.model

    def get_model(self):
        return self.model
        
    def act(self, state, legal_moves):
        # eps greedy
        if np.random.rand() <= self.eps:
            action = random.randint(0,6)
            while legal_moves[action] == False:
                action = random.randint(0,6)
            return action

        mask = []
        for index in range(len(legal_moves)):
            if legal_moves[index] == False:
                mask.append(self.mask_value)
            else:
                mask.append(0)

        q_values = self.model.predict(state)
        q_values[0] = q_values[0] + mask

        if self.human_play:
            print(q_values)
            #print(state)

        return np.argmax(q_values[0])

    def save(self, prev_state, action, reward, curr_state, terminal):
        self.memory.append((prev_state, action, reward, curr_state, terminal))

    def learn(self):
        batch = random.sample(self.memory, self.batch_size)

        boards = []
        turns = []
        targets = []
        for prev_state, action, reward, curr_state, terminal in batch:
            q_next_values = self.model.predict(curr_state)

            if terminal:
                target = reward
            else:
                target = reward + self.gamma * np.max(q_next_values[0])

            q_next_values[0][action] = target

            boards.append(prev_state[0])
            turns.append(prev_state[1])
            targets.append(np.array(q_next_values))

        boards = np.squeeze(boards, axis=1)
        turns = np.squeeze(turns, axis=1)
        targets = np.squeeze(targets, axis=1)

        if self.steps % self.tensor_log_steps == 0:
            self.model.fit([boards, turns], targets, batch_size=self.batch_size, epochs=1, verbose=0, callbacks=[self.tensorBoard])
        else:
            self.model.fit([boards, turns], targets, batch_size=self.batch_size, epochs=1, verbose=0)
        
        self.learn_times += 1
        
        if self.eps > self.eps_min:
            self.eps -= self.eps_decay

    def step(self, response, legal_moves):
        reward = response[0]
        curr_board = response[1]
        terminal = response[2]
        turn = response[3]

        if curr_board.ndim == 3:
            curr_board = np.expand_dims(curr_board, axis=0)

        curr_state = [np.array(curr_board), np.expand_dims(turn, axis=0)]

        if self.prev_action != -1:
            self.save(self.prev_state, self.prev_action, reward, curr_state, terminal)

        if self.steps > self.learn_after_steps and self.steps % self.train_every_steps == 0:
            self.learn()

        action = self.act(curr_state, legal_moves)

        self.prev_action = action
        self.prev_state = curr_state
        self.steps += 1

        return action

    def reset(self, response):
        reward = response[0]
        curr_board = response[1]
        terminal = response[2]
        turn = response[3]

        self.games_played += 1

        if reward == 1:
            self.wins += 1
            self.all_games_played.append(1)
        else:
            self.all_games_played.append(0)

        if curr_board.ndim == 3:
            curr_board = np.expand_dims(curr_board, axis=0)

        curr_state = [np.array(curr_board), np.expand_dims(turn, axis=0)]

        self.save(self.prev_state, self.prev_action, reward, curr_state, terminal)

        if self.steps > self.learn_after_steps and self.steps % self.train_every_steps == 0:
            self.learn()

        self.prev_action = -1
        self.prev_state = None

    def save_model(self, run, episode, agent_num):
        self.model.save("models/agent_" + str(agent_num) + ".h5")

    def load_model(self, agent):
        self.model = load_model("models/agent_" + str(agent) + ".h5")


class CustomTensorBoard(TensorBoard):
    def __init__(self, agent, *args, **kwargs):
        super(CustomTensorBoard, self).__init__(*args, **kwargs)
        self.agent = agent
    
    def get_winrate(self):
        winrate = self.agent.wins / self.agent.games_played

        return winrate

    def get_winrate_lastn(self, n):
        length = len(self.agent.all_games_played)
        last_n_games = self.agent.all_games_played[length-n : length]

        winrate = sum(last_n_games) / n

        return winrate

    def on_epoch_end(self, epoch, logs=None):
         logs.update({"winrate": self.get_winrate(),
                      "winrate_last10": self.get_winrate_lastn(10),
                      "winrate_last100": self.get_winrate_lastn(100)
                     })
         super(CustomTensorBoard, self).on_epoch_end(epoch, logs)