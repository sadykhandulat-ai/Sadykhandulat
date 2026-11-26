class pizza:
    @staticmethod
    def make_pizza(size, *toppings):
        """Summarize the pizza we are about to make."""
        print(f"\nMaking a {size}-inch pizza with the following toppings:")
        for topping in toppings:
            print(f"- {topping}")
    @classmethod
    def make_vegetarian_pizza(cls, size):
        return cls.make_pizza(size, "mushrooms", "peppers", "onions")
    @classmethod
    def make_meat_lovers_pizza(cls, size):
        return cls.make_pizza(size, "pepperoni", "sausage", "bacon")
    @staticmethod
    def make_custom_pizza(size, *toppings):
        return pizza.make_pizza(size, *toppings)
    @staticmethod
    def make_hawaiian_pizza(size):  
        return pizza.make_pizza(size, "ham", "pineapple")