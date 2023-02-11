#include "sensor_module.h"
extern LogData log_data;

extern SignalManager signal_manager;

static TaskHandle_t sensor_module_task_handle;

SensorModule::SensorModule() 
{
}

// void ::get_battery_percentage()
// {
//     float supply_voltage = pmGetBatteryVoltage();
//     float supply_ratio = supply_voltage - MIN_BATTERY ;
//     float ratio = MAX_BATTERY - MIN_BATTERY;

//     battery_percentage = supply_ratio / ratio;
// }   

void SensorModule::sensor_module_start_task()
{
    xTaskCreate(this->fill_log_values_wrapper, "Collect log_data", SENSOR_MODULE_TASK_SIZE, nullptr,
                      SENSOR_TASK_PRIO, &sensor_module_task_handle);
}

short SensorModule::get_left_distance()
{
    logVarId_t left_distance_id = logGetVarId("range", "left");
    return static_cast<short>(logGetUint(left_distance_id));
}

short SensorModule::get_right_distance()
{
    logVarId_t right_distance_id = logGetVarId("range", "right");
    return static_cast<short>(logGetUint(right_distance_id));
}

short SensorModule::get_front_distance()
{
    logVarId_t front_distance_id = logGetVarId("range", "front");
    return static_cast<short>(logGetUint(front_distance_id));
}

short SensorModule::get_back_distance()
{
    logVarId_t back_distance_id = logGetVarId("range", "back");
    return static_cast<short>(logGetUint(back_distance_id));
}

float SensorModule::get_x_position()
{
    logVarId_t x_position_id = logGetVarId("stateEstimate", "x");
    return (logGetFloat(x_position_id));
}

float SensorModule::get_y_position()
{
    logVarId_t y_position_id = logGetVarId("stateEstimate", "y");
    return (logGetFloat(y_position_id));    
    
}

float SensorModule::get_z_position()
{
    logVarId_t z_position_id = logGetVarId("stateEstimate", "z");
    return (logGetFloat(z_position_id));
}

short SensorModule::get_orientation()
{
    logVarId_t orientation = logGetVarId("stabilizer", "roll");
    return static_cast<short>(logGetUint(orientation));
}

float SensorModule::get_battery(){
    logVarId_t battery_id = logGetVarId("pm", "vbat");  
    return (logGetFloat(battery_id));
}


void SensorModule::fill_log_values() 
{ 
    log_data.orientation = get_orientation();

    log_data.battery_voltage = get_battery();

    log_data.distance = {
        .distance_right = get_right_distance(), 
        .distance_left = get_left_distance(),
        .distance_front = get_front_distance(),
        .distance_back = get_back_distance(),
                        };

    log_data.position = {
        .x = get_x_position(),
        .y = get_y_position(),
        .z = get_z_position(),
    };
}

void SensorModule::fill_log_values_wrapper(void* _this)
{
    static_cast<SensorModule*>(_this)->fill_log_values();
}