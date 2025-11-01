from state import State
import time

class Game:
    __slots__ = ['_current_state', '_player_turn']

    def __init__(self):
        self._current_state = None
        self._player_turn = 'X'
        self.initialize_game()
    def initialize_game(self):
        self._current_state = State()
        self._player_turn = 'X'

    # player O is max
    def max(self):
        maxv = -2
        px = None
        py = None
        result, winner = self._current_state.is_end()

        if result:
            if winner == 'X':
                return -1, 0, 0
            elif winner == 'O':
                return 1, 0, 0
            else:
                return 0, 0, 0
            
        # game is not over
        for i in range(0,3):
            for j in range(0,3):
                if self._current_state.get_value(i,j) == '-':
                    self._current_state.set_value(i,j,'O')
                    (m, min_i, min_j) = self.min()
                    if m>maxv:
                        maxv = m
                        px = i
                        py = j
                    self._current_state.set_value(i,j,'-')
        return maxv, px, py
    
    def min(self):
        minv = 2
        qx = None
        qy = None
        result, winner = self._current_state.is_end()
        if result:
            if winner == 'X':
                return -1,0,0
            elif winner == 'O':
                return 1,0,0
            else:
                return 0,0,0
        for i in range(0,3):
            for j in range(0,3):
                if self._current_state.get_value(i,j) == '-':
                    self._current_state.set_value(i,j,'X')
                    (m, max_i, max_j) = self.max()
                    if m<minv:
                        minv = m
                        qx = i
                        qy = j
                    self._current_state.set_value(i,j,'-')
        return minv, qx, qy
    
    def play(self):
        while True:
            print(self._current_state)
            result, winner = self._current_state.is_end()

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
                    (m, qx, qy) = self.min()
                    end = time.time()
                    print('Evaluation time: {}s'.format(round(end - start, 7)))
                    print('Recommended move: X = {}, Y = {}'.format(qx, qy))

                    px = int(input('Insert the X coordinate: '))
                    py = int(input('Insert the Y coordinate: '))
                    
                    if self._current_state.is_move_valid(px, py, 'X'):
                        self._current_state.set_value(px, py, 'X')
                        self._player_turn = 'O'
                        print(self._current_state)
                        break
                    else:
                        print('The move is not valid! Try again.')

            else:
                (m, px, py) = self.max()
                self._current_state.set_value(px, py, 'O')
                self._player_turn = 'X'