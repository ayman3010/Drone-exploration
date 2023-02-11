from dataclasses import dataclass
from enum import Enum

from map.map import Map


class FlightType(Enum):
    FLIGHT = "flight"
    SIMULATION = "simulation"


@dataclass
class HistoricFlightsEntry:
    date: str
    time: str
    flight_time: float
    number_of_drones: int
    flight_type: FlightType
    flight_distance: float

    def get_object(self):
        return {
            "date": self.date,
            "time": self.time,
            "flight_time": self.flight_time,
            "number_of_drones": self.number_of_drones,
            "flight_type": self.flight_type,
            "flight_distance": self.flight_distance
        }

@dataclass
class HistoricMapsEntry:
    date: str
    time: str
    map: Map

    def get_object(self):
        return {
            "date": self.date,
            "time": self.time,
            "map": self._get_map_as_list()
        }
    
    def _get_map_as_list(self):
        map_list = []
        for coord in self.map.map:
            map_list.append((coord.x, coord.y))
        return map_list
