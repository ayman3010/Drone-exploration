from enum import Enum

class DronesState(Enum):
    WAIT = 'waiting'
    TAKE_OFF = 'taking off'
    EXPLORE = 'exploring'
    LAND = 'landing'
    UNKNOWN = 'UNKNOWN'


class SimulationDrone:
    def __init__(self, droneId, state):
        self.droneId = droneId
        self.state = state
        