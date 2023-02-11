#include "socket_manager.h"

void SocketManager::ConnectToServer(){
    this->client.set_open_listener(std::bind(&SocketManager::on_connected,this));
    this->client.set_close_listener(std::bind(&SocketManager::on_close,this,std::placeholders::_1));
    this->client.set_fail_listener(std::bind(&SocketManager::on_fail, this));
    this->client.connect("http://host.docker.internal:6001");
    _lock.lock();
    if(!connection_established)
    {
        _cond.wait(_lock);
    }
    _lock.unlock();
    sleep(5);
	this->current_socket = this->client.socket();
    this->bind_event();
}

void SocketManager::on_connected()
{
    _lock.lock();
    _cond.notify_all();
    this->connection_established = true;
    _lock.unlock();
}
void SocketManager::on_close(sio::client::close_reason const& reason)
{
    std::cout<<"Connection with the server has been closed "<<std::endl;
    this->connection_established = false;
}

void SocketManager::on_fail()
{
    std::cout<<"Connection with the server has failed "<<std::endl;
    this->connection_established = false;
}


void SocketManager::on_take_off(sio::event& event){
     _lock.lock();
     this->current_state = TAKEOFF;
     printf("Take off command received\n");
    _lock.unlock();
}

void SocketManager::on_land(sio::event& event){
     _lock.lock();
     this->current_state = LAND;
    printf("landing command received\n");

    _lock.unlock();
}

void SocketManager::on_return_to_base(sio::event& event){
     _lock.lock();
     this->current_state = RETURN_TO_BASE;
    printf("return to base command received\n");
    _lock.unlock();
}

void SocketManager::on_select_zone(sio::event& event){
     _lock.lock();

    std::string Numbers = event.get_message()->get_string();
    std::vector<float> v;
    std::istringstream iss(Numbers);
    std::copy(std::istream_iterator<float>(iss),
        std::istream_iterator<float>(),
        std::back_inserter(v));
    std::copy(v.begin(), v.end(),
        std::ostream_iterator<float>(std::cout, ", "));
    cout<<"Vector: ";
    float arr[4];
    copy(v.begin(),v.end(),zone_coordinates);
    zone_specified = true;
    printf("zone specified \n");
    _lock.unlock();
}


void SocketManager::bind_event(){
    this->current_socket->on("takeoff", std::bind(&SocketManager::on_take_off,this,std::placeholders::_1));
    this->current_socket->on("land", std::bind(&SocketManager::on_land,this,std::placeholders::_1));
    this->current_socket->on("return_to_base", std::bind(&SocketManager::on_return_to_base,this,std::placeholders::_1));
    this->current_socket->on("select_zone", std::bind(&SocketManager::on_select_zone,this,std::placeholders::_1));
} 