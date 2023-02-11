from socket import SocketIO
from flask import Flask, jsonify, request
from flask_cors import CORS
from flask_socketio import SocketIO
import sys

# ---------------- SERVER SETUP --------------------
app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
CORS(app)
socketio = SocketIO(app,engineio_logger=True, logger=True, debug=True, cors_allowed_origins="*")

gevent_socketio_found = True
try:
    from socketio import socketio_manage  # noqa: F401
except ImportError:
    gevent_socketio_found = False
if gevent_socketio_found:
    print('The gevent-socketio package is incompatible with this version of '
          'the Flask-SocketIO extension. Please uninstall it, and then '
          'install the latest version of python-socketio in its place.')
    sys.exit(1)