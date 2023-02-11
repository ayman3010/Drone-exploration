import sys

from testslide import TestCase
import os

sys.path.append(os.getcwd() + "/..")
from communication.communication_drone import CommunicationDrone


class TestCallbackRadio(TestCase):
    def setUp(self):
        super().setUp()
        self.callback = CommunicationDrone("adress", 1)

    def test_extract_packet_obstacle_found(self):
        packet = []
        