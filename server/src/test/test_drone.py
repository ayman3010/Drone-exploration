import sys
import os




sys.path.append(os.getcwd() + "/..")
from testslide import TestCase

from drone.drone import DRONES, Drone, add_flight_to_db
from database.database import HistoricFlights, HistoricMaps
from database.object_entry import FlightType



class TestDrone(TestCase):
    def setUp(self):
        super().setUp()
        self.drone = Drone(3)

    def test_start_mission(self):
        self.drone.start_mission()
        self.assertTrue(self.drone.isActive == True)

    def test_add_map_to_db(self):
        db_instance = HistoricMaps()
        self.mock_callable(db_instance, "add_map").to_return_value(None).and_assert_called_once()
        self.drone.add_map_to_db()

    def test_add_flight_db(self):
        DRONES[0].start_mission()
        db_instance = HistoricFlights()
        self.mock_callable(db_instance, "add_flight").to_return_value(None).and_assert_called_once()
        add_flight_to_db(1, FlightType.FLIGHT)

