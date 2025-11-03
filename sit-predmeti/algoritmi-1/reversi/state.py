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
    def mark_available_moves(self, player):     # player = 'X' or 'O'
        #   print out '*' for available moves
        move = player
        for i in range(0,8):
            for j in range(0,8):
                count_found = 0
                if self._board[i][j] == move:
            #   check left
                    for k in range(1,j):
                        if self._board[i][j-k]!=move and self._board[i][j-k]!='-' and self._board[i][j-k]!='*':      # so if its another color
                            count_found += 1
                            if self._board[i][j-k-1]=='-' and count_found==1:
                                self._board[i][j-k-1] = '*'
                                break
                    if count_found:
                        count_found = 0
            #   check right
                    for k in range(j+1,7):
                        if self._board[i][k]!=move and self._board[i][k]!='-' and self._board[i][k]!='*':
                            count_found += 1
                            if self._board[i][k+1]=='-' and count_found==1:
                                self._board[i][k+1] = '*'
                                break
                    if count_found:
                        count_found = 0
            #   check up
                    for k in range(1,i):
                        if self._board[i-k][j]!=move and self._board[i-k][j]!='-' and self._board[i-k][j]!='*':      # so if its another color
                            count_found += 1
                            if self._board[i-k-1][j]=='-' and count_found==1:
                                self._board[i-k-1][j] = '*'
                                break
                    if count_found:
                        count_found = 0
            #   check down
                    for k in range(i+1,7):
                        if self._board[k][j]!=move and self._board[k][j]!='-' and self._board[k][j]!='*':      # so if its another color
                            count_found += 1
                            if self._board[k+1][j]=='-' and count_found==1:
                                self._board[k+1][j] = '*'
                                break
                    if count_found:
                        count_found = 0
            
            # check diagonal 1 (NW to SE)
                    if i>j or i==j:
                        m = i
                    else:
                        m = j
                    for k in range(1,7-m):
                        if self._board[i+k][j+k]!= move and self._board[i+k][j+k]!='-' and self._board[i+k][j+k]!='*':
                            count_found += 1
                            if self._board[i+k+1][j+k+1]=='-' and count_found==1:
                                self._board[i+k+1][j+k+1] = '*'
                                break
                    if count_found:
                        count_found = 0

            # check diagonal 2 (SE to NW)
                    if i>j or i==j:
                        m = i
                    else:
                        m = j
                    for k in range(1,m):
                            if self._board[i-k][j-k]!= move and self._board[i-k][j-k]!='-' and self._board[i-k][j-k]!='*':
                                count_found += 1
                                if self._board[i-k-1][j-k-1]=='-' and count_found==1:
                                    self._board[i-k-1][j-k-1] = '*'
                                    break
                    if count_found:
                        count_found = 0

            #   check diagonal 3 (NE to SW)
                    if 7-i<j or 7-i==j:
                        m = 7-i
                    else:
                        m = j
                    for k in range(1,m):
                        if self._board[i+k][j-k]!= move and self._board[i+k][j-k]!='-' and self._board[i+k][j-k]!='*':
                            count_found += 1
                            if self._board[i+k+1][j-k-1]=='-' and count_found==1:
                                self._board[i+k+1][j-k-1] = '*'
                                break
                    if count_found:
                        count_found = 0
            #   check diagonal 4 (SW to NE)
                    if i<7-j or i==7-j:
                        m = i
                    else:
                        m = 7-j
                    for k in range(1,m):
                        if self._board[i-k][j+k]!= move and self._board[i-k][j+k]!='-' and self._board[i-k][j+k]!='*':
                            count_found += 1
                            if self._board[i-k-1][j+k+1]=='-' and count_found==1:
                                self._board[i-k-1][j+k+1] = '*'
                                break
                    if count_found:
                        count_found = 0
    def __str__(self):
        self.mark_available_moves('X')
        ret = "\n\n"
        ret += "   | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |\n"
        ret += "   ---------------------------------\n"
        for i in range(0,8):
            row = str(i) + "  |"
            for j in range(0,8):
                if self._board[i][j] == '-':
                    row += "   |"
                else:
                    row += " "
                    row += self._board[i][j]
                    row += " |"
            ret += row
            ret += "\n"
            ret += "   ---------------------------------\n"
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