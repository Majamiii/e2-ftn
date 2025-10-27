
class Player:
    def __init__(self, health, mana):
        self._health = health
        self._mana = mana

    @property
    def health(self):
        return self._health
    @health.setter
    def health(self,health):
        self._health = health
    
    @property
    def mana(self):
        return self._mana
    @mana.setter
    def mana(self,mana):
        self._mana = mana

    def __str__(self):
        return "PLAYER :   health: " + str(self._health) + "   mana: " + str(self._mana)
    
class Item:
    def __init__(self,value):
        self._value = value

    @property
    def value(self):
        return self._value
    @value.setter
    def value(self,value):
        self._value = value

    def __str__(self):
        return "ITEM:    value: " + str(self._value)
    
    def use(self, player):
        pass
    
class Food(Item):    
    def use(self,player):
        player.health += self.value

    def __str__(self):
        return "FOOD :     value: " + str(self._value)
    
class Potion(Item):
    def __init__(self, value, type):
        super().__init__(value)
        self._type = type
    
    @property
    def type(self):
        return self._type
    @type.setter
    def type(self,type):
        self._type = type

    def __str__(self):
        return "POTION:    value: " + str(self._value) + "    type: " + str(self._type)
    
    def use(self,player):
        if (self.type.lower() == "health"):
            player.health += self.value
        elif (self.type.lower() == "mana"):
            player.mana += self.value
        else:
            raise ValueError("Tip potion-a moze biti samo health ili mana.")


if __name__ == "__main__":

    player = Player(100, 100)
    print(player)

    f1 = Food(100)
    p1 = Potion(200, "health")
    p2 = Potion(300, "mana")

    item_list = [f1,p1,p2]

    for item in item_list:
        print(item)
        item.use(player)
        print(player)