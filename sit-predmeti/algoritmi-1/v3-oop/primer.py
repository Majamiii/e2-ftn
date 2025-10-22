# klasa ComplexNumber za kompleksne brojeve

# metode za pristum Re i Im delu
# metoda __str__
# + - * /

class ComplexNumber:
    
    def __init__(self,re=0,im=0):
        self._re = re
        self._im = im

    def get_re(self):
        return self._re
    
    def get_im(self):
        return self._im
    
    def __str__(self):
        return str(self._re) + " + " + str(self._im) + "i"

    def __add__(self, num):
        re_2 = num.get_re()
        im_2 = num.get_im()
        re_1 = self._re
        im_1 = self._im

        return ComplexNumber(re_1+re_2, im_1+im_2)
    
    def __sub__(self, num):
        re_2 = num.get_re()
        im_2 = num.get_im()
        re_1 = self._re
        im_1 = self._im

        return ComplexNumber(re_1-re_2, im_1-im_2)
    
if __name__ == "__main__":
    a = ComplexNumber(1,2)
    print(a)
    b = ComplexNumber(4,5)

    print(a+b)

    