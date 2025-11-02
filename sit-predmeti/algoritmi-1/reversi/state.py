class State:
    def __init__(self):
        self._board = []
        for i in range(0,8):
            self._board.append(8 * ['-'])
        self._board[3][3] = 'X'     # X is black - starting the game - the player
        self._board[4][4] = 'X'
        self._board[3][4] = 'O'     # computer
        self._board[4][3] = 'O'
    def get_value(self, i, j):
        return self._board[i][j]
    def set_value(self,i,j,value):
        self._board[i][j] = value
    def is_move_valid(self,i,j,move):
        move = move.upper()
        if move not in 'XO':
            return False
        if self._board[i][j] != '-':
            return False
        return True
    def __str__(self):
        #   print out '*' for available moves
        diff_found = False
        for i in range(0,8):
            for j in range(0,8):
                diff_found = False
                if self._board[i][j] != '-':
                    # move = self._board[i][j]
                    move = 'X'
            #   check left
                    for k in range(1,j):
                        if self._board[i][j-k]!=move and self._board[i][j-k]!='-':      # so if its another color
                            diff_found = True
                            if self._board[i][j-k-1]=='-':
                                self._board[i][j-k-1] = '*'
                                break
                    if diff_found:
                        diff_found = False
                        break
            #   check right
                    for k in range(j+1,8):
                        if self._board[i][k]!=move and self._board[i][k]!='-':
                            diff_found = True
                            if self._board[i][k+1]=='-':
                                self._board[i][k+1] = '*'
                                break
                    if diff_found:
                        diff_found = False
                        break

        ret = "\n\n---------------------------------\n"
        for i in range(0,8):
            row = "|"
            for j in range(0,8):
                if self._board[i][j] == '-':
                    row += "   |"
                else:
                    row += " "
                    row += self._board[i][j]
                    row += " |"
            ret += row
            ret += "\n"
            ret += "---------------------------------\n"
        return ret
    def is_end(self):
        found_option = False
        for i in range(0,8):
            for j in range(0,8):
                if self._board[i][j] == '*':
                    found_option = True
        if found_option: return True
        return False

b = State()
print(b)