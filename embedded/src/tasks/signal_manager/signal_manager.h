#include "eventtrigger.h"
extern "C" {
#include "FreeRTOS.h"
#include "semphr.h"
#include "static_mem.h"
#include "task.h"
}

#include "tasks_config.h"

enum SignalType { Unknown, Identify, LaunchMission, ReturnToBase, Failure, EndMission, LogRequest, PeerToPeer };

// TODO: Move this to separate file
enum Modules { StateMachine, Transmitter, N_MODULES };

struct Signal   
{
    SignalType type;
    int priority;
    Modules signal_module;
};

using CallbackFunction = void (*)(const Signal&); 

#pragma once

class SignalManager
{
    public:
        SignalManager();
        void add_signal_to_queue(const Signal& signal);
        void remove_signal_from_queue(const Signal& signal);
        Signal get_highest_prio_signal();
        void manage_signals();
        void sort_queue();
        void register_signal_callback(Modules destination_module, CallbackFunction callback_function);
        void start_task();
        static void manage_signal_wrapper(void* param);

    private:

        static constexpr unsigned int QUEUE_SIZE = 420;
        static unsigned int element_counter;
        Signal signal_queue[QUEUE_SIZE];

        SemaphoreHandle_t signal_manager_mutex = NULL;
        StaticSemaphore_t mutex_buffer;

        CallbackFunction signal_callbacks[Modules::N_MODULES];

        xTaskHandle signal_manager_task_handle;
};
