import sys
import os
import json


sys.path.append(os.getcwd() + "/..")
from testslide import TestCase


from map.map import GLOBAL_MAP, Coordinate, Map
from communication.packet import Packet


class TestMap(TestCase):
    def setUp(self):
        super().setUp()
        self.map = Map()
        self.packet1 = Packet(1,3,7,1,0,0,0,0)
        self.packet2 = Packet(1,3,7,2,0,5,0,0)
        
    def test_add_obstacle(self):
        self.map.add_obstacle(self.packet1)
        coord = Coordinate(4, 7)
        self.assertTrue(coord in self.map.map)
        self.map.add_obstacle(self.packet2)
        print(self.map.distance)
        self.assertTrue(False)
        

    def test_global_map(self):
        self.map.add_obstacle(self.packet1)
        coord1 = Coordinate(4, 7)

        new_map = Map()
        new_map.add_obstacle(self.packet2)
        coord2 = Coordinate(5, 7)

        x = 7
        y = 8
        coord3 = Coordinate(x, y)
        self.assertTrue(coord1 in GLOBAL_MAP)
        self.assertTrue(coord2 in GLOBAL_MAP)
        self.assertTrue(coord3 not in GLOBAL_MAP)

    # def test_get_map(self):
    #     x1 = 3
    #     y1 = 7
    #     self.map.add_obstacle(self.packet1)

    #     x2 = 8
    #     y2 = 7
    #     self.map.add_obstacle(self.packet2)

    #     idx = 1
    #     map = self.map.get_map(idx)
    #     returned_map = json.loads(map)
    #     self.assertTrue(returned_map["id"] == 1)
    #     self.assertTrue(returned_map["x"] == [x2,x1])
    #     self.assertTrue(returned_map["y"] == [y2,y1])





