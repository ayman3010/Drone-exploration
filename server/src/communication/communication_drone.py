from cflib.crazyflie import Crazyflie
# from communication.callbacks_radio import CallbacksRadio
from communication.command_drone import Command, CommandDrone



class CommunicationDrone(CommandDrone):
    def __init__(self, crazyflie, idx: int, address):
        self.crazyflie = crazyflie
        CommandDrone.__init__(self)
        self.address = address
        self.idx = idx

    def __del__(self):
        self.crazyflie.close_link()

COMMUNICATION_CHANNELS : list[CommunicationDrone] = []



def send_request_drone(idx: int, command: Command):
    for comm_channel in COMMUNICATION_CHANNELS:
        if comm_channel.idx == idx:\
            comm_channel.execute_action(command)
            
def create_communication_channel(address: str, idx: int):
    COMMUNICATION_CHANNELS.append(CommunicationDrone(address, idx))
