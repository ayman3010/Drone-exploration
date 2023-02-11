from database.connector import get_database
from database.constants import DB_NAME, HISTORIC_FLIGHTS_COLLECTION_NAME, HISTORIC_MAPS_COLLECTION_NAME
from database.object_entry import HistoricFlightsEntry, HistoricMapsEntry
from singleton_decorator import singleton



class DatabaseCollection:
    def connect_database(self, db_name: str):
        self.collection = get_database(DB_NAME)[db_name]
        return self.collection

    def add_entry(self, new_data: any) -> None:
        self.collection.insert_one(new_data)

    def query_collection(self) -> any:
        return self.collection.find()

@singleton
class HistoricFlights(DatabaseCollection):
    connected = False
    def connect_historic_flights(self) -> None:
        self.collection = self.connect_database(HISTORIC_FLIGHTS_COLLECTION_NAME)
        self.connected = True

    def add_flight(self, new_flight: HistoricFlightsEntry) -> None:
        if not self.connected: self.connect_historic_flights()
        self.add_entry(new_flight.get_object())

    def get_flights(self) -> list:
        if not self.connected: self.connect_historic_flights()
        flights = self.query_collection()
        flights_db = [HistoricFlightsEntry(flight["date"], flight["time"], flight["flight_time"], 
                      flight["number_of_drones"], flight["flight_type"], flight["flight_distance"]).get_object() for flight in flights]
        return flights_db

@singleton
class HistoricMaps(DatabaseCollection):
    connected = False

    def connect_historic_maps(self) -> None:
        self.collection =  self.connect_database(HISTORIC_MAPS_COLLECTION_NAME)
        self.connected = True

    def add_map(self, new_map: HistoricMapsEntry) -> None:
        if not self.connected: self.connect_historic_maps()
        self.add_entry(new_map.get_object())

    def get_maps(self) -> list:
        if not self.connected: self.connect_historic_maps()
        maps = self.query_collection()
        maps_db = [HistoricMapsEntry(map["date"], map["time"], map["map"]) for map in maps]
        return maps_db
