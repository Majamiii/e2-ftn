from state import State
import time
import copy

# change depth level for minimizer (player) and maximizer (AI) for different speeds and qualities of moves

# initial value: 7 for AI and 8 for minimizer (so that you always win if you follow the reccomendationed moves ;)

class Game():
    __slots__ = ['_current_state', '_player_turn']
    def __init__(self):
        self._current_state = None
        self._player_turn = 'X'
        self.initialize_game()
    def initialize_game(self):
        self._current_state = State()
        self._player_turn = 'X'

    # player O (AI) is max
    def max(self, state, depth=0, alpha=-2000, beta=2000):

        depth += 1

        maxv = -1500
        px = None
        py = None
        result, winner = state.is_end('O')

        if result:
            if winner == 'X':
                return -1000, 0, 0
            elif winner == 'O':
                return 1000, 0, 0
            else:
                return 0, 0, 0
            
        if depth>7:
            maxv = state.heuristics('O')
            return maxv, 0, 0
            
        # game is not over
        for i in range(0,8):
            for j in range(0,8):
                if state.get_value(i,j) == '*':

                    new_state = copy.deepcopy(state)
                    new_state.set_value(i, j, 'O')
                    new_state.reset_available_moves('O')

                    (m, min_i, min_j) = self.min(new_state, depth, alpha, beta)
                    if m>maxv:
                        maxv = m
                        px = i
                        py = j

                    if maxv >= beta:
                        return maxv,px,py
                    if maxv>alpha:
                        alpha = maxv

        return maxv, px, py



    # player X (human player) is min
    def min(self, state, depth = 0, alpha=-2000, beta=2000):
        #   return 0,0,0
        depth += 1

        minv = 1500
        px = None
        py = None
        result, winner = state.is_end('X')

        if result:
            if winner == 'X':
                return -1000, 0, 0
            elif winner == 'O':
                return 1000, 0, 0
            else:
                return 0, 0, 0
            
        if depth>8:
            minv = -state.heuristics('X')
            return minv, 0, 0
            
        # game is not over
        for i in range(0,8):
            for j in range(0,8):
                if state.get_value(i,j) == '*':

                    new_state = copy.deepcopy(state)
                    new_state.set_value(i, j, 'X')
                    new_state.reset_available_moves('X')

                    (m, min_i, min_j) = self.max(new_state, depth, alpha, beta)
                    if m<minv:
                        minv = m
                        px = i
                        py = j

                        
                    if minv <= alpha:
                        return minv, px, py

                    if minv < beta:
                        beta = minv

        return minv, px, py
    

    def play(self):
        while True:
            self._current_state.reset_available_moves(self._player_turn)
            print("Player ", self._player_turn, "turn")
            result, winner = self._current_state.is_end(self._player_turn)
            print(self._current_state)

            if result:
                if winner == 'X':
                    print('The winner is X!')
                elif winner == 'O':
                    print('The winner is O!')
                else:
                    print("It's a tie!")

                self.initialize_game()
                return
            
            if self._player_turn == 'X':
                while True:
                    start = time.time()
                    (m, px, py) = self.min(copy.deepcopy(self._current_state))
                    end = time.time()
                    print("Evaluation time: ", end-start)
                    print("Recommended move: ", py, px)

                    qy = int(input("Set x coordinate: "))
                    if qy<0 or qy>7:
                        print("Value not in range [0,7], try again!")
                        continue
                    qx = int(input("Set y coordinate: "))
                    if qx<0 or qx>7:
                        print("Value not in range [0,7], try again!")
                        continue

                    if self._current_state.is_move_valid(qx, qy, 'X'):
                        self._current_state.set_value(qx,qy,'X')
                        self._player_turn = 'O'
                        print(self._current_state)
                        break
                    else:
                        print('The move is not valid! Try again.')


            else:
                (m, px, py) = self.max(self._current_state)
                self._current_state.set_value(px,py,'O')
                self._player_turn = 'X'