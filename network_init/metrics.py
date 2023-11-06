class Metrics:

    def __init__(self) -> None:
        self.count_transmissions = 0
        self.total_toa = 0
        self.collision_in_nodes = 0

    def add_transmission(self):
        self.count_transmissions += 1

    def return_transmissions(self):
        return self.count_transmissions

    def add_toa(self, toa):
        self.total_toa += toa

    def return_total_toa(self):
        return self.total_toa

    def add_node_collision(self):
        self.collision_in_nodes += 1

    def return_node_collisions(self):
        return self.collision_in_nodes
