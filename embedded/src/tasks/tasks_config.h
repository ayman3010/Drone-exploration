#ifndef TASKS_CONFIG_H
#define TASKS_CONFIG_H

static constexpr unsigned int STATE_MACHINE_TASK_PRIO = 8;
static constexpr unsigned int RECEIVER_TASK_PRIO = 10;
static constexpr unsigned int SEND_TASK_PRIO = 8;
static constexpr unsigned int SENSOR_TASK_PRIO = 8;
static constexpr unsigned int SIGNAL_MANAGER_PRIO = 2;

static constexpr unsigned int SIGNAL_MANAGER_TASK_SIZE = 400;
static constexpr unsigned int SENSOR_MODULE_TASK_SIZE = 400;
static constexpr unsigned int STATE_MACHINE_TASK_SIZE = 400;
static constexpr unsigned int RECEIVER_TASK_SIZE = 400;
static constexpr unsigned int SEND_TASK_SIZE = 400;

#endif
