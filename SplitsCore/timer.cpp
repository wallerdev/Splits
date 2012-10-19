//
//  timer.cpp
//  SplitsCore
//
//  Created by Edward Waller on 10/15/12.
//  Copyright (c) 2012 Edward Waller. All rights reserved.
//

#include "timer.h"
#include <sstream>
#include <iomanip>

Timer::Timer() : _started(false), _stopped(false) {
    
}

Timer::~Timer() {
    
}

void Timer::Start() {
    _started = true;
    _stopped = false;
    _start_time = std::chrono::high_resolution_clock::now();
}

void Timer::Stop() {
    _stopTime = GetTimeElapsed();
    _started = false;
    _stopped = true;
}

std::chrono::high_resolution_clock::duration Timer::GetTimeElapsed() {
    if(_started) {
        return std::chrono::high_resolution_clock::now() - _start_time;
    } else if(_stopped) {
        return _stopTime;
    } else {
        return std::chrono::high_resolution_clock::duration(0);
    }

}

unsigned long Timer::GetTimeElapsedMilliseconds() {
    std::chrono::high_resolution_clock::duration duration = GetTimeElapsed();
    std::chrono::milliseconds mils = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    return mils.count();
}