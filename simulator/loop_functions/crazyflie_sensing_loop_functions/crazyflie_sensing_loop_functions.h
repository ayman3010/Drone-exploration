// // reference: https://github.com/socketio/socket.io-client-cpp/blob/master/examples/Console/main.cpp
// #ifndef CRAZYFLIE_LOOP_FUNCTIONS_H
// #define CRAZYFLIE_LOOP_FUNCTIONS_H

// #include <argos3/core/simulator/loop_functions.h>
// #include <controllers/crazyflie_sensing/crazyflie_sensing.h>
// #include <argos3/core/simulator/simulator.h>
// #include <argos3/plugins/robots/crazyflie/simulator/crazyflie_entity.h>
// #include <argos3/core/utility/configuration/argos_configuration.h>
// #include <argos3/core/utility/logging/argos_colored_text.h>
// #include <argos3/core/utility/math/vector3.h>
// #include <sio_client.h>

// #include <functional>
// #include <iostream>
// #include <thread>
// #include <mutex>
// #include <condition_variable>
// #include <string>

// using namespace sio;
// using namespace std;
// std::mutex _lock;

// std::condition_variable_any _cond;
// bool connect_finish = false;
// using namespace argos;

// class CCrazyflieSensingLoopFunctions : public CLoopFunctions{
// public:
//    CCrazyflieSensingLoopFunctions();
//    virtual ~CCrazyflieSensingLoopFunctions();

//    virtual void Init(TConfigurationNode &t_tree);

//    virtual void Destroy();
   
//    void ConnectToServer();

// private:
//    void bind_events();
//    socket::ptr current_socket;
//    sio::client client;

// };

// #endif
