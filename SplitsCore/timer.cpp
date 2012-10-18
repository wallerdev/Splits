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

Timer::Timer() {
    
}

Timer::~Timer() {
    
}

void Timer::Start() {
     _start_time = std::chrono::high_resolution_clock::now();
}

void Timer::Stop() {
    
}

std::chrono::high_resolution_clock::duration Timer::GetTimeElapsed() {
    return std::chrono::high_resolution_clock::now() - _start_time;
}

std::string Timer::GetTimeElapsedDisplay() {
    std::chrono::high_resolution_clock::duration duration = GetTimeElapsed();
    std::chrono::milliseconds mils = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    unsigned long miliseconds = mils.count();
    
    int hours = miliseconds / (1000*60*60);
    int mins = (miliseconds % (1000*60*60)) / (1000*60);
    int seconds = ((miliseconds % (1000*60*60)) % (1000*60)) / 1000;
    int rem_mili = ((miliseconds % (1000*60*60)) % (1000*60)) % 1000;

    std::stringstream ss;
    ss << std::setfill('0');
    ss << hours << ":" << std::setw(2) << mins << ":" << std::setw(2) << seconds << "." << std::setw(3) << rem_mili;
    return ss.str();
}