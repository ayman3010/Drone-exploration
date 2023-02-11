// reference: https://github.com/socketio/socket.io-client-cpp/blob/master/examples/Console/main.cpp
#ifndef SOCKET_MANAGER_H
#define SOCKET_MANAGER_H
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <string>
#include <stdio.h>
#include <sio_client.h>
#include <iostream>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>
#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <sstream>

using namespace std;
using namespace sio;
using namespace std;

enum State
{
   WAIT,  
   TAKEOFF,
   EXPLORE,
   LAND,
   AVOID,
   RETURN_TO_BASE
};


class SocketManager{
public:
    void ConnectToServer();
    void bind_event();
    void on_connected();
    void on_fail();
    void on_close(sio::client::close_reason const& reason);
    void on_start_mission(sio::event& event);
    void on_end_mission(sio::event& event);
    void on_take_off(sio::event& event);
    void on_land(sio::event& event);  
    void on_return_to_base(sio::event& event);
    void on_select_zone(sio::event& event);
    State current_state = WAIT;
    socket::ptr current_socket;
    float zone_coordinates[4] = {0.0, 0.0, 0.0, 0.0};;
    bool zone_specified = false;
private:
    bool connection_established;
    sio::client client;
    std::mutex _lock;
    std::condition_variable_any _cond;
};
#endif
