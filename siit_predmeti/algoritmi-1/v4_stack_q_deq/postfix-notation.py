# conversion from prefix to postfix notation of algebraic operations

# 3*2-1  =>   3 2 * 1 -

from stack import Stack

def postfix(expression):
    postfix_expression = ""
    priority = False

    for character in expression:
        if character == "*" or character == "/":
            s.push(character)
            priority = True
        elif character == "+" or character == "-":
            if not priority:
                s.push(character)
            else:
                while not s.is_empty():
                    postfix_expression += s.pop()
                s.push(character)
            priority = False
        else:
            postfix_expression += character

    while not s.is_empty():
        postfix_expression += s.pop()

    return postfix_expression


if __name__ == "__main__":
    s = Stack()

    expression = input("Napisati izraz u prefiksnoj notaciji: ")

    print(postfix(expression))

# zagrade - svaki izraz kao da je poseban izraz. stavlja se sve na stek od otvorene zagrade i onda se sklanja sve dok ne dodje opet do otvorene.