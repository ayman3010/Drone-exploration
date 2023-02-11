import json
from unittest import mock
import sys

import socketio


from testslide import TestCase


sys.path.append("..")
from ..app import app, socketio
from communication.communication_drone import COMMUNICATION_CHANNELS, CommunicationDrone
from communication.command_drone import Command
from database.database import HistoricFlights, HistoricMaps
from flask_socketio import SocketIO, send, emit, join_room, leave_room, \
    Namespace, disconnect
from drone.drone import DRONES



comm_drone = CommunicationDrone("adr", 1)

class TestApp(TestCase):

    def setUp(self):
        super().setUp()
        self.flask_app = app
        if len(COMMUNICATION_CHANNELS) == 0: COMMUNICATION_CHANNELS.append(comm_drone)
        
        self.test_client = self.flask_app.test_client()

    def test_identify(self):
        self.mock_callable(COMMUNICATION_CHANNELS[0], 'execute_action').for_call(Command.IDENTIFY).to_return_value(None).and_assert_called_once()
        client = socketio.test_client(app, flask_test_client = self.test_client)
        request = [1, False]
        client.emit("identify", request)
        
    def test_launch_mission(self):
        self.mock_callable(COMMUNICATION_CHANNELS[0], 'execute_action').for_call(Command.LAUNCH_MISSION).to_return_value(None).and_assert_called_once()
        client = socketio.test_client(app, flask_test_client = self.test_client)
        request = [1, False]
        client.emit("launch_mission", request)
   
    def test_end_mission(self):
        DRONES[0].start_mission()
        self.mock_callable(COMMUNICATION_CHANNELS[0], 'execute_action').for_call(Command.END_MISSION).to_return_value(None).and_assert_called_once()
        client = socketio.test_client(app, flask_test_client = self.test_client)
        request = [1, False]
        client.emit("end_mission", request)
    
    def test_get_historic_flights(self):
        db_instance = HistoricFlights()
        flights = [1,2,3]
        self.mock_callable(db_instance, 'get_flights').to_return_value(flights).and_assert_called_once()
        client = socketio.test_client(app, flask_test_client = self.test_client)
        client.emit("get-flight-db")

    def test_get_historic_maps(self):
        db_instance = HistoricMaps()
        maps = [1,2,3]
        self.mock_callable(db_instance, 'get_maps').to_return_value(maps).and_assert_called_once()
        client = socketio.test_client(app, flask_test_client = self.test_client)
        client.emit("get-map-db")
        