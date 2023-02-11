
extern "C" {
#include "radiolink.h"
#include "configblock.h"
#include "led.h"
#include <stdio.h>
}
#include<math.h>
#include <stdlib.h>

#include <string.h>
#include "data.h"
#include "sensors.h"
#include "sensor_module.h"


extern SensorModule sensor;
extern LogData log_data;

void p2p_callback_handler(P2PPacket *p);
void send_P2P_packet();