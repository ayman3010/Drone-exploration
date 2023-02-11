
extern "C" {
#include "FreeRTOS.h"
#include "task.h"
#include "static_mem.h"
#include "log.h"
#include "signal.h"
#include "data.h"
#include "range.h"
}
#include <math.h>

#include "led.h"
#include "log.h"
#include "param.h"
#include "estimator_kalman.h"
#include "signal_manager.h"

 
#pragma once
extern LogData log_data;

class SensorModule
{
    public:
        SensorModule();
        //void get_battery_percentage();
        void sensor_module_start_task();

        short get_left_distance();
        short get_right_distance();
        short get_front_distance();
        short get_back_distance();

        float get_x_position();
        float get_y_position();
        float get_z_position();
        short get_orientation();
        float get_battery();
        
        void fill_log_values();
        void create_log_signal();
        static void fill_log_values_wrapper(void* _this);
};
