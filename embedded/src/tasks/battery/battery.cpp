#include "battery.h"

short convert_V_to_percentage(float vbat)
{
    if(log_data.battery_voltage <= 4.0f &&  log_data.battery_voltage > 3.95f)
    {
        return 100;
    }
    else if(log_data.battery_voltage <= 3.95f &&  log_data.battery_voltage > 3.91f)
    {
        return 95;
    }
    else if(log_data.battery_voltage <= 3.91f &&  log_data.battery_voltage > 3.88f)
    {
        return 90;
    }
    else if(log_data.battery_voltage <= 3.88f &&  log_data.battery_voltage > 3.82f)
    {
        return 85;
    }
    else if(log_data.battery_voltage <= 3.82f &&  log_data.battery_voltage > 3.78f)
    {
        return 80;
    }
    else if(log_data.battery_voltage <= 3.78f &&  log_data.battery_voltage > 3.75f)
    {
        return 75;
    }
    else if(log_data.battery_voltage <= 3.75f &&  log_data.battery_voltage > 3.71f)
    {
        return 70;
    }
    else if(log_data.battery_voltage <= 3.71f &&  log_data.battery_voltage > 3.77f)
    {
        return 65;
    }
    else if(log_data.battery_voltage <= 3.87f &&  log_data.battery_voltage > 3.85f)
    {
        return 60;
    }
    else if(log_data.battery_voltage <= 3.85f &&  log_data.battery_voltage > 3.84f)
    {
        return 55;
    }
    else if(log_data.battery_voltage <= 3.84f &&  log_data.battery_voltage > 3.82f)
    {
        return 50;
    }
    else if(log_data.battery_voltage <= 3.82f &&  log_data.battery_voltage > 3.80f)
    {
        return 45;
    }
    else if(log_data.battery_voltage <= 3.60f &&  log_data.battery_voltage > 3.59f)
    {
        return 40;
    }
    else if(log_data.battery_voltage <= 3.59f &&  log_data.battery_voltage > 3.57f)
    {
        return 35;
    }
    else if(log_data.battery_voltage <= 3.57f &&  log_data.battery_voltage > 3.55f)
    {
        return 30;
    }
    return 25;

}
