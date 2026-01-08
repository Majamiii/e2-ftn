class EmptyListException(Exception):
    pass

# -------- NODE ----------

class SinglyLinkedListNode(object):
    def __init__(self, value, next_node =None):
        self._value = value
        self._next = next_node

    @property
    def value(self):
        return self._value
    @value.setter
    def value(self,value):
        self._value = value


    @property
    def next(self):
        return self._next
    @next.setter
    def next(self,node):
        self._next = node

    def __str__(self):
        return str(self._value)
    

# -------- LIST -----------


class SinglyLinkedList:
    def __init__(self):
        self._head = None
        self._tail = None
        self._size = 0

    def is_empty(self):
        return len(self)==0
    def __len__(self):
        return self._size
    
    def __iter__(self):
        current_node = self._head
        while current_node:
            yield current_node
            current_node = current_node.next

    def __getitem__(self, my_index):
        index = 0
        if my_index < 0:
            my_index += len(self)
        for node in self:
            if index == my_index:
                return node
            index += 1
            if index >= len(self):
                raise IndexError("Index out of range !")

    def __delitem__(self, index):
        if index < 0:
            index = len(self) + index
        node = self[index]
        if node == self._head:
            self._head = node.get_next()
        elif node == self._tail:
            self[index-1].set_next(None)
            self._tail = self[index-1]
        else:
            previous = self[index - 1]
            previous.set_next(node.get_next())

    def __setitem__(self, index, value):
        self[index].set_data(value)

    def get_first(self):
        if self.is_empty():
            raise EmptyListException("List is empty")
        return self._head
    def get_last(self):
        if self.is_empty():
            raise EmptyListException("List is empty")
        return self._tail
    
    def add_first(self, value):

        new_node = SinglyLinkedListNode(value)

        if self.is_empty():
            self._tail = new_node
        else:
            new_node.next = self._head

        self._head = new_node
        self._size += 1

    def add_last(self,value):
        new_node = SinglyLinkedListNode(value)

        if self.is_empty():
            self._head = new_node
        else:
            self._tail.next = new_node

        self._tail = new_node
        self._size += 1

    def remove_first(self):
        if self.is_empty():
            raise EmptyListException("List is empty")
        if self._size == 1:
            self._tail = None
            return
        self._head = self._head.next
        self._size -= 1

    def remove_last(self):
        if self.is_empty():
            raise EmptyListException("List is empty")
        if self._size == 1:
            self._head = None
            self._tail = None
            return

        curr = self._head

        while curr.next != self._tail:
            curr = curr.next
        
        curr.next = None
        self._tail = curr
        self._size -= 1

    def append(self,value):
        self.add_last(value)

    def extend(self, other_list):
        if other_list.is_empty():
            return
        
        if self.is_empty():
            self._head = other_list._head
            self._tail = other_list._tail
            self._size = other_list._size
            return

        self._tail.next = other_list._head
        self._tail = other_list._tail
        self._size += other_list.size()

    def insert(self,index,value):
        # ako je idx negativan bice upisan na pocetak
        # ako je veci od br el liste bice upisan na kraj
        self.append(None)
        if index < 0:
            index += len(self)
        for i in range(len(self)-1, index, -1):
            self[i] = self[i-1].get_data()
        self[index] = value
        if self[index] != self._tail:
            self[index].set_next(self[index+1])

    def remove(self, value):
        curr = self._head
        previous = None

        while curr.value != value:
            previous = curr
            curr = curr.next

        if previous != None: previous.next = curr.next
        else: self._head = self._head.next

        self._size -= 1

    def pop(self, index = -1):
        index = self._fix_index(index)
        counter = 0

        while counter != index:
            previous = curr
            curr = curr.next
            counter += 1

        if previous != None: previous.next = curr.next
        else: self._head = self._head.next

        self._size -= 1

    def _fix_index(self, index, more_than_len_allowed = False):
        if not more_than_len_allowed and (self._size<index):
            raise IndexError("Last index out of range")
        if index < - self._size:
            return 0
        elif index<0:
            return self._size + index + 1
        if index>= self._size:
            return self._size
        return index
    
    def __str__(self):
        string = "["
        string += ", ".join([str(item) for item in self])
        string += "]"
        return string
    
        



if __name__ == "__main__":

    a = [1,2,3]
    b = [5,6,7]
    a.append(4)
    a.extend(b)
    print(a)

    l1 = SinglyLinkedList()
    l1.add_first(5)
    l1.add_first(4)
    l1.add_first(3)
    for item in l1: print(item)
    l1.remove_last()
    for item in l1: print(item)

    l1.append(7)
    for item in l1: print(item)

    l1.remove(4)
    for item in l1: print(item)