# 1. prvo sa neogranicenim brojem elemenata
# 2. onda ograniciti sa N
# 3. efikasnije upravljanje memorijskim prostorom: cirkularno smestanje elemenata

class QueueError(Exception):
    pass

class Queue:
    def __init__(self):
        self._data = []

    def __len__(self):
        return len(self._data)
    
    def is_empty(self):
        return len(self._data)==0
    
    def enqueue(self, element):
        self._data.append(element)

    def dequeue(self):
        element = self._data[0]
        del self._data[0]
        return element
    
    def first(self):
        return self._data[0]
    

class QueueCircular():
    def __init__(self, capacity=10):
        self._size = 0
        self._first = 0
        self._capacity = capacity
        self._data = [None]*self._capacity
    def __len__(self):
        return self._size
    def is_empty(self):
        return self._size == 0
    def first(self):
        return self._data[self._first]
    
    def dequeue(self):
        # izbacuje prvi element iz reda
        if self.is_empty():
            raise QueueError("Red je prazan.")
        element = self._data[self._first]
        # brisanje se vrsi postavljanjem sadrzaja na vrednost None
        self._data[self._first] = None

        # pomeramo indekse ali gledamo moduo pri deljenju jer je red cirkularan
        self._first = ( self._first + 1 ) % self._capacity
        self._size -= 1

        if (0 < self._size < self._capacity//4):
            self._resize(self._capacity//2)

        return element
    
    def enqueue(self, element):
        if self._size == self._capacity:
            self._resize(2*self._capacity)

        # novi element je prvi iza trenutno poslednjeg
        index = (self._first + self._size) % self._capacity
        self._data[index] = element
        self._size += 1
    
    def _resize(self, capacity):
        current_data = self._data
        current_first = self._first

        # kreira se prazna lista sa zadanim brojem elemenata
        self._data = [None]*capacity

        for k in range(self._size):
            self._data[k] = current_data[current_first]
            current_first = (current_first+1) % len(current_data)


if __name__ == "__main__":

    queue = QueueCircular()
    queue.enqueue(3)
    queue.enqueue(8)
    queue.enqueue(1)
    print(len(queue))
    print(queue.first())

    queue.dequeue()
    print(len(queue))

    print(queue.first())
    print(queue.is_empty())