add_library(crazyflie_sensing SHARED crazyflie_sensing.h crazyflie_sensing.cpp socket_manager.h socket_manager.cpp)

target_link_libraries(crazyflie_sensing
  PUBLIC 
  sioclient
  argos3core_simulator
  argos3plugin_simulator_crazyflie
  argos3plugin_simulator_genericrobot)
