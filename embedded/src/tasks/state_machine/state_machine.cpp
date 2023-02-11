#include "state_machine.h"
#include "start.h"
#include "return_to_base.h"
#include "data.h"
#include "sensor_module.h"

State state; 

extern LogData log_data;
extern SensorModule sensor;
extern bool P2P;

void change_state(const Signal& signal)
{
    switch (signal.type) {
        case SignalType::Identify:
            state = State::IdentifyMode;
            log_data.command_received = static_cast<short>(state);
            break;
        case SignalType::LaunchMission:
            state = State::ExplorationMode;
            log_data.command_received = static_cast<short>(state);
            break;
        case SignalType::ReturnToBase:
            vTaskDelay(10);
            state = State::ReturnToBaseMode;
            log_data.command_received = static_cast<short>(state);
            break;
        case SignalType::EndMission:
            P2P = false;
            state = State::EndOfMissionMode;
            log_data.command_received = static_cast<short>(state);
            break;
        case SignalType::Failure:
            state = State::FailureMode;
            log_data.command_received = static_cast<short>(state);
            break;       
        default:
            log_data.command_received = static_cast<short>(State::FailureMode);
            break;
    }
}

void state_machine()
{
    switch (state)
    {
        case State::IdentifyMode:
            identify_blue();
            state = State::Default;
            break;
        case State::ExplorationMode:
            start_mission();
            break;
        case State::EndOfMissionMode:
            end_mission();
            state = State::Default;
            break;
        case State::ReturnToBaseMode:
            return_to_base();
            break;
        case State::FailureMode:
            break;
        case State::Default:
            break;
        default:
            break;
    }
    
}

// void start_state_machine_task() {
//     xTaskCreate((TaskFunction_t)state_machine, "State Machine", STATE_MACHINE_TASK_SIZE, nullptr, STATE_MACHINE_TASK_PRIO, &state_machine_task_handle);
// }
