class shape:
    def area(self):
        pass
class circle(shape):
    def __init__(self, radius):
        self.radius = radius

    def area(self):
        return 3.14 * self.radius * self.radius
class rectangle(shape):
    def __init__(self, width, height):
        self.width = width
        self.height = height

    def area(self):
        return self.width * self.height
class triangle(shape):
    def __init__(self, base, height):
        self.base = base
        self.height = height

    def area(self):
        return 0.5 * self.base * self.height
shapes = [circle(5), rectangle(4, 6), triangle(3, 8)]
for shape in shapes:
    print(f"The area of the {shape.__class__.__name__} is: {shape.area()}")
    for shape in shapes:
        print(f"The area of the {shape.__class__.__name__} is: {shape.area()}")