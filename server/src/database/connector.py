from database.constants import CONNECTION_STRING
from pymongo import MongoClient
def get_database(database_name: str): 
   # Create a connection using MongoClient. You can import MongoClient or use pymongo.MongoClient
   client = MongoClient(CONNECTION_STRING)
 
   # Create the database for our example (we will use the same database throughout the tutorial
   return client[database_name]
  
