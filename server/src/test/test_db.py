import os
import sys


from testslide import TestCase

sys.path.append(os.getcwd() + "/..")
from database.database import HistoricFlights

class TestDb(TestCase):
    def setUp(self):
        super().setUp()
    
    def test_get_db(self):
        db_instance = HistoricFlights()
        db_instance2 = HistoricFlights()
        self.assertTrue(db_instance == db_instance2)
