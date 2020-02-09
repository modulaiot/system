#include "stdio.h"
#include "System.hpp"

using namespace MIOT::System;

extern "C"
{
    void app_main();
}

void app_main()
{
    printf("Hello World\n");

    Task *task = Task::Run("test", []() {
        printf("Task Action\n");
        Task::Delay(1000);
        return TaskStatus::COMPLETED;
    });

    for (;;)
    {
        printf("Status: %u\n", (uint)task->Status());
        Task::Delay(500);
    }
}