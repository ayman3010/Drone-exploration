import sys
import struct

from testslide import TestCase
import os

sys.path.append(os.getcwd() + "/..")

from communication.command_drone import Command, CommandDrone
from communication.communication_drone import CommunicationDrone
from cflib.crazyflie import Crazyflie


class TestCommandDrone(TestCase):
    def setUp(self):
        super().setUp()
        self.comm_drone = CommunicationDrone("adr", 1)
        self.crazyflie = self.comm_drone.crazyflie

    def test_identify_drone(self):
        data = struct.pack("<hi", self.comm_drone.idx, Command.IDENTIFY.value)
        data_rdm = struct.pack("<i", 12345)
        self.mock_callable(self.crazyflie.appchannel, 'send_packet').for_call(data).to_return_value(None).and_assert_called_once()
        self.mock_callable(self.crazyflie.appchannel, 'send_packet').for_call(data_rdm).to_return_value(None).and_assert_not_called()
        self.comm_drone._identify_drone()

    def test_launch_mission(self):
        data = struct.pack("<hi", self.comm_drone.idx, Command.LAUNCH_MISSION.value)
        data_rdm = struct.pack("<i", 12345)
        self.mock_callable(self.crazyflie.appchannel, 'send_packet').for_call(data).to_return_value(None).and_assert_called_once()
        self.mock_callable(self.crazyflie.appchannel, 'send_packet').for_call(data_rdm).to_return_value(None).and_assert_not_called()
        self.comm_drone._launch_mission()

    def test_update_drone(self):
        data = struct.pack("<hi", self.comm_drone.idx, Command.UPDATE.value)
        data_rdm = struct.pack("<i", 12345)
        self.mock_callable(self.crazyflie.appchannel, 'send_packet').for_call(data).to_return_value(None).and_assert_called_once()
        self.mock_callable(self.crazyflie.appchannel, 'send_packet').for_call(data_rdm).to_return_value(None).and_assert_not_called()
        self.comm_drone._update_drone()

    def test_bring_drone_ground_station(self):
        data = struct.pack("<hi", self.comm_drone.idx, Command.BACK_TO_STATION.value)
        data_rdm = struct.pack("<i", 12345)
        self.mock_callable(self.crazyflie.appchannel, 'send_packet').for_call(data).to_return_value(None).and_assert_called_once()
        self.mock_callable(self.crazyflie.appchannel, 'send_packet').for_call(data_rdm).to_return_value(None).and_assert_not_called()
        self.comm_drone._bring_drone_ground_station()

    def test_execute_p2p(self):
        data = struct.pack("<hi", self.comm_drone.idx, Command.P2P.value)
        data_rdm = struct.pack("<i", 12345)
        self.mock_callable(self.crazyflie.appchannel, 'send_packet').for_call(data).to_return_value(None).and_assert_called_once()
        self.mock_callable(self.crazyflie.appchannel, 'send_packet').for_call(data_rdm).to_return_value(None).and_assert_not_called()
        self.comm_drone._execute_p2p()
    
    

