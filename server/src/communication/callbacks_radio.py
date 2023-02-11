import struct
# from communication.communication_client import send_logs, send_new_obstacle, send_crashed_drone

from map.obstacle import add_obstacle
from communication.packet import Packet
from drone.drone import DRONES


# class CallbacksRadio:
#     crazyflie = None
#     def __init__(self):
#         print("CCCCCAAAAAALLLLLLLBAAACCCCKKKKKSSS Init")
#         self.crazyflie.appchannel.packet_received.add_callback(self._add_packet_received)
#         self.logs = []


#     def _add_packet_received(self, packet: list):
#         """Helper function to extract a packet"""
#         print("############# RECEIVED PACKET ###############")
#         data = struct.unpack("<hhhhhhhhhhhh", packet)
#         print(data)
#         if data[9] == 1:
#             send_crashed_drone(self.idx)
#             return
#         packet = Packet(self.idx, data[2],data[3],data[4],data[5],data[6],data[7],data[8])
#         obstacles = DRONES[self.idx-1].map.add_obstacle(packet)
#         send_logs(packet)
        # send_new_obst, self.idxacle(obstacles, self.idx)




        

    # def _get_logs(self):
    #     return self.logs

    # def _clear_logs(self):
    #     self.logs = []
                

        # def add_callbacks(self):
    #     """ Callbacks for the drone"""
    #     self.crazyflie.appchannel.packet_received.add_callback(self._check_packet)
    
    # def _parse_packet(self, packet: Packet) -> None:
    #     """ Analyses packet received"""
    #     if packet.action == DronePacket.OBSTACLE_FOUND:
    #         self._treat_obstacle_found(packet)
    #     if packet.action == DronePacket.IDENTIFY_POSITION:
    #         self._treat_identify_position(packet)
    
    # def _treat_obstacle_found(self, packet):
    #     """ Treats when obstacle is found"""
    #     add_obstacle(packet[0], packet[1], packet[2], packet[3])

    # def _treat_identify_position(self, packet):
    #     pass
