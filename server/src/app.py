import struct
import time
from communication.command_drone import Command
from flask import jsonify, request
from communication.communication_drone import COMMUNICATION_CHANNELS, CommunicationDrone, send_request_drone
from database.database import HistoricFlights, HistoricMaps
from drone.drone import DRONES, add_flight_to_db
from database.object_entry import FlightType
from communication.packet import Packet
from simulation.simulationDrones import DronesState, SimulationDrone
from server_setup import socketio, app
import json
from cflib.crazyflie import Crazyflie
import random


# ---------------- WEB SOCKET COMMUNICATION --------------------

global simulation_drone_number
simulation_drone_number = int(0)
simulationDrones = {}
dronesLogs = {}
# events from simulator
PACKET = Packet(1, .5, 2,1,.4,.6,.1,80, False).get_object()

@socketio.on('drone_connect')
def connect():
    global simulation_drone_number
    simulation_drone_number += 1
    print("######SOCKET#####")
    print(request.sid)
    print("######SOCKET#####")
    simulationDrones[request.sid] = SimulationDrone(simulation_drone_number, DronesState.WAIT.value)
    
@socketio.on('update_drone_data')
def get_simulation_logs(*data):
    logs_array = list(data)  
    logs_array = logs_array[1::]
    logs_array.insert(0, request.sid)
    print("///////////// UPDATE DRONE DATA /////////////")
    print(simulationDrones[request.sid].droneId)
    id_drone_sim = simulationDrones[request.sid].droneId
    packet = Packet(id_drone_sim, data[2], data[3], data[5]/100, data[6]/100, data[7]/100, data[8]/100, data[9], False)
    if request.sid == logs_array[0]:
        dronesLogs[request.sid] = logs_array
    socketio.emit('simulation_update_drones',dronesLogs)
    socketio.emit('new_obstacle_simulation', {"idx": id_drone_sim, "obstacles": DRONES[id_drone_sim - 1].map.add_obstacle(packet)})

@socketio.on('get-flight-db')
def get_flight_db(args):
    flights = HistoricFlights().get_flights()
    flights = json.dumps(flights)
    socketio.emit('flight_db', flights)

# @socketio.on('get-map-db')
# def get_map_db(args):
#     maps = HistoricMaps().get_maps()
#     maps = json.dumps(maps)
#     socketio.emit('map_db', maps)

@socketio.on('identify')
def identify(args):
    print(' /////////////////// IDENTIFY  ////////////////')
    if (args[1] == True):
        args[1] = args[1]
    else:
        socketio.emit("send_logs", Packet(args[0],0,0,0,0,0,0,0,0).get_object())
        send_request_drone(args[0], Command.IDENTIFY)
        print("ici")
        DRONES[int(args[0])-1].start_mission()

@socketio.on('return_to_base')
def return_to_base(args):
    if (args[1] == True):
        #To be implemented
        args[1] = args[1]
    else:
        print("PHYSIC ID, ", args)
        send_request_drone(args[0], Command.BACK_TO_STATION)
    
@socketio.on('launch_mission')
def launch_mission(args):
    if (args[1] == True):
        socketio.emit("takeoff", to=args[0])
        socketio.emit('simulation_command_log', "Mission Started!")
        id_drone_sim = simulationDrones[args[0]].droneId
        print("Drone launch mission ID: ", id_drone_sim)
        DRONES[int(id_drone_sim)-1].start_mission()
    else:
        print(args)
        send_request_drone(args[0], Command.LAUNCH_MISSION)
        socketio.emit('command_ack', 'Lunch Mission Message Received!')
        DRONES[int(args[0])-1].start_mission()

@socketio.on('end_mission')
def end_mission(args):
    print("END MISSION CALLED")
    if (args[1] == True):
        socketio.emit("land", to=args[0])
        id_drone_sim = simulationDrones[args[0]].droneId
        socketio.emit('simulation_command_log', "Mission Ended!")
        print("Drone end mission ID: ", args[0], id_drone_sim)
        add_flight_to_db(id_drone_sim, FlightType.SIMULATION)
        DRONES[int(id_drone_sim)-1].add_map_to_db()
    else: 
        send_request_drone(args[0], Command.END_MISSION)
        add_flight_to_db(args[0], FlightType.FLIGHT)
        DRONES[int(args[0])-1].add_map_to_db()
        
@socketio.on('return_to_base_client')
def return_to_base(args):
    if(args[1] == True):
        socketio.emit('return_to_base', to=args[0])
    else:
        send_request_drone(args[0], Command.BACK_TO_STATION)

@socketio.on('returned_to_base')
def returned_to_base():
    id_drone_sim = simulationDrones[request.sid].droneId
    socketio.emit('simulation_command_log', "Mission Ended!")
    print("Drone end mission ID: ", request.sid, id_drone_sim)
    add_flight_to_db(id_drone_sim, FlightType.SIMULATION)
    DRONES[int(id_drone_sim)-1].add_map_to_db()
    
@socketio.on('select_zone_client')
def select_zone(args):
    print(args[0])
    socketio.emit('select_zone', args[0])
    


def add_packet_received_1(packet: list):
    """Helper function to extract a packet"""
    print("############# RECEIVED PACKET CCCAAAAALLLLLLBBBBBAAAACCCCCKKKKK1 ###############")
    data = struct.unpack("<hhhhhhhhhh", packet)
    print(data)
    global PACKET
    PACKET = Packet(1, data[2], data[3],data[4],data[5],data[6],data[7],data[8], data[9])
    print("############## PACKET1 ########## ")
    print(PACKET)
    socketio.emit('send_logs', "BONJOUR") 

def add_packet_received_2(packet: list):
    """Helper function to extract a packet"""
    print("############# RECEIVED PACKET CCCAAAAALLLLLLBBBBBAAAACCCCCKKKKK2 ###############")
    data = struct.unpack("<hhhhhhhhhh", packet)
    print(data)
    global PACKET
    PACKET = Packet(2, data[2], data[3],data[4],data[5],data[6],data[7],data[8], data[9]).get_object()
    print("############## PACKET2 ########## ")
    print(PACKET)
    socketio.emit('simulation_update_drones')

@app.route('/log_request', methods=['GET', 'POST'])
def log_request():
    print('LOG REQUEST')
    print(request.get_json())
    if request.method == 'POST':
        droneId = request.get_json().get('id')
    return jsonify(PACKET)
    


if __name__ == '__main__':

    crazyflie1 = Crazyflie()
    crazyflie1.open_link("radio://0/80/2M/E7E7E7E7E7")
    crazyflie2 = Crazyflie()
    crazyflie2.open_link("radio://0/80/2M/E7E7E7E782")
    COMMUNICATION_CHANNELS.append(CommunicationDrone(crazyflie1, 1, "radio://0/80/2M/E7E7E7E7E7"))
    COMMUNICATION_CHANNELS.append(CommunicationDrone(crazyflie2, 2, "radio://0/80/2M/E7E7E7E782"))
    crazyflie1.appchannel.packet_received.add_callback(add_packet_received_1)
    crazyflie2.appchannel.packet_received.add_callback(add_packet_received_2)
    socketio.run(app, host = '0.0.0.0', port=6001, debug = True)
