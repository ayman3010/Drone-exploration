
extern "C" {
#include "FreeRTOS.h"
#include "task.h"
#include "app_channel.h"
#include "static_mem.h"
}
#include <cstdlib>

#include "tasks_config.h"
#include "data.h"
#include "signal.h"
#include "battery.h"

extern LogData log_data;

struct PacketTX 
{
    short orientation;
    short command;
    short x_position;
    short y_position;
    short right_distance;
    short left_distance;
    short front_distance;
    short back_distance;
    short battery_percentage;
    short crashed;


} __attribute__((packed));

void radio_send_logs();


