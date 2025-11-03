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
        self.update_board(i,j,value)

    def taken_corners(self, player):
        corners = 0
        if self._board[0][0] == player:
            corners +=1
        if self._board[7][7] == player:
            corners +=1
        if self._board[0][7] == player:
            corners +=1
        if self._board[7][0] == player:
            corners +=1
        return corners
    
    def taken_corners_opponent(self, move):
        corners = 0
        if move == 'X': player = 'O'
        elif move == 'O': player = 'X'
        if self._board[0][0] == player:
            corners +=1
        if self._board[7][7] == player:
            corners +=1
        if self._board[0][7] == player:
            corners +=1
        if self._board[7][0] == player:
            corners +=1
        return corners
    
    def taken_pieces(self, player):
        pieces = 0
        for i in range(0,8):
            for j in range(0,8):
                if self._board[i][j] == player:
                    pieces += 1
        return pieces
    
    def taken_pieces_opponent(self, move):
        if move == 'X': player = 'O'
        elif move == 'O': player = 'X'
        pieces = 0
        for i in range(0,8):
            for j in range(0,8):
                if self._board[i][j] == player:
                    pieces += 1
        return pieces
    
    def taken_around_corners(self, player):
        return 0

    def is_move_valid(self,i,j,move):
        move = move.upper()
        if move not in 'XO':
            return False
        self.reset_available_moves(move)
        if self._board[i][j] != '*':
            return False
        return True
    
    def available_moves(self):
        available = 0
        for i in range(0,8):
            for j in range(0,8):
                if self._board[i][j] == '*': available += 1
        return available

    
    def mark_available_moves(self, player='X'):     # player = 'X' or 'O'
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

    def reset_available_moves(self, player='X'):
        for i in range(0,8):
            for j in range(0,8):
                if self._board[i][j] == '*':
                    self._board[i][j] = '-'
        self.mark_available_moves(player)
        return self._board
    
    def clean_available_moves(self, player='X'):
        for i in range(0,8):
            for j in range(0,8):
                if self._board[i][j] == '*':
                    self._board[i][j] = '-'

    def update_board(self, qx, qy, value, first=True, direction=1):
        # directions are clockwise from 1 to 8 - we should always keep going in the same direction

        if first:
            for direction in range(1,9):
                # dir=1, we are checking bottom-up
                if direction==1 and qx>0:
                    if self._board[qx-1][qy] not in [value, '-', '*'] and self._board[qx-1][qy] in "XO":
                        self._board[qx-1][qy] = value
                        self.update_board(qx-1, qy, value, False, 1)

                if direction == 2 and qx>0 and qy<6:
                    if self._board[qx-1][qy+1] not in [value, '-', '*'] and self._board[qx-1][qy+1] in "XO":
                        self._board[qx-1][qy+1] = value
                        self.update_board(qx-1, qy+1, value, False, 2)
                
                if direction == 3 and qy<6:
                    if self._board[qx][qy+1] not in [value, '-', '*'] and self._board[qx][qy+1] in "XO":
                        self._board[qx][qy+1] = value
                        self.update_board(qx, qy+1, value, False, 3)

                if direction == 4 and qx<6 and qy<6:
                    if self._board[qx+1][qy+1] not in [value, '-', '*'] and self._board[qx+1][qy+1] in "XO":
                        self._board[qx+1][qy+1] = value
                        self.update_board(qx+1, qy+1, value, False, 4)
                
                if direction == 5 and qx<6:
                    if self._board[qx+1][qy] not in [value, '-', '*'] and self._board[qx+1][qy] in "XO":
                        self._board[qx+1][qy] = value
                        self.update_board(qx+1, qy, value, False, 5)
                
                if direction == 6 and qx<6 and qy>0:
                    if self._board[qx+1][qy-1] not in [value, '-', '*'] and self._board[qx+1][qy-1] in "XO":
                        self._board[qx+1][qy-1] = value
                        self.update_board(qx+1, qy-1, value, False, 6)

                if direction == 7 and qy>0:
                    if self._board[qx][qy-1] not in [value, '-', '*'] and self._board[qx][qy-1] in "XO":
                        self._board[qx][qy-1] = value
                        self.update_board(qx, qy-1, value, False, 7)
                
                if direction == 8 and qx>0 and qy>0:
                    if self._board[qx-1][qy-1] not in [value, '-', '*'] and self._board[qx-1][qy-1] in "XO":
                        self._board[qx-1][qy-1] = value
                        self.update_board(qx-1, qy-1, value, False, 8)

        

        else:
            # not the first time entering the loop - we must keep going in the same direction
            # dir=1, we are checking bottom-up
            
            if direction==1 and qx>0:
                if self._board[qx-1][qy] not in [value, '-', '*'] and self._board[qx-1][qy] in "XO":
                    self._board[qx-1][qy] = value
                    self.update_board(qx-1, qy, value, False, 1)

            if direction == 2 and qx>0 and qy<6:
                if self._board[qx-1][qy+1] not in [value, '-', '*'] and self._board[qx-1][qy+1] in "XO":
                    self._board[qx-1][qy+1] = value
                    self.update_board(qx-1, qy+1, value, False, 2)
            
            if direction == 3 and qy<6:
                if self._board[qx][qy+1] not in [value, '-', '*'] and self._board[qx][qy+1] in "XO":
                    self._board[qx][qy+1] = value
                    self.update_board(qx, qy+1, value, False, 3)

            if direction == 4 and qx<6 and qy<6:
                if self._board[qx+1][qy+1] not in [value, '-', '*'] and self._board[qx+1][qy+1] in "XO":
                    self._board[qx+1][qy+1] = value
                    self.update_board(qx+1, qy+1, value, False, 4)
            
            if direction == 5 and qx<6:
                if self._board[qx+1][qy] not in [value, '-', '*'] and self._board[qx+1][qy] in "XO":
                    self._board[qx+1][qy] = value
                    self.update_board(qx+1, qy, value, False, 5)
            
            if direction == 6 and qx<6 and qy>0:
                if self._board[qx+1][qy-1] not in [value, '-', '*'] and self._board[qx+1][qy-1] in "XO":
                    self._board[qx+1][qy-1] = value
                    self.update_board(qx+1, qy-1, value, False, 6)

            if direction == 7 and qy>0:
                if self._board[qx][qy-1] not in [value, '-', '*'] and self._board[qx][qy-1] in "XO":
                    self._board[qx][qy-1] = value
                    self.update_board(qx, qy-1, value, False, 7)
            
            if direction == 8 and qx>0 and qy>0:
                if self._board[qx-1][qy-1] not in [value, '-', '*'] and self._board[qx-1][qy-1] in "XO":
                    self._board[qx-1][qy-1] = value
                    self.update_board(qx-1, qy-1, value, False, 8)
        
        return


        
    def __str__(self):
        #   self.reset_available_moves()        # should be commented out
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
    
    def is_end(self, player):
        found_option = False
        self.reset_available_moves(player)
        for i in range(0,8):
            for j in range(0,8):
                if self._board[i][j] == '*':
                    found_option = True, None
        if found_option: return False, None

        # so no options were found for this player, the other is a winner
        if player == 'X': return True, 'O'
        elif player == 'O': return True, 'X'
        else:
            raise Exception("Error: Bug: No moves found but no winner either")
        


        
    #   -------------------------------------------------
    #   TACICS - HEURISTICS - THE MOST IMPORTANT FUNCTION
    #   -------------------------------------------------

    def heuristics(self, player):       
        # use it simply like this for the maximizer
        # and for the minimizer take the negative value of the return value of heuristics
        score = 0
        score += 100 * (self.taken_pieces(player) / self.taken_pieces_opponent(player))
        score += 50 * self.taken_corners(player)  -  20*self.taken_corners_opponent(player)
        score -= 30 * self.taken_around_corners(player)     #  TODO: implement this
        score += 20 * self.available_moves()

        return score
        