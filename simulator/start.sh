#!/bin/bash
cd /root/argos3-webviz/client && python3 -m http.server &
cd /root/simulator && mkdir build
cd /root/simulator/build && cmake ..
cd /root/simulator/build && cmake --build .
cd /root/simulator && argos3 -c experiments/crazyflie_sensing.argos
