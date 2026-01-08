# first task: implement Stack class
# and LimitedStack with a limit (input)

class StackError(Exception):
    pass

class Stack:
    def __init__(self):
        self._data = []

    def __len__(self):
        return len(self._data)

    def is_empty(self):
        return len(self._data) == 0

    def push(self, element):
        self._data.append(element)

    def top(self):
        return self._data[-1]
    
    def pop(self):
        if len(self._data)==0:
            raise StackError("Stack is empty")
        return self._data.pop()
    

class LimitedStack(Stack):
    def push(self,element, n):
        if (len(self._data) == n):
            raise StackError("Stack limit reached")
        self._data.append(element)

    
if __name__ == "__main__":
    n = int(input("Uneti limit za stack: "))

    s = LimitedStack()
    s.push(2,n)
    print(s.top())
    print(len(s))

    s.pop()
    print(s.is_empty())

    s.push(5,n)
    s.push(6,n)
    s.push(999,n)
    s.push(1,n)
    #   s.pop()