#include <string.h>
#include <stdint.h>
#include <stdbool.h>

extern "C"
{
#include "app.h"
#include "commander.h"
#include "FreeRTOS.h"
#include "task.h"
#include "log.h"
#include "param.h"
}
#include "data.h"
#include "log.h"

extern LogData log_data;

void setHoverSetpoint(setpoint_t *setpoint, float vx, float vy, float z, float yawrate);

void start_mission();

void end_mission();
