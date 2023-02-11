
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "autoconf.h"

extern "C" 
{
#include "app.h"
#include "FreeRTOS.h"
#include "task.h"

#include "system.h"
#include "static_mem.h"
#include "debug.h"
}

#include "p2p.h"
#include "signal_manager.h"
#include "receiver.h"
#include "state_machine.h"
#include "start.h"
#include "sensor_module.h"
#include "data.h"
#include "console.h"
#include "transmitter.h"

#define MAX(a,b) (((a)>(b))?(a):(b))

SensorModule sensor;
SignalManager signal_manager;
LogData log_data;
extern State state;

bool P2P = false;

static int count;

void appMain() 
{
  count = 0;
  while (true) 
  {
    PacketRX command_received;  
    Signal signal;

    sensor.fill_log_values();

    if(log_data.orientation < -60 ||  log_data.orientation > 45)
    {
      log_data.crashed = 1;
    }
    else
    {
      log_data.crashed = 0;
    }
    
    if (appchannelReceiveDataPacket(&command_received, sizeof(command_received), 250))
    {
      switch (command_received.command)
      {
        case SignalType::Identify:
            signal = { .type = SignalType::Identify, .priority = 5, .signal_module = StateMachine };
            change_state(signal);
            break;
        case SignalType::LaunchMission:
              log_data.initial_position = {.x = sensor.get_x_position(), .y = sensor.get_y_position(), .z = sensor.get_z_position()};
              signal = { .type = SignalType::LaunchMission, .priority = 1, .signal_module = Modules::StateMachine};
              change_state(signal);
            break;
        case SignalType::ReturnToBase:
            signal = { .type = SignalType::ReturnToBase, .priority = 1, .signal_module = Modules::StateMachine};
            change_state(signal);
            break;
        case SignalType::EndMission:
            signal = { .type = SignalType::EndMission, .priority = 1, .signal_module = Modules::StateMachine };
            change_state(signal);
            break;
        case SignalType::LogRequest:
            radio_send_logs();
            break;
        case SignalType::PeerToPeer:
            P2P = true;
            send_P2P_packet();
            break;            
        default:
            signal = { .type = SignalType::Unknown, .priority = 0, .signal_module = Modules::N_MODULES };
            break;
      }

    }

    state_machine();

    if(count % 20 == 0)
    {
      radio_send_logs();
    }  

    if(count % 5 == 0)
    {
      send_P2P_packet();
    }

    count++;

    vTaskDelay(10);
  }

}
