#include "stdafx.h"
#include "gametime.h"

Time::Time()
{
    previous_time = std::chrono::system_clock::now();
    current_time = previous_time;
    current_frame = 0;
    delta_time = std::chrono::duration<float>(0);
    total_time = std::chrono::duration<float>(0);
}

void Time::Tick()
{
    previous_time = current_time;
    current_time = std::chrono::system_clock::now();

    delta_time = current_time - previous_time;
    total_time += delta_time;

    current_frame++;
}


float Time::DeltaTime() const
{
    return delta_time.count();
}

float Time::DeltaTimeRaw() const
{
    return delta_time.count() * time_scale;
}

unsigned long long Time::GetCurrentFrame() const
{
    return current_frame;
}
