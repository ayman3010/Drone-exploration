// #ifdef _WIN32
// #include <Windows.h>
// #else
// #include <unistd.h>
// #endif
// #include <iostream>
// #include <cstdlib>

// #include "crazyflie_sensing_loop_functions.h"


// class connection_listener
// {
//     sio::client &handler;

// public:
    
//     connection_listener(sio::client& h):
//     handler(h)
//     {
//     }
//     void on_connected()
//     {
//         _lock.lock();
//         _cond.notify_all();
//         connect_finish = true;
//         _lock.unlock();
//     }
//     void on_close(client::close_reason const& reason)
//     {
//         std::cout<<"sio closed "<<std::endl;
//         exit(0);
//     }
    
//     void on_fail()
//     {
//         std::cout<<"sio failed "<<std::endl;
//         exit(0);
//     }
// };

// CCrazyflieSensingLoopFunctions::CCrazyflieSensingLoopFunctions() {}

// CCrazyflieSensingLoopFunctions::~CCrazyflieSensingLoopFunctions(){
// }

// void CCrazyflieSensingLoopFunctions::Init(TConfigurationNode &t_tree){
//    ConnectToServer();
//    std::cout << "has started";
// };

// void CCrazyflieSensingLoopFunctions::Destroy(){
// //    client.sync_close();
// //     client.clear_con_listeners();
// };


// void CCrazyflieSensingLoopFunctions::ConnectToServer(){
//    sio::client client;
//     connection_listener listener(client);
//     client.set_open_listener(std::bind(&connection_listener::on_connected, &listener));
//     client.set_close_listener(std::bind(&connection_listener::on_close, &listener,std::placeholders::_1));
//     client.set_fail_listener(std::bind(&connection_listener::on_fail, &listener));
//     client.connect("http://host.docker.internal:6001");
//     _lock.lock();
//     if(!connect_finish)
//     {
//         _cond.wait(_lock);
//     }
//     _lock.unlock();
// 	  current_socket = client.socket();
//     current_socket->emit("hello");
//     printf("hello emitted\n");
// }

// void CCrazyflieSensingLoopFunctions::bind_events(){
//    current_socket->on("command", sio::socket::event_listener([&](sio::event &event)                                                                 {
//       _lock.lock();
//       std::cout << "Command received from server" << std::endl;
//       _lock.unlock(); 
//       }));
// }  


// REGISTER_LOOP_FUNCTIONS(CCrazyflieSensingLoopFunctions, "crazyflie_sensing_loop_functions");
