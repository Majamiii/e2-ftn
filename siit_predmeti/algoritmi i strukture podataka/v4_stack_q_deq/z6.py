# calculating the value of postfix expression using Stack

from stack import Stack

def calculate(expression):

    value = 0

    for character in expression:

        if character >= ascii(0) and character <= ascii(9):     # if its a number
            s.push(character)
            if value == 0:
                value = int(character)

        elif character == "+":
            value += int(s.pop())
        elif character == "-":
            value -= int(s.pop())
        elif character == "/":
            value /= int(s.pop())
        elif character == "*":
            value *= int(s.pop())

    return value

if __name__=="__main__":
    s = Stack()
    print(calculate("3 2 * 5-"))