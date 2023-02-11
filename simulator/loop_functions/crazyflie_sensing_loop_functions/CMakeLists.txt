set (CMAKE_CXX_STANDARD 11)

# include(${CMAKE_CURRENT_SOURCE_DIR}/../../socket.io-client-cpp/CMakeLists.txt)

set(crazyflie_sensing_loop_functions_SOURCES
    crazyflie_sensing_loop_functions.h
    crazyflie_sensing_loop_functions.cpp)



add_library(crazyflie_sensing_loop_functions MODULE
  ${crazyflie_sensing_loop_functions_SOURCES})
  
  
target_link_libraries(crazyflie_sensing_loop_functions
  PUBLIC
  sioclient
  argos3core_simulator
  argos3plugin_simulator_entities
  argos3plugin_simulator_footbot)


