// External headers
extern "C" {
#include "FreeRTOS.h"
#include "task.h"
#include "app_channel.h"
#include "static_mem.h"
}

// Project headers
#include "identify.h"
#include "signal_manager.h"
#include "tasks_config.h"

extern SignalManager signal_manager;

struct PacketRX 
{
  int command : 8;
} __attribute__((packed));

void radio_receive_task();

void start_receive_task();
