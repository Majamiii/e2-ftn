from math import sqrt

# moze i samo   class Point:
class Point(object):

    def __init__(self, x=0, y=0):
        self._x = x
        self._y = y

    def get_x(self):
        return self._x
    
    def get_y(self):
        return self._y
    
    def __str__(self):
        return "Point (x=" + str(self._x) + ", y=" + str(self._y) + ")"
    
    def distance(self,tacka):
        x2 = tacka.get_x()
        y2 = tacka.get_y()
        x1 = self._y
        y1 = self._y
        return sqrt((x1-x2)**2 + (y1-y2)**2)
    

if __name__ == "__main__":
    p1 = Point(4,5)
    print(p1)
    p2 = Point()

    print(p1.distance(p2))