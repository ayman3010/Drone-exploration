"""CommandDrone """
import struct
from enum import Enum
import threading
from cflib.crazyflie import Crazyflie
import cflib
import time


class Command(Enum):
    """Possible commands for the drone"""
    UNKOWN          = 0 
    IDENTIFY        = 1
    LAUNCH_MISSION  = 2
    BACK_TO_STATION = 3
    FAILURE         = 4
    END_MISSION     = 5
    LOG_REQUEST     = 6
    UPDATE          = 7
    P2P             = 8

class CommandDrone:
    """Various operations for drones"""
    def __init__(self):
        cflib.crtp.init_drivers(enable_debug_driver=False)
        
    def execute_action(self, command: Command) -> None:
        """Parses action"""
        self.crazyflie.open_link(self.address)
        if command == Command.IDENTIFY:
            self._identify_drone()
        elif command == Command.LAUNCH_MISSION:
            # self._set_log_calls()
            self._launch_mission()
        elif command == Command.END_MISSION:
            self._end_mission()
        elif command == Command.UPDATE:
            self._update_drone()
        elif command == Command.BACK_TO_STATION:
            self._bring_drone_ground_station()
        elif command == Command.P2P:
            self._execute_p2p()
        # elif command == Command.LOG_REQUEST:
        #     self._log_request()
        elif command == Command.BACK_TO_STATION:
            self._return_to_base()
    
    def _return_to_base(self):
        data = self._produce_struct_pack(Command.BACK_TO_STATION)
        self.crazyflie.appchannel.send_packet(data)

    def _produce_struct_pack(self, command:Command) -> bytes:
        """Produce the packet"""
        return struct.pack("<i", int(command.value))

    def _identify_drone(self) -> None:
        """idxentify the drone"""
        data = self._produce_struct_pack(Command.IDENTIFY)
        self.crazyflie.appchannel.send_packet(data)

    def _launch_mission(self) -> None:
        """Lunch mission the drone"""
        data = self._produce_struct_pack(Command.LAUNCH_MISSION)
        self.crazyflie.appchannel.send_packet(data)

    def _end_mission(self) -> None:
        """End mission the drone"""
        data = self._produce_struct_pack(Command.END_MISSION)
        self.crazyflie.appchannel.send_packet(data)
    
    def _update_drone(self) -> None:
        """" Updates drone"""
        data = self._produce_struct_pack(Command.UPDATE)
        self.crazyflie.appchannel.send_packet(data)

    def _bring_drone_ground_station(self) -> None:
        """Brings drone back to ground station"""
        data = self._produce_struct_pack(Command.BACK_TO_STATION)
        self.crazyflie.appchannel.send_packet(data)

    def _execute_p2p(self) -> None:
        """Executes p2p operation"""
        data = self._produce_struct_pack(Command.P2P)
        self.crazyflie.appchannel.send_packet(data)


    
