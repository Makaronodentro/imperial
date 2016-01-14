class Shape:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def area(self):
        return self.x * self.y

rectangle = Shape(100, 45)
print rectangle.area()
