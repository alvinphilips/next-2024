#include "stdafx.h"
#include "system.h"

System::System(const SystemFunction& system)
{
    func = system;
    schedule = SystemSchedule::EachFrame;
    is_enabled = true;
}

System::System(const SystemFunction& system, const SystemSchedule schedule)
{
    func = system;
    this->schedule = schedule;
    is_enabled = true;
}

bool System::Restart()
{
    const bool was_running = is_enabled;

    is_enabled = true;
    return was_running;
}
