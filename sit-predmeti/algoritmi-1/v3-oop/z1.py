class Rectangle:
    def __init__(self,x,y):
        self._x = x
        self._y = y

    @property
    def a(self):
        return self._a
    
    @a.setter
    def a(self,value):
        self._a = value
    
    def obim(self):
        return 2 * (self._x + self._y)
    
    def povrsina(self):
        return self._x * self._y
        

class Square(Rectangle):
    def __init__(self, a):
        super().__init__(a,a)


if __name__ == "__main__":
    a = Rectangle(3,4)
    print(a.obim())

    b = Square(8)
    print(b.povrsina())