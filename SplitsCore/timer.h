//
//  timer.h
//  SplitsCore
//
//  Created by Edward Waller on 10/15/12.
//  Copyright (c) 2012 Edward Waller. All rights reserved.
//

#ifndef __SplitsCore__timer__
#define __SplitsCore__timer__

#include <iostream>

class Timer {
public:
    Timer();
    ~Timer();
    void Start();
    void Stop();
    std::chrono::high_resolution_clock::duration GetTimeElapsed();
    std::string GetTimeElapsedDisplay();
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> _start_time;
};

#endif /* defined(__SplitsCore__timer__) */
