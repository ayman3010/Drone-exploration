#pragma once

struct Position {
    float x;
    float y;
    float z;
};

struct Distance {
    short distance_right;
    short distance_left;
    short distance_front;
    short distance_back;
};

struct LogData
{
    short command_received;
    Position position;
    short orientation;
    Distance distance;
    float battery_voltage;
    Position initial_position;
    short crashed;
};
