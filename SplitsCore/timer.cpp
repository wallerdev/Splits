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

Timer::Timer() : _started(false) {
    
}

Timer::~Timer() {
    
}

void Timer::Start() {
    _started = true;
    _start_time = std::chrono::high_resolution_clock::now();
}

void Timer::Stop() {
    
}

std::chrono::high_resolution_clock::duration Timer::GetTimeElapsed() {
    if(_started) {
        return std::chrono::high_resolution_clock::now() - _start_time;
    } else {
        return std::chrono::high_resolution_clock::duration(0);
    }

}

unsigned long Timer::GetTimeElapsedMilliseconds() {
    std::chrono::high_resolution_clock::duration duration = GetTimeElapsed();
    std::chrono::milliseconds mils = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    return mils.count();
}