#ifdef ESP32

#include "Task.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "stdio.h"

namespace MIOT
{
namespace System
{

struct TaskData
{
    const char *_name;
    Action _action;
    TaskHandle_t _handle;
};

Task *Task::Run(const char *name, const Action action)
{
    TaskData *data = new TaskData();
    data->_name = name;
    data->_action = action;

    Task *task = new Task();
    task->_data = data;

    BaseType_t error = xTaskCreate(_Runner, name, MIOT_TASK_STACK_SIZE, task, tskIDLE_PRIORITY, &data->_handle);

    if (error == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY)
    {
        task->_status = TaskStatus::FAILED;
    }
    else
    {
        task->_status = TaskStatus::RUNNING;
    }

    return task;
}

void Task::_Runner(void *_task)
{
    printf("S: %u\n", uxTaskGetStackHighWaterMark(NULL));

    Task *task = (Task *)_task;
    TaskData *data = (TaskData *)task->_data;

    TaskStatus status = data->_action();
    task->_status = status;

    printf("S: %u\n", uxTaskGetStackHighWaterMark(NULL));

    vTaskDelete(NULL);
}

void Task::Delay(uint32_t delay, bool us)
{
    delay /= portTICK_PERIOD_MS;
    if (us)
    {
        delay /= 1000;
    }
    vTaskDelay(delay);
}

} // namespace System
} // namespace MIOT

#endif