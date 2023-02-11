from map.map import Map
from database.object_entry import FlightType, HistoricFlightsEntry, HistoricMapsEntry
from datetime import datetime
import time
from database.database import HistoricFlights, HistoricMaps

class Drone:
    "Important information about the drone"
    def __init__(self, drone_id: int):
        self.drone_id = drone_id
        self.map = Map()
        self.isActive = False
        self.hasBeenActive = False

    def start_mission(self) -> None:
        self.start_time = time.time()
        self.isActive = True
        self.hasBeenActive = True    

    def add_map_to_db(self) -> None:
        current_time = datetime.now()
        date = str(current_time.year) + "/" + str(current_time.month) + "/" + str(current_time.day)
        time = str(current_time.hour) + ":" + str(current_time.minute) + ":" + str(current_time.second)
        histMap = HistoricMapsEntry(date, time, self.map)
        HistoricMaps().add_map(histMap)

    
DRONES : list[Drone] = [Drone(i) for i in range(10)]

def get_number_of_drones():
    number_of_drones = 0
    for drone in DRONES:
        if drone.hasBeenActive:
            number_of_drones+=1
    return number_of_drones
            

def add_flight_to_db(idx: int, flight_type: FlightType) -> None:
    print("############ ADD FLIGH DATABASE ################")
    print(" DRONE ID " , idx )
    print("############ ADD FLIGH DATABASE ################")
    current_time = datetime.now()
    date = str(current_time.year) + "/" + str(current_time.month) + "/" + str(current_time.day)
    physical_time = str(current_time.hour) + ":" + str(current_time.minute) + ":" + str(current_time.second)
    DRONES[idx-1].isActive = False
    flight_time = time.time() - DRONES[idx - 1].start_time 
    nb_drones = get_number_of_drones()
    flight_distance = DRONES[idx -1].map.distance
    histFlight = HistoricFlightsEntry(date, physical_time, flight_time, nb_drones, flight_type, flight_distance)
    HistoricFlights().add_flight(histFlight)
