#pragma once

#ifndef ENGINE_RESOURCE_GAMETIME_H
#define ENGINE_RESOURCE_GAMETIME_H

#include <chrono>

class Time
{
    std::chrono::time_point<std::chrono::system_clock> previous_time;
    std::chrono::time_point<std::chrono::system_clock> current_time;
    std::chrono::duration<float> delta_time;
    std::chrono::duration<float> total_time;
    unsigned long long current_frame;
public:
    float time_scale = 1;
    constexpr static float MS_TO_SECONDS = 1000;

    Time();
    void Tick();
    float DeltaTime() const;
    float DeltaTimeRaw() const;
    unsigned long long GetCurrentFrame() const;
};

#endif