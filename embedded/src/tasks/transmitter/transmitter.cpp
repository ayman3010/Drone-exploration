#include "transmitter.h"
#include "identify.h"
#include "sensor_module.h"

extern SensorModule sensor;

void radio_send_logs()
{
    PacketTX packet_to_send = 
    {   
        .orientation = log_data.orientation,
        .command = log_data.command_received, 
        .x_position = static_cast<short>(log_data.position.x),
        .y_position = static_cast<short>(log_data.position.y),
        .right_distance = log_data.distance.distance_right,
        .left_distance = log_data.distance.distance_left,
        .front_distance = log_data.distance.distance_front,
        .back_distance = log_data.distance.distance_back,
        .battery_percentage = convert_V_to_percentage(log_data.battery_voltage),
        .crashed = log_data.crashed,
    };

    appchannelSendDataPacket(&packet_to_send, sizeof(packet_to_send));
}

