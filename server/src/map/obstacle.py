from drone.drone import DRONES


def add_obstacle(idx:int, x: float,y: float,z: float):
    for drone in DRONES:
        if drone.drone_id == idx:
            drone.map.add_obstacle(x , y ,z)