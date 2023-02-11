#include "receiver.h"

static TaskHandle_t receiver_task_handle;

void radio_receive_task(void*)
{
    PacketRX command_received;  
    Signal signal;

    for(;;)
    {
        if (appchannelReceiveDataPacket(&command_received, sizeof(command_received), APPCHANNEL_WAIT_FOREVER) > 0)
        {
            switch (command_received.command)
            {
                case SignalType::Identify:
                    signal = { .type = SignalType::Identify, .priority = 5, .signal_module = StateMachine };
                    break;
                case SignalType::LaunchMission:
                    signal = { .type = SignalType::LaunchMission, .priority = 1, .signal_module = Modules::StateMachine};
                    break;
                case SignalType::ReturnToBase:
                    signal = { .type = SignalType::ReturnToBase, .priority = 1, .signal_module = Modules::StateMachine};
                    break;
                case SignalType::EndMission:
                    signal = { .type = SignalType::EndMission, .priority = 1, .signal_module = Modules::StateMachine };
                    break;
                case SignalType::LogRequest:
                    signal = { .type = SignalType::LogRequest, .priority = 1, .signal_module = Modules::Transmitter };
                    break;               
                default:
                    signal = { .type = SignalType::Unknown, .priority = 0, .signal_module = Modules::N_MODULES };
                    break;
            }
        }
        // signal_manager.add_signal_to_queue(signal);
    }
}

void start_receive_task() {
        xTaskCreate((TaskFunction_t)radio_receive_task, "Receiver Task", RECEIVER_TASK_SIZE, nullptr, 
                      RECEIVER_TASK_PRIO, &receiver_task_handle);
}
