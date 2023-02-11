from database.database import HistoricFlights


historic_flights = None

def get_historic_flights_db() -> HistoricFlights:
    if historic_flights is None:
        historic_flights = HistoricFlights()
        historic_flights.connect_historic_flights()
        return historic_flights
    return historic_flights