#include "signal_manager.h"
#include "identify.h"

unsigned int SignalManager::element_counter = 0;

SignalManager::SignalManager()
{
    signal_manager_mutex = xSemaphoreCreateMutexStatic(&mutex_buffer);

}

void SignalManager::register_signal_callback(Modules module, CallbackFunction callback_function) 
{
    signal_callbacks[module] = callback_function;
}

void SignalManager::start_task() 
{
        xTaskCreate((TaskFunction_t)&manage_signal_wrapper, "Manage Signals", SIGNAL_MANAGER_TASK_SIZE, this, 
                      SIGNAL_MANAGER_PRIO, &signal_manager_task_handle);
}

void SignalManager::add_signal_to_queue(const Signal& signal)
{
    if(signal_manager_mutex != NULL) return;

    // See if we can obtain the semaphore.  If the semaphore is not
    // available wait 100 ticks to see if it becomes free.
    if(xSemaphoreTake(signal_manager_mutex, (TickType_t)100))
    {
        if(element_counter < QUEUE_SIZE) {
            signal_queue[element_counter++] = signal; 
            sort_queue();
        }

        xSemaphoreGive( signal_manager_mutex );
    }
}

void SignalManager::remove_signal_from_queue(const Signal& signal)
{
    if(signal_manager_mutex != NULL) return;
    // See if we can obtain the semaphore.  If the semaphore is not
    // available wait 100 ticks to see if it becomes free.
    // maybe instead 100 tics wait indefinitely
    if(xSemaphoreTake(signal_manager_mutex, (TickType_t)100))
    {
        for(unsigned int i = 0; i < element_counter; i++)
        {
            if(signal.type == signal_queue[i].type)
            {
                for(unsigned int j = i; j < element_counter; j++)
                {   
                    signal_queue[j] = signal_queue[j+1];
                }     
                element_counter--;
            }
        }
        xSemaphoreGive( signal_manager_mutex );
    }
}

Signal SignalManager::get_highest_prio_signal()
{
    Signal signal_to_remove = signal_queue[0];
    remove_signal_from_queue(signal_to_remove);
    return signal_to_remove;
}

//TODO: can be refactored to allow new high prio signals to be placed without going through the entire queue(passing the signal in args)
void SignalManager::sort_queue()
{
    for(unsigned int i = 0; i < element_counter; i++)
    {
        if(signal_queue[i].priority > signal_queue[i + 1].priority)
        {
            Signal shift_signal = signal_queue[i];
            signal_queue[i] = signal_queue[i + 1];
            signal_queue[i + 1] = shift_signal;
        }
    }
}

// TODO: Implement this method and create the task in the construct
void SignalManager::manage_signals()
{
    while(true)
    {
        if(element_counter > 0)
        {
            Signal highest_prio_signal = get_highest_prio_signal();
            CallbackFunction callback = signal_callbacks[highest_prio_signal.signal_module];
            (*callback)(highest_prio_signal);
        }
        vTaskDelay(M2T(1000));
    }
}

void SignalManager::manage_signal_wrapper(void* param)
{
    static_cast<SignalManager*>(param)->manage_signals();
}
