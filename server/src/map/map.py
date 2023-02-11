from typing import Set

from dataclasses import dataclass
import json

from communication.packet import Packet


@dataclass
class Coordinate:
    x : float
    y : float

    def __hash__(self):
        return hash((self.x, self.y))
    
    def __eq__(self, other):
        if not isinstance(other, type(self)): 
            return NotImplemented
        return self.x == other.x and self.y == other.y
GLOBAL_MAP = set()

class Map:
    def __init__(self):
        self.map : Set[Coordinate] = set()
        self.distance = 0
        self.last_x = 0
        self.last_y = 0
        
    def add_obstacle(self, packet: Packet) -> list:
        new_obstacles = []
        self._set_distance(packet.pos_x, packet.pos_y)
        if (packet.obs_front > 0):
            x = packet.pos_x + packet.obs_front
            y = packet.pos_y 
            new_obstacles.append((x,y))
            self._add_obstacles_to_maps(Coordinate(x,y))
        if (packet.obs_back > 0):
            x = packet.pos_x  - packet.obs_back
            y = packet.pos_y
            new_obstacles.append((x,y))
            self._add_obstacles_to_maps(Coordinate(x,y))
        if (packet.obs_left > 0):
            x = packet.pos_x 
            y = packet.pos_y + packet.obs_left
            new_obstacles.append((x,y))
            self._add_obstacles_to_maps(Coordinate(x,y))
        if (packet.obs_right > 0):
            x = packet.pos_x 
            y = packet.pos_y - packet.obs_right
            new_obstacles.append((x,y))
            self._add_obstacles_to_maps(Coordinate(x,y))
        return new_obstacles
    
    def _set_distance(self, x,y):
        if self.last_x == 0 and self.last_y == 0:
            self.last_x = x
            self.last_y = y
            return
        dx = (x - self.last_x)
        dy = (y - self.last_y)
        self.distance += (dx**2 + dy**2)**0.5
        self.last_x = x
        self.last_y = y
    
    def _add_obstacles_to_maps(self, coord:Coordinate):
       self.map.add(Coordinate(coord.x, coord.y))
       GLOBAL_MAP.add(Coordinate(coord.x, coord.y))










