from state import State
import time
import copy

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
    def max(self, depth=0):
        #   return 0,0,0

        depth += 1

        maxv = -1500
        px = None
        py = None
        result, winner = self._current_state.is_end('O')

        if result:
            if winner == 'X':
                return -1000, 0, 0
            elif winner == 'O':
                return 1000, 0, 0
            else:
                return 0, 0, 0
            
        if depth>3:
            maxv = self._current_state.heuristics('O')
            #   self._current_state.clean_available_moves('O')
            return maxv, 0, 0
            
        # game is not over
        for i in range(0,8):
            for j in range(0,8):
                if self._current_state.get_value(i,j) == '*':
                    og_board = copy.deepcopy(self._current_state._board)
                    self._current_state.set_value(i,j,'O')
                    self._current_state.reset_available_moves('O')
                    (m, min_i, min_j) = self.min(depth)
                    if m>maxv:
                        maxv = m
                        px = i
                        py = j
                    self._current_state._board = og_board
        return maxv, px, py

    # player X (human player) is min
    def min(self, depth = 0):
        #   return 0,0,0
        depth += 1

        minv = 1500
        px = None
        py = None
        result, winner = self._current_state.is_end('X')

        if result:
            if winner == 'X':
                return -1000, 0, 0
            elif winner == 'O':
                return 1000, 0, 0
            else:
                return 0, 0, 0
            
        if depth>3:
            minv = self._current_state.heuristics('X')
            #   self._current_state.clean_available_moves('O')
            return minv, 0, 0
            
        # game is not over
        for i in range(0,8):
            for j in range(0,8):
                if self._current_state.get_value(i,j) == '*':
                    og_board = copy.deepcopy(self._current_state._board)
                    self._current_state.set_value(i,j,'X')
                    self._current_state.reset_available_moves('X')
                    (m, min_i, min_j) = self.max(depth)
                    if m<minv:
                        minv = m
                        px = i
                        py = j
                    self._current_state._board = og_board
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
                    #(m, px, py) = self.min()
                    end = time.time()
                    print("Evaluation time: ", end-start)
                    #   print("Recommended move: ", px, py)

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
                (m, px, py) = self.max()
                self._current_state.set_value(px,py,'O')
                self._player_turn = 'X'