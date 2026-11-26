class vehicle:
    def __init__(self, make, model):
        self.make = make
        self.model = model

    def start_engine(self):
        return f"The engine of the {self.make} {self.model} is starting."
class car(vehicle):
    def __init__(self, make, model, num_doors):
        super().__init__(make, model)
        self.num_doors = num_doors

    def start_engine(self):
        return f"The engine of the {self.make} {self.model} car with {self.num_doors} doors is starting."
class electricCar(car):
    def __init__(self, make, model, num_doors, battery_capacity):
        super().__init__(make, model, num_doors)
        self.battery_capacity = battery_capacity

    def start_engine(self):
        return f"The electric engine of the {self.make} {self.model} car with {self.num_doors} doors and a battery capacity of {self.battery_capacity} kWh is starting."

class motorcycle(vehicle):
    def __init__(self, make, model, has_sidecar):
        super().__init__(make, model)
        self.has_sidecar = has_sidecar

    def start_engine(self):
        sidecar_info = "with a sidecar" if self.has_sidecar else "without a sidecar"
        return f"The engine of the {self.make} {self.model} motorcycle {sidecar_info} is starting."