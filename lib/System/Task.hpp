#pragma once

#include <functional>
#include "Config.hpp"

namespace MIOT
{
namespace System
{

enum class TaskStatus
{
    INIT,
    RUNNING,
    COMPLETED,
    FAILED
};

typedef std::function<TaskStatus()> Action;

class ITask
{
public:
    bool Running() { return Status() == TaskStatus::RUNNING; }
    bool Completed() { return Status() == TaskStatus::COMPLETED; }
    bool Failed() { return Status() == TaskStatus::FAILED; }
    bool Done() { return Status() != TaskStatus::INIT && Status() != TaskStatus::RUNNING; }

    virtual TaskStatus Status();
};

class Task : public ITask
{
public:
    TaskStatus Status() override { return _status; }

    // Device Dependant
    static Task *Run(const char *name, const Action action);
    static void Delay(uint32_t delay, bool us = false);

protected:
    TaskStatus _status = TaskStatus::INIT;

    // Device Dependant
    void *_data;
    static void _Runner(void *_task);
};

} // namespace System
} // namespace MIOT