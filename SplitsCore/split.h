//
//  split.h
//  SplitsCore
//
//  Created by Edward Waller on 10/15/12.
//  Copyright (c) 2012 Edward Waller. All rights reserved.
//

#ifndef __SplitsCore__split__
#define __SplitsCore__split__

#include <iostream>

class Split {
public:
    Split();
    ~Split();
    std::string name();
    void set_name(std::string name);
    unsigned long time();
    void set_time(unsigned long time);
    unsigned long new_time();
    void set_new_time(unsigned long time);
private:
    std::string _name;
    unsigned long _time;
    unsigned long _new_time;
};

#endif /* defined(__SplitsCore__split__) */
