#include "identify.h"
#include "signal_manager.h"
#include "tasks_config.h"

extern "C" {
#include "FreeRTOS.h"
#include "task.h"
#include "static_mem.h"
}

enum class State { IdentifyMode, ExplorationMode, EndOfMissionMode, ReturnToBaseMode, FailureMode, Default};

void change_state(const Signal& signal);

void state_machine();

// void start_state_machine_task();
